#include <avr/io.h>
#include <compat/twi.h>
#include "MCP23017.h"
#include "i2c.h"

void Write_MCP23017(unsigned char reg_addr, unsigned char data)
{
	i2c_start(MCP23017_ID, 0x00, TW_WRITE);
	i2c_write(reg_addr);
	i2c_write(data);
	i2c_stop();
}

unsigned char Read_MCP23017(unsigned char reg_addr)
{
	char data;
	// Start the I2C Write Transmission
	i2c_start(MCP23017_ID,MCP23017_ADDR,TW_WRITE);
	// Read data from MCP23008 Register Address
	i2c_write(reg_addr);
	// Stop I2C Transmission
	i2c_stop();

	// Re-Start the I2C Read Transmission
	i2c_start(MCP23017_ID,MCP23017_ADDR,TW_READ);
	i2c_read(&data,NACK);

	// Stop I2C Transmission
	i2c_stop();

	return data;
}

void MCP23017_INIT() {
	Write_MCP23017(IODIRA, 0b10111111);
}