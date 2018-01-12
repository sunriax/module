/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: MAX7219
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       display things on the MAX7219
 * -------------------------------------
 */

#include "max7219.h"

// Characters for 8x8 matrix display
const unsigned char character[][8] = {	{	0b01100110, 0b10011001, 0b10000001, 0b10000001, 0b10000001, 0b01000010, 0b00100100, 0b00011000	},
										{	0b00111100, 0b01111110, 0b11111111, 0b11111111, 0b11111111, 0b00000000, 0b00011000, 0b00011000	},
										{	0b11111110, 0b11111111, 0b11000000, 0b11111111, 0b11111111, 0b00000011, 0b11111111, 0b01111111	},
										{	0b10000001, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11111111, 0b01111110	},
										{	0b11000001, 0b11100011, 0b11110011, 0b11011011, 0b11011011, 0b11001111, 0b11000111, 0b10000011	},
										{	0b00000000, 0b00000000, 0b00000000, 0b11111110, 0b11111111, 0b11000000, 0b11000000, 0b11000000	},
										{	0b00011000, 0b00011000, 0b00000000, 0b00111100, 0b00011000, 0b00011000, 0b00011000, 0b00111100	},
										{	0b00000000, 0b00000000, 0b00000000, 0b01111110, 0b11111111, 0b11000011, 0b11111111, 0b01111111	},
										{	0b11000011, 0b01100110, 0b00111100, 0b00011000, 0b00011000, 0b00111100, 0b01100110, 0b11000011	}	};

// Frame buffer for
// |   Display 1/1   |   Display 1/2   | Dis...
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// |    Display 2/1  |   Display 2/2   | Dis...
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// |      Dis...     |     Dis...      | Dis...
// | . . . . . . . . | . . . . . . . . | . . . 
// | . . . . . . . . | . . . . . . . . | . . .
// | . . . . . . . . | . . . . . . . . | . . .

static unsigned char max7219_buffer[H_DISPLAY_SIZE][V_DISPLAY_SIZE * DISPLAY_MATRIX];

unsigned char max7219_init(unsigned char intensity)
{
	// Initialize SPI interface
	//        Mode: Master
	//   Direction: MSB First
	//  Phase/Idle: Directly/LOW
	//   Prescaler: F_CPU/2
	unsigned char init = spi_init(0xFF, 0x00, 0x00, 0x01);

	spi_select(0xFF);
	for(unsigned int i=0; i < (H_DISPLAY_SIZE * V_DISPLAY_SIZE); i++)
		max7219_set(MAX7219_DECODE_MODE, MAX7219_DISABLE);
	spi_select(0x00);

	spi_select(0xFF);
	for(unsigned int i=0; i < (H_DISPLAY_SIZE * V_DISPLAY_SIZE); i++)
		max7219_set(MAX7219_SCAN_LIMIT, (DISPLAY_MATRIX - 1));
	spi_select(0x00);
	
	spi_select(0xFF);
	for(unsigned int i=0; i < (H_DISPLAY_SIZE * V_DISPLAY_SIZE); i++)
		max7219_set(MAX7219_INTENSITY, (0x0F & intensity));
	spi_select(0x00);
	
	spi_select(0xFF);
	for(unsigned int i=0; i < (H_DISPLAY_SIZE * V_DISPLAY_SIZE); i++)
		max7219_set(MAX7219_SHUTDOWN, MAX7219_ENABLE);
	spi_select(0x00);
	
	return init;
}

void max7219_set(unsigned char address, const unsigned char data)
{
	spi_transfer(address);
	spi_transfer(data);
}

void max7219_intensity(unsigned char intensity, unsigned char item)
{
	if(item < 1 || item > (H_DISPLAY_SIZE * V_DISPLAY_SIZE))
		return;
	
	spi_select(0xFF);
	
	for(unsigned i=0; i < item; i++)
		if(i == (item - 1))
			max7219_set(MAX7219_INTENSITY, intensity);
		else
			max7219_set(MAX7219_NOP, 0x00);
	
	spi_select(0x00);
		
}

void max7219_frame(unsigned char **frame)
{
	
}

void max7219_display(unsigned char *matrix, unsigned char item)
{

	if(item < 1 || item > (H_DISPLAY_SIZE * V_DISPLAY_SIZE))
		return;

	for(unsigned int i=0; i < 8; i++)
	{
		spi_select(0xFF);
		
		for(unsigned j=0; j < item; j++)
			if(j == (item - 1))
				max7219_set((MAX7219_START_ROW + i), *matrix);
			else
				max7219_set(MAX7219_NOP, 0x00);
		
		spi_select(0x00);
		
		matrix++;
	}
}


