/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: MAX7219atmel
 * Ver.: 1.0 Release
 * Type: Executable
 * Text: Demo project for display things
 *       @ 8x8 DOT Matrix with MAX7219
 * -------------------------------------
 */

#define F_CPU 12000000UL	// System clock
#define ATMEL				// Define hardware platform

// Include standard libraries
#include <util/delay.h>

// Include EEPROM library
#include "../../STK500/spi/spi.h"
#include "../MAX7219/max7219.h"

// Characters for 8x8 matrix display
static unsigned char character[][DISPLAY_MATRIX] = {{	0b01100110, 0b10011001, 0b10000001, 0b10000001, 0b10000001, 0b01000010, 0b00100100, 0b00011000	},
													{	0b00111100, 0b01111110, 0b11111111, 0b11111111, 0b11111111, 0b00000000, 0b00011000, 0b00011000	},
													{	0b11111110, 0b11111111, 0b11000000, 0b11111111, 0b11111111, 0b00000011, 0b11111111, 0b01111111	},
													{	0b10000001, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11111111, 0b01111110	},
													{	0b11000001, 0b11100011, 0b11110011, 0b11011011, 0b11011011, 0b11001111, 0b11000111, 0b10000011	},
													{	0b00000000, 0b00000000, 0b00000000, 0b11111110, 0b11111111, 0b11000000, 0b11000000, 0b11000000	},
													{	0b00011000, 0b00011000, 0b00000000, 0b00111100, 0b00011000, 0b00011000, 0b00011000, 0b00111100	},
													{	0b00000000, 0b00000000, 0b00000000, 0b01111110, 0b11111111, 0b11000011, 0b11111111, 0b01111111	},
													{	0b11000011, 0b11100111, 0b01100110, 0b00111100, 0b00111100, 0b01100110, 0b11100111, 0b11000011	}	};

int main(void)
{
	unsigned char intensity = 0x01;	// Variable for setting up display intensity
	max7219_init(intensity);		// Initialize the max7219 item(s)

	// Endless loop
	while (1)
	{
		// Display all characters in array
		for(unsigned char i=0; i < sizeof(character); i++)
		{
			// Transfer data matrix to the display
			max7219_display(character[i], sizeof(character[i]), 1);
			_delay_ms(2000);	// Wait some time before repeating the function
		}
	}	// End of loop
}	// End of main

