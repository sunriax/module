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
 *       write things on the MAX7219
 * -------------------------------------
 */

#include "max7219.h"

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

void max7219_display(unsigned char *matrix, unsigned char length, unsigned char item)
{

	if(item < 1 || item > (H_DISPLAY_SIZE * V_DISPLAY_SIZE))
		return;

	for(unsigned int i=0; i < length; i++)
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

// Matrix frame example
// |    Matrix 0     |    Matrix 1     | Mat...
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// |    Matrix 2     |    Matrix 3     | Mat...
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// | X X X X X X X X | X X X X X X X X | . . .
// |      Mat...     |     Mat...      | Mat...
// | . . . . . . . . | . . . . . . . . | . . .
// | . . . . . . . . | . . . . . . . . | . . .
// | . . . . . . . . | . . . . . . . . | . . .

void max7219_cascade(unsigned char **matrix, unsigned char matrix_width, unsigned char matrix_height)
{
	if((matrix_width < 1) || (matrix_height > (H_DISPLAY_SIZE)) || (matrix_height < 1) || (matrix_width > (V_DISPLAY_SIZE)))
		return;

	for(unsigned int i=(matrix_height - 1); i >= 0; i--)
	{
		spi_select(0xFF);
		
		for(unsigned int j=(matrix_width - 1); j >= 0; j--)
		{
			max7219_set((MAX7219_START_ROW + i), matrix[i][j]);
		}
		
		spi_select(0x00);
	}
}


