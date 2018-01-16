/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: AT24C02atmel
 * Ver.: 1.0 Release
 * Type: Executeable
 * Text: Demo project for r/w things
 *       @ I2C EEPROM AT24C02
 * -------------------------------------
 */

#define F_CPU 12000000UL	// System clock
#define ATMEL				// Use ATMEL library

//#define WRITE				// Define to Write Data to EEPROM
#define ADDRESS 0x20

// Include standard libraries
#include <util/delay.h>

// Include EEPROM library
#include "../AT24C02/at24c02.h"

int main(void)
{
	DDRC = 0xFC;
	
	at24c02_init();
	
	#ifdef WRITE
		
		unsigned char data[] = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0 };
		PORTC = at24c02_write_string(ADDRESS, data, sizeof(data), 1);
		//PORTC = at24c02_write_page(ADDRESS, data, sizeof(data), 1);
		//PORTC = at24c02_write_byte(ADDRESS, 0x0A, 1);
	
		while (1)
		{
		}
	
	#else
	
		unsigned char data[10];
	
		while (1)
		{
			for(unsigned char i=0; i < sizeof(data); i++)
			{
				at24c02_read_string(ADDRESS, data, sizeof(data));
				PORTC = (data[i]);
				_delay_ms(1000);
			}
		}	// End of loop
	#endif
}	// End of main

