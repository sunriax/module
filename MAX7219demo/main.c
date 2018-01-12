/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 *           rPI/Arietta G25
 * Platform: ATmega8/16/32
 *           ARM uC
 * -------------------------------------
 * Name: MAX7219demo
 * Ver.: 1.0 Release
 * Type: Executable
 * Text: Demo project for display things
 *       on MAX7219 8x8 DOT Matrix
 * -------------------------------------
 */

#define STK500

#ifdef STK500
	#define F_CPU 12000000UL

	#include <util/delay.h>

	#include "../../STK500/spi/spi.h"
#endif

#include "../MAX7219/max7219.h"

extern unsigned char character[][8];

int main(void)
{
	unsigned char intensity = 0x01;

	max7219_init(intensity);

	while (1)
	{
		for(unsigned char i=0; i < 9; i++)
		{
			max7219_display(character[i], 1);
			_delay_ms(2000);
		}
	}
}

