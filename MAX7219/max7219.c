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

//	+---------------------------------------------------------------+
//	|						MAX7219 initialization					|
//	+---------------------------------------------------------------+
unsigned char max7219_init(unsigned char intensity)
{
	// Initialize SPI interface
	//        Mode: Master
	//   Direction: MSB First
	//  Phase/Idle: Directly/LOW
	//   Prescaler: F_CPU/2
	unsigned char init = spi_init(0xFF, 0x00, 0x00, 0x01);

	spi_select(0xFF);	// Slave Select LOW
	// Disable decode mode for all displays
	for(unsigned int i=0; i < (H_DISPLAY_SIZE * V_DISPLAY_SIZE); i++)
		max7219_set(MAX7219_DECODE_MODE, MAX7219_DISABLE);
	spi_select(0x00);	// Slave Select HIGH

	spi_select(0xFF);	// Slave Select LOW
	// Set scan limit to display dots - 1 for all displays
	for(unsigned int i=0; i < (H_DISPLAY_SIZE * V_DISPLAY_SIZE); i++)
		max7219_set(MAX7219_SCAN_LIMIT, (DISPLAY_MATRIX - 1));
	spi_select(0x00);	// Slave Select HIGH
	
	spi_select(0xFF);	// Slave Select LOW
	// Set intensity for all displays
	for(unsigned int i=0; i < (H_DISPLAY_SIZE * V_DISPLAY_SIZE); i++)
		max7219_set(MAX7219_INTENSITY, (0x0F & intensity));
	spi_select(0x00);	// Slave Select HIGH
	
	spi_select(0xFF);	// Slave Select LOW
	// Disable shutdown mode on all displays
	for(unsigned int i=0; i < (H_DISPLAY_SIZE * V_DISPLAY_SIZE); i++)
		max7219_set(MAX7219_SHUTDOWN, MAX7219_ENABLE);
	spi_select(0x00);	// Slave Select HIGH
	
	return init;
}

//	+---------------------------------------------------------------+
//	|						MAX7219 transfer data					|
//	+---------------------------------------------------------------+
void max7219_set(unsigned char address, const unsigned char data)
{
	spi_transfer(address);	// Transfer address byte
	spi_transfer(data);		// Transfer data byte
}

//	+---------------------------------------------------------------+
//	|						MAX7219 intensity						|
//	+---------------------------------------------------------------+
void max7219_intensity(unsigned char intensity, unsigned char item)
{
	// Check if there are items (displays) defined
	if(item < 1 || item > (H_DISPLAY_SIZE * V_DISPLAY_SIZE))
		return;
	
	spi_select(0xFF);	// Slave Select LOW
	
	// Setup intensity for selected items
	for(unsigned i=0; i < item; i++)
		// Check if selected item has been reached
		if(i == (item - 1))
			max7219_set(MAX7219_INTENSITY, intensity);	// Set intensity on the item
		else
			max7219_set(MAX7219_NOP, 0x00);				// Set no operation on other items
	
	spi_select(0x00);	// Slave Select HIGH
}

//	+---------------------------------------------------------------+
//	|						MAX7219 display							|
//	+---------------------------------------------------------------+
void max7219_display(unsigned char *matrix, unsigned char length, unsigned char item)
{
	// Check if there are items (displays) defined
	if(item < 1 || item > (H_DISPLAY_SIZE * V_DISPLAY_SIZE))
		return;
	
	// Setup data for selected items
	for(unsigned int i=0; i < length; i++)
	{
		spi_select(0xFF);	// Slave Select LOW
		
		// Loop through the items for each single data byte
		for(unsigned j=0; j < item; j++)
			// Check if selected item has been reached
			if(j == (item - 1))
				max7219_set((MAX7219_START_ROW + i), matrix[j]);	// Set data for selected line on item
			else
				max7219_set(MAX7219_NOP, 0x00);						// Set no operation on other items
		
		spi_select(0x00);	// Slave Select HIGH
	}
}

//	+---------------------------------------------------------------+
//	|						MAX7219 cascade							|
//	+---------------------------------------------------------------+

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
	// Check if there are items (displays) defined
	if((matrix_width < 1) || (matrix_height > (H_DISPLAY_SIZE)) || (matrix_height < 1) || (matrix_width > (V_DISPLAY_SIZE)))
		return;

	// Start with last matrix lines
	for(unsigned int i=(matrix_height - 1); i >= 0; i--)
	{
		spi_select(0xFF);	// Slave Select LOW
		
		// Loop through the items (displays)
		for(unsigned int j=(matrix_width - 1); j >= 0; j--)
			max7219_set((MAX7219_START_ROW + i), matrix[i][j]);	// Set data for selected line on item
		
		spi_select(0x00);	// Slave Select HIGH
	}
}


