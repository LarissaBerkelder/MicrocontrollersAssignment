#define F_CPU 16000000UL
#define BAUD 9600
#define BAUDRATE ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <compat/twi.h>
#include <stdbool.h>
#include <stdio.h>

#include "uart_communication.h"
#include "i2c.h"
#include "MCP23017.h"
#include "hcsr04.h"

int main(void) {
  UART_INIT(BAUDRATE);
  I2C_INIT();
  MCP23017_INIT();

    unsigned char ioDir = Read_MCP23017(IODIRA);
    ioDir |= (1 << 7);  // Configure GPA7 as input
    Write_MCP23017(IODIRA, ioDir);
    unsigned char gppu = Read_MCP23017(GPPUA);
    gppu |= (1 << 7);  // Enable pull-up on GPA7
    Write_MCP23017(GPPUA, gppu);

  //UART_SendString("Ready to measure distance\n");

  // while (1) {
  //       // Read the state of the pin
  //       unsigned char pinState = Read_MCP23017(GPIOA) & (1 << 7);

  //       // Send the pin state over USART
  //       if (pinState) {
  //           UART_SendString("Pin is HIGH\n");
  //       } else {
  //           UART_SendString("Pin is LOW\n");
  //       }

  //       // Simple debounce delay
  //       _delay_ms(500); // Adjust delay as needed
  //   }
	while (1) {

    _delay_ms(100);
    uint16_t distance = measureDistance();
    char buffer[10];
    sprintf(buffer, "%d\n", distance); 
    UART_SendString(buffer);
    _delay_ms(1000);
	}
	
	return 0;
}