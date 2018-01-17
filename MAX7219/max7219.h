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

#ifndef MAX7219_H_
#define MAX7219_H_

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! DEFINE ONLY FOR COMPILING THE LIBRARY !!!
#ifndef ATMEL
	#define ATMEL
#endif
// !!! #define LINUX                         !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef DISPLAY_MATRIX		// Display Size (8x8)
	#define DISPLAY_MATRIX 8
#endif

#ifndef H_DISPLAY_SIZE		// Horizontal LED matrix panels
	#define H_DISPLAY_SIZE 1
#endif

#ifndef V_DISPLAY_SIZE		// Vertical LED matrix panels
	#define V_DISPLAY_SIZE 1
#endif

// MAX7219 register codes (!!! Do not change !!!)
#ifndef MAX7219_REGISTER
	#define MAX7219_REGISTER
	
	#define MAX7219_NOP          0x00	// No Operation
	#define MAX7219_START_ROW    0x01	// Start ROW (Digit 0)
	#define MAX7219_DECODE_MODE  0x09	// Code B font (only for 7 Segment necessary)
	#define MAX7219_INTENSITY    0x0A	// Intensity operation
	#define MAX7219_SCAN_LIMIT   0x0B	// Scan limit operation
	#define MAX7219_SHUTDOWN     0x0C	// Shutdown operation
	#define MAX7219_DISPLAY_TEST 0x0F	// Test the display
	
	#define MAX7219_ENABLE 0x01			// Enabling MAX7219
	#define MAX7219_DISABLE 0x00		// Disabling MAX7219
#endif

// Platform selector
#ifdef ATMEL
	#include "../../STK500/spi/spi.h"
#else
	// Other platform (not available @ the moment)
#endif

unsigned char max7219_init(unsigned char intensity);
         void max7219_set(unsigned char address, const unsigned char data);
         void max7219_intensity(unsigned char intensity, unsigned char item);
         void max7219_display(unsigned char *matrix, unsigned char length, unsigned char item);
         void max7219_cascade(unsigned char **matrix, unsigned char matrix_width, unsigned char matrix_height);

#endif /* MAX7219_H_ */