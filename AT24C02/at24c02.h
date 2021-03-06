/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: AT24C02
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       read/write to TWI EEPROM
 * -------------------------------------
 */

#ifndef AT24C02_H_
#define AT24C02_H_

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! DEFINE ONLY FOR COMPILING THE LIBRARY !!!
#ifndef ATMEL
	#define ATMEL
#endif
// !!! #define LINUX                         !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef F_CPU				// System clock
	#define F_CPU 12000000UL
#endif

#ifndef F_TWI				// TWI clock
	#define F_TWI 400000UL
#endif

#ifndef AT24C02_ADDRESS		// TWI EEPROM address
	#define AT24C02_ADDRESS 0b01010000
#endif

#ifndef AT24C02_BYTE_SIZE	// Size of EEPROM memory
	#define AT24C02_BYTE_SIZE 128
#endif

#ifndef AT24C02_PAGE_SIZE	// Size of EEPROM page
	#define AT24C02_PAGE_SIZE 16
#endif

#include <util/delay.h>

#ifdef ATMEL
	#include "../../STK500/twi/twi.h"
#endif

         void at24c02_init(void);
unsigned char at24c02_write_byte(unsigned char address, const unsigned char data, unsigned char verify);
unsigned char at24c02_write_page(unsigned char address, unsigned char *page, unsigned char length, unsigned char verify);
unsigned char at24c02_write_string(unsigned char address, unsigned char *data, unsigned char length, unsigned char verify);
unsigned char at24c02_read_byte(unsigned char address, unsigned char *data);
unsigned char at24c02_read_string(unsigned char address, unsigned char *data, unsigned char length);

#endif /* AT24C02_H_ */