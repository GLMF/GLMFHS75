#include "PI_GPIO.c"

#define PIN_273_SEL (17)  // con.: pin 11

#define PIN_273_DAT0 (22)  // con.: pin 15
#define PIN_273_DAT1 (23)  // con.: pin 16
#define PIN_273_DAT2 (24)  // con.: pin 18
#define PIN_273_DAT3 (25)  // con.: pin 22

volatile unsigned int Dummy;
// délai de 120ns environ :
#define SETTLE  Dummy^=(GPIO_LEV)
// Le xor vers une valeur volatile ne devrait pas être optimisé
// par le compilateur, l'accès aux registres GPIO non plus.
// Attention car la durée dépend aussi des accès précédents
// aux registres d'entrées-sorties, en lecture comme en écriture.

// dure approx. 500ns :
void set_273(unsigned val) {
  // moitié basse
  GPIO_CLR = ( 15        << PIN_273_DAT0);
  GPIO_SET = ((15 & val) << PIN_273_DAT0);
  SETTLE;
  GPIO_SET_N(PIN_273_SEL);
  SETTLE;
  // moitié haute
  GPIO_CLR = ( 15             << PIN_273_DAT0);
  GPIO_SET = ((15 & (val>>4)) << PIN_273_DAT0);
  SETTLE;
  GPIO_CLR_N(PIN_273_SEL);
  SETTLE;
}

void reg_cleanup() {
  set_273(0);
  fputs("\nregistres remis à 0 ", stderr);
}

void reg_init() {
  PI_GPIO_config(PIN_273_SEL,  BCM_GPIO_OUT);
  PI_GPIO_config(PIN_273_DAT0, BCM_GPIO_OUT);
  PI_GPIO_config(PIN_273_DAT1, BCM_GPIO_OUT);
  PI_GPIO_config(PIN_273_DAT2, BCM_GPIO_OUT);
  PI_GPIO_config(PIN_273_DAT3, BCM_GPIO_OUT);
  set_273(0);
  atexit(reg_cleanup);
}