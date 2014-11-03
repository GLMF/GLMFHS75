/*
 PI_GPIO.c  (c) Yann Guidon 20130204
 Accès aux E/S de la carte Raspberry Pi
 Dérivé du code de Dom & Gert @ http://elinux.org/RPi_Low-level_peripherals version 20130101

  20130507 : mmap : valeur de retour corrigée (MAP_FAILED)
  20130508 : modifs pour ajouter SPI
  20130513
  20130527 stupid mask bug found ! avoid previous versions !!!
  20130611 added input macro
  20140726 fonction "parachute"
  20140904 err()
  20140907 : tout sur stderr
*/

#ifndef PI_GPIO
#define PI_GPIO

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

int mmap_fd=0;

#define GPIO_BASE  (0x20200000)
#define BLOCK_SIZE (4096) // correspond à la taille d'une page de MMU */

// si la fonction erreur() n'est pas déjà fournie
#ifdef PI_GPIO_ERR
#include <errno.h>

/* sortie avec un message d'erreur contextualisé */
void erreur(char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

// 2è message d'erreur, sans perror
void err(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(EXIT_FAILURE);
}
#endif

unsigned * PI_IOmmap(off_t where) {
   void* map;

   // ne réouvre pas /dev/mem si on l'a déjà ouvert
   if (mmap_fd <= 0) {
     // ouvre /dev/mem
     if ((mmap_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
       erreur("Echec à l'ouverture de /dev/mem");
   }

   // projette les registres GPIO dans la mémoire de notre programme
   map = mmap(
      NULL,             // projette où ça arrange le kernel
      BLOCK_SIZE,       // les registres de contrôle tiennent dans une seule page
      PROT_READ|PROT_WRITE, // on veut lire et écrire
      MAP_SHARED,       // partagé avec d'autres processus
      mmap_fd,          // la mémoire
      where             // adresse de la zone à accéder
   );

   if (map == MAP_FAILED)
     erreur("Echec de mmap()");

   return (unsigned*)map;
}


volatile unsigned *PI_gpio=NULL; // DOIT être volatile
// Pour mettre des broches à 1 ou à 0 :
#define RPI_GPSET0   (7)
#define RPI_GPCLR0  (10)
#define RPI_GPLEV0  (13)
#define GPIO_SET    *(PI_gpio+RPI_GPSET0)
#define GPIO_CLR    *(PI_gpio+RPI_GPCLR0)
#define GPIO_LEV    *(PI_gpio+RPI_GPLEV0)

#define GPIO_SET_N(N) GPIO_SET = (1 << N)
#define GPIO_CLR_N(N) GPIO_CLR = (1 << N)
#define GPIO_LEV_N(N) (((GPIO_LEV) >> N) &1)

#define BCM_GPIO_IN   (0)
#define BCM_GPIO_OUT  (1)
#define BCM_GPIO_ALT0 (4)
#define BCM_GPIO_ALT1 (5)
#define BCM_GPIO_ALT2 (6)
#define BCM_GPIO_ALT3 (7)
#define BCM_GPIO_ALT4 (3)
#define BCM_GPIO_ALT5 (2)
#define BCM_GPIO_ALT3 (7)


#ifndef GPIO_NO_ATEXIT
unsigned long long int GPIO_used=0; // Liste des broches à désactiver
void GPIO_parachute(); // pré-déclaration

#include <signal.h>
#endif

// à appeler obligatoirement avant d'accéder aux broches !
void PI_GPIO_config(int port, int mode) {
  int registre, offset, temp;

  // le premier appel lance le mmap (pour pas oublier)
  if (PI_gpio == NULL)
    PI_gpio = PI_IOmmap(GPIO_BASE); // adresse des ports d'entrée-sortie

  if ((port >= 0) && (port < 32) // Works up to 54 but the macros don't handle more than 32 GPIO
   && (mode >= 0) && (mode < 8 )) {
    // Calcul du numéro de registre :
    registre = port/10;

    // lecture dudit registre :
    temp = *(PI_gpio+registre);

    // calcul de l'offset :
    offset = port - (registre*10); // modulo déguisé
    offset *= 3; // 3 bits par port

    // Effacer les bits précédents :
    temp &= ~(7 << offset);
    // ajouter le mode désiré :
    temp |= mode << offset;

    // réécriture du résultat :
    *(PI_gpio+registre) = temp;

#ifndef GPIO_NO_ATEXIT
    if (mode != 0) {
      // enregistrement de la broche pour la désactivation
      if ( GPIO_used == 0 ) {
        atexit(GPIO_parachute);
        // En cas de signal, termine le programme
        // et indirectement appelle GPIO_parachute :
        signal(SIGHUP,  exit);
        signal(SIGINT,  exit);
        signal(SIGQUIT, exit);
        signal(SIGSTOP, exit);
        signal(SIGTERM, exit);
        signal(SIGABRT, exit);
        signal(SIGKILL, exit);
      }
      GPIO_used |= 1UL << port;
    }
#endif
  }
  else {
    fprintf(stderr,"Mauvais numéro de port (%d) ou de mode (%d)\n", port, mode);
    exit(EXIT_FAILURE);
  }
}

#ifndef GPIO_NO_ATEXIT

void GPIO_parachute() {
  unsigned int GPIO_cache = GPIO_used;
  unsigned int mask = 1;
  int i=0;

  fputs("\nSetting pins", stderr);
  while (GPIO_cache) {
    if (GPIO_cache & mask) {
      PI_GPIO_config(i, BCM_GPIO_IN);
      GPIO_cache &= ~mask;
      fprintf(stderr, " %d", i);
    }
    mask += mask; // décalage à gauche
    i++;
  }

  fputs(" as input\n", stderr);
}

#endif

#endif
