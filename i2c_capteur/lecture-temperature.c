#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#define DS1621_I2C_BUS            "/dev/i2c-1"
#define DS1621_SLAVE_ADDR         0x4F
#define DS1621_ACCESS_CONFIG      0xAC
#define DS1621_START_CONVERT      0xEE
#define DS1621_READ_TEMPERATURE   0xAA
#define DS1621_ONE_SHOT           0x01
#define DS1621_DONE               0x80


int main(int argc, char * argv[])
{
	int fd;
	int value;
	
	// Obtenir l'acces au bus i2c.
	fd = open(DS1621_I2C_BUS, O_RDWR);
	if (fd < 0) {
		perror(DS1621_I2C_BUS);
		exit(EXIT_FAILURE);
	}

	// Fixer l'adresse de l'esclave avec qui communiquer.
	if (ioctl(fd, I2C_SLAVE, DS1621_SLAVE_ADDR) < 0) {
		perror("Slave unreachable");
		exit(EXIT_FAILURE);
	}

	// Lire le registre ACCESS_CONFIG.
	value = i2c_smbus_read_byte_data(fd, DS1621_ACCESS_CONFIG);
	if (value < 0) {
		perror("Read ACCESS_CONFIG");
		exit(EXIT_FAILURE);
	}

	value |= DS1621_ONE_SHOT;

	// Re-ecrire ACCESS_CONFIG
	if (i2c_smbus_write_byte_data(fd, DS1621_ACCESS_CONFIG, value) < 0) {
		perror("Write ACCESS_CONFIG");
		exit(EXIT_FAILURE);
	}
	
	// Demarrer l'acquisition.
	if (i2c_smbus_write_byte(fd, DS1621_START_CONVERT) < 0) {
		perror("Write START_CONVERT");
		exit(EXIT_FAILURE);
	}

	// Attendre qu'une acquisition soit terminee.
	do {
		value = i2c_smbus_read_byte_data(fd, DS1621_ACCESS_CONFIG);
		if (value < 0) {
			perror("Read ACCESS_CONFIG");
			exit(EXIT_FAILURE);
		}
	} while ((value & DS1621_DONE) == 0);

	// Lire la temperature.
	value = i2c_smbus_read_byte_data(fd, DS1621_READ_TEMPERATURE);
        if (value < 0) {
		perror("Read TEMPERATURE");
		exit(EXIT_FAILURE);
	}

	if (value > 127)
		value -= 256;
	fprintf(stdout, "%d\n", value);

	return EXIT_SUCCESS;
}

