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

#ifndef MAX7219_H_
#define MAX7219_H_

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! DEFINE ONLY FOR COMPILING THE LIBRARY !!!
#ifndef ATMEL
	#define ATMEL
#endif
// !!! #define LINUX                         !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef DISPLAY_MATRIX	// Display Size (8x8)
	#define DISPLAY_MATRIX 8
#endif

#ifndef H_DISPLAY_SIZE	// Horizontal LED matrix panels
	#define H_DISPLAY_SIZE 1
#endif

#ifndef V_DISPLAY_SIZE	// Vertical LED matrix panels
	#define V_DISPLAY_SIZE 1
#endif

#ifndef MAX7219_REGISTER
	#define MAX7219_REGISTER
	
	#define MAX7219_NOP         0x00
	#define MAX7219_START_ROW   0x01
	#define MAX7219_DECODE_MODE 0x09
	#define MAX7219_INTENSITY   0x0A
	#define MAX7219_SCAN_LIMIT  0x0B
	#define MAX7219_SHUTDOWN    0x0C
	
	#define MAX7219_ENABLE 0x01
	#define MAX7219_DISABLE 0x00
#endif

#ifdef ATMEL
	#include "../../STK500/spi/spi.h"
#endif

unsigned char max7219_init(unsigned char intensity);
         void max7219_set(unsigned char address, const unsigned char data);
         void max7219_intensity(unsigned char intensity, unsigned char item);
		 void max7219_frame(unsigned char **frame);
         void max7219_display(unsigned char *matrix, unsigned char item);

#endif /* MAX7219_H_ */