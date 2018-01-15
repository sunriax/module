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
 *       read/write to I2C EEPROM
 * -------------------------------------
 */

#include "at24c02.h"

//	+---------------------------------------------------------------+
//	|					AT24C02 initialization						|
//	+---------------------------------------------------------------+
void at24c02_init(void)
{
	twi_init(0xFF);	// Initialize TWI as master
}

//	+---------------------------------------------------------------+
//	|					AT24C02 write byte							|
//	+---------------------------------------------------------------+
unsigned char at24c02_write_byte(unsigned char address, const unsigned char data, unsigned char verify)
{
	// Check TWI start transmission for errors
	if(twi_start() != 0x00)
		return 0x0F;
	// Check TWI select address for errors
	if(twi_address(AT24C02_ADDRESS, TWI_WRITE) != 0x00)
		return 0x1F;
	// Check TWI select EEPROM register for errors
	if(twi_set(address) != 0x00)
		return 0x2F;
	// Check TWI write data byte for errors
	if(twi_set(data) != 0x00)
		return 0x3F;
	
	twi_stop();			// Stop TWI transmission
	
	_delay_us(1500);	// Wait until Data is written to the EEPROM
						// (see datasheet for more information)
	
	// Check if written data should be verified
	if(verify != 0x00)
	{
		unsigned char checksum = TWI_NACK;	// Set NOT acknowledge to the checksum data byte
		
		// Check TWI read byte for errors
		if(at24c02_read_byte(address, &checksum) != 0x00)
			return 0xFF;
		
		// Check if written byte is equal to received data byte
		if(checksum != data)
			return 0x3F;	// Return that data byte is not equal
	}
	return 0x00;	// Return that everything is ok
}

//	+---------------------------------------------------------------+
//	|					AT24C02 write page							|
//	+---------------------------------------------------------------+
unsigned char at24c02_write_page(unsigned char address, unsigned char *page, unsigned char length, unsigned char verify)
{
	// Check if length is greater than page size
	if(length > AT24C02_PAGE_SIZE)
		return 0x01;	// Return that command was not executed
	
	// Check TWI start transmission for errors
	if(twi_start() != 0x00)
		return 0x0F;
	// Check TWI select address for errors
	if(twi_address(AT24C02_ADDRESS, TWI_WRITE) != 0x00)
		return 0x1F;
	// Check TWI select EEPROM register for errors
	if(twi_set(address) != 0x00)
		return 0x2F;
	
	// Run page transmission
	for(unsigned char i=0; i < length; i++)
	{
		// Check TWI write page for errors
		if(twi_set(page[i]) != 0x00)
			return 0x3F;
	}
	twi_stop();	// Stop TWI transmission
	
	_delay_us(1500);	// Wait until Data is written to the EEPROM
						// (see datasheet for more information)	
	
	// Check if written data should be verified
	if(verify != 0x00)
	{
		unsigned char checksum[length];	// Checksum data array for reveiving data
		
		// Check TWI read data string for errors
		if(at24c02_read_string(address, checksum, length) != 0x00)
			return 0xF0;
		
		// Run page transmission
		for(unsigned char i=0; i < length; i++)
			// Check if written byte is equal to received data byte
			if(page[i] != checksum[i])
				return 0xF3;
	}
	return 0x00;	// Return that everything is ok
}

//	+---------------------------------------------------------------+
//	|					AT24C02 write string						|
//	+---------------------------------------------------------------+
unsigned char at24c02_write_string(unsigned char address, unsigned char *data, unsigned char length, unsigned char verify)
{
	// Check if length is greater than EEPROM byte size and if address is greater than EEPROM byte size
	if((length > AT24C02_BYTE_SIZE) || (address >= (AT24C02_BYTE_SIZE - 1)))
		return 0xFF;
	
	// Run string transmission
	for(unsigned char i=0; i < length; i++)
	{
		// Check TWI write byte for errors
		if(at24c02_write_byte(address, *data, verify) != 0x00)
			return 0xFF;
		
		// Check if address is greater than EEPROM register size
		if(address >= (AT24C02_BYTE_SIZE - 1))
			address = 0;	// Set address to EEPROM register start address
		else
			address++;		// Increment address variable
		
		data++;	// Increment data array
	}
	return 0x00;	// Return that everything is ok
}

//	+---------------------------------------------------------------+
//	|					AT24C02 read byte							|
//	+---------------------------------------------------------------+
unsigned char at24c02_read_byte(unsigned char address, unsigned char *data)
{
	unsigned char buffer[1];	// Create a buffer with one data byte
	
	// Check TWI read string for errors
	if(at24c02_read_string(address, buffer, 1) != 0x00)
		return 0xFF;
	
	*data = buffer[0];	// Write data buffer byte to data
	
	return 0x00;	// Return that everything is ok
}

//	+---------------------------------------------------------------+
//	|					AT24C02 read string							|
//	+---------------------------------------------------------------+
unsigned char at24c02_read_string(unsigned char address, unsigned char *data, unsigned char length)
{
	// Check if length is greater than EEPROM byte size
	if(length > AT24C02_BYTE_SIZE)
		return 0x01;
	
	// Check TWI start transmission for errors
	if(twi_start() != 0x00)
		return 0x0F;
	// Check TWI select address for errors
	if(twi_address(AT24C02_ADDRESS, TWI_WRITE) != 0x00)
		return 0x1F;
	// Check TWI select EEPROM register for errors
	if(twi_set(address) != 0x00)
		return 0x2F;
	// Check TWI repeated start transmission for errors
	if(twi_start() != 0x00)
		return 0x0F;
	// Check TWI select address for errors
	if(twi_address(AT24C02_ADDRESS, TWI_READ) != 0x00)
		return 0x1F;
	
	// Run string transmission
	for(unsigned char i=0; i < length; i++)
	{
		// Check if last byte has to be transmitted
		if(i >= (length - 1))
			*data = TWI_NACK;	// Write NOT acknowledge to data
		else
			*data = TWI_ACK;	// Write acknowledge to data
		
		// Check TWI read data byte for errors
		if(twi_get(data) != 0x00)
			return 0xFF;
		
		// Check if length is greater 1
		if(length > 1)
			data++;	// Increment data
	}
	twi_stop();		// Stop TWI transmission
	
	return 0x00;	// Return that everything is ok
}


