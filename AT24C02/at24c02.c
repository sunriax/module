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

void at24c02_init(void)
{
	twi_init(0xFF);
}

unsigned char at24c02_write_byte(unsigned char address, const unsigned char data, unsigned char verify)
{
	unsigned char checksum = TWI_NACK;
	
	if(twi_start() != 0x00)
		return 0xFF;
	if(twi_address(AT24C02_ADDRESS, TWI_WRITE) != 0x00)
		return 0xFF;
	if(twi_set(address) != 0x00)
		return 0xFF;
	if(twi_set(data) != 0x00)
		return 0xFF;
	
	twi_stop();
	
	_delay_us(1500);
	
	if(verify != 0x00)
	{
		if(twi_start() != 0x00)
			return 0xF0;
		if(twi_address(AT24C02_ADDRESS, TWI_READ) != 0x00)
			return 0xF0;
		if(twi_get(&checksum) != 0x00)
			return 0xF0;
			
		twi_stop();
		
		if(checksum != data)
			return 0xFF;
	}
	return 0x00;
}

unsigned char at24c02_write_page(unsigned char address, unsigned char *page, unsigned char length, unsigned char verify)
{
	if(length > AT24C02_PAGE_SIZE)
		return 0x01;
	
	if(twi_start() != 0x00)
		return 0xFF;
	if(twi_address(AT24C02_ADDRESS, TWI_WRITE) != 0x00)
		return 0xFF;
	if(twi_set(address) != 0x00)
		return 0xFF;
	
	for(unsigned char i=0; i < length; i++)
	{
		if(twi_set(*page) != 0x00)
			return 0xFF;
		
		page++;
	}
	
	twi_stop();
	
	_delay_us(1500);
	
	if(verify != 0x00)
	{
		unsigned char checksum[length];
		
		if(at24c02_read_string(address, checksum, length) != 0x00)
			return 0xF0;
		
		for(unsigned char i=0; i < length; i++)
			if(page[i] != checksum[i])
				return 0xF0;
	
	}
	return 0x00;
}

unsigned char at24c02_write_string(unsigned char address, unsigned char *data, unsigned char length, unsigned char verify)
{
	if((length > AT24C02_BYTE_SIZE) || (address >= AT24C02_BYTE_SIZE))
		return 0xFF;
	
	for(unsigned char i=0; i < length; i++)
	{
		if(at24c02_write_byte(address, *data, verify) != 0x00)
			return 0xFF;
		
		if(address >= AT24C02_BYTE_SIZE)
			address = 0;
		else
			address++;
		
		data++;
	}
	
	return 0x00;
}

unsigned char at24c02_read_byte(unsigned char address, unsigned char *data)
{
	unsigned char buffer[1];
	
	if(at24c02_read_string(address, buffer, 1) != 0x00)
		return 0xFF;
	
	*data = buffer[0];
	
	return 0x00;
}

unsigned char at24c02_read_string(unsigned char address, unsigned char *data, unsigned char length)
{
	if(length > AT24C02_BYTE_SIZE)
		return 0x01;
		
	if(twi_start() != 0x00)
		return 0xFF;
	if(twi_address(AT24C02_ADDRESS, TWI_WRITE) != 0x00)
		return 0xFF;
	if(twi_set(address) != 0x00)
		return 0xFF;
	if(twi_start() != 0x00)
		return 0xFF;
	if(twi_address(AT24C02_ADDRESS, TWI_READ) != 0x00)
		return 0xFF;
		
	for(unsigned char i=0; i < length; i++)
	{
		if(i >= (length - 1))
			*data = TWI_NACK;
		else
			*data = TWI_ACK;
		
		if(twi_get(data) != 0x00)
			return 0xFF;
		
		if(length > 1)
			data++;
	}
	
	twi_stop();
	
	return 0x00;
}


