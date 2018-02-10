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
#define OUTPUT 0b00000100	// Set output PORT (PORTC)

#define ATMEL				// Define hardware platform

//#define WRITE				// Define to Write Data to EEPROM
#define ADDRESS 0x20		// Define EEPROM register address

// Include standard libraries
#include <util/delay.h>

// Include EEPROM library
#include "../../STK500/port/port.h"
#include "../../STK500/twi/twi.h"
#include "../AT24C02/at24c02.h"

int main(void)
{
	port_init(OUTPUT, 0xFC, 0x00);	// Initialize PORT4(7:2) (PORTC) as OUTPUT
									// Bit(1:0) is used by TWI bus
	
	at24c02_init();	// Initialize the EEPROM
	
	#ifdef WRITE
		
		unsigned char string[] = "This is a secret";	// Save a string into an array
		unsigned char data[] = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0 };	// Save some values into an array
		
		unsigned char result = at24c02_write_string(ADDRESS, string, sizeof(string), 1);	// Write data string to EEPROM and verify data
		//PORTC = at24c02_write_page(ADDRESS, data, sizeof(data), 1);						// Write a page to EEPROM and verify data
		//PORTC = at24c02_write_byte(ADDRESS, 0x0A, 1);										// Write a single byte to EEPROM and verify data
	
		port_write(OUTPUT, (result & 0xFC), 0);		// Write result to PORT4 except bit (1:0)
		
		// Endless loop
		while (1)
		{
		}
	
	#else
	
		unsigned char data[16];														// Buffer for reading data
		unsigned char result = at24c02_read_string(ADDRESS, data, sizeof(data));	// Read data from EEPROM
		
		port_write(OUTPUT, (result & 0xFC), 0);		// Write result to PORT4 except bit (1:0)
		_delay_ms(2000);							// Wait some time that error can be red by user
		
		// Endless loop
		while (1)
		{
			// Display each byte onto PORTC
			for(unsigned char i=0; i < sizeof(data); i++)
			{
				port_write(OUTPUT, (data[i] & 0xFC), 0);		// Write data to PORT4 except bit (1:0)
				_delay_ms(1000);	// Wait some time that user can verify that data that was written is valid
			}
		}	// End of loop
	#endif
}	// End of main

