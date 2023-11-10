#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "hcsr04.h"
#include "uart_communication.h"
#include "MCP23017.h"

uint16_t measureDistance() {
        // Send trigger pulse
    Write_MCP23017(GPIOA, Read_MCP23017(GPIOA) | (1 << 6)); 
    _delay_us(10);
    Write_MCP23017(GPIOA, Read_MCP23017(GPIOA) & ~(1 << 6));
    int i = 0;
    bool high = false; 
    unsigned char pinState = Read_MCP23017(GPIOA) & (1 << 7);
    if (pinState)
    {
        high = true; 
    }

    while (high)
    {
       unsigned char pinState = Read_MCP23017(GPIOA) & (1 << 7);
       if (pinState)
       {
            i++;
       }
       else high = false;
    }
    return i; 
    
    // int i = 0 ;
    // while (i < 25){
    // unsigned char pinState = Read_MCP23017(GPIOA) & (1 << 7);
    // if (pinState) {
    //     UART_SendString("Pin is HIGH\n");
    // } else {
    //     UART_SendString("Pin is LOW\n");
    // }
    // i++;
    // }
    

    // // Initialize timer
    // TCNT1 = 0; // Reset timer
    // TCCR1B |= (1 << CS10); // Start timer with no prescaler

    // // Wait for echo pin to go high
    // while (!(Read_MCP23017(GPIOA) & (1 << 7))) {
    //     if (TCNT1 > 50000) { // Timeout condition, adjust as needed
    //         TCCR1B &= ~(1 << CS10); // Stop timer
    //         return 0; // No echo received
    //     }
    // }

    // uint16_t startTime = TCNT1; // Record start time

    // // Wait for echo pin to go low
    // while (Read_MCP23017(GPIOA) & (1 << 7)) {
    //     if (TCNT1 - startTime > 50000) { // Timeout condition, adjust as needed
    //         TCCR1B &= ~(1 << CS10); // Stop timer
    //         return 0; // Echo stayed high too long
    //     }
    // }

    // uint16_t endTime = TCNT1; // Record end time
    // TCCR1B &= ~(1 << CS10); // Stop timer

    // // Calculate echo time (round trip)
    // uint16_t echoTime = endTime - startTime;

    // // Convert echo time to distance (one-way trip)
    // // Using 58 to convert from timer ticks to centimeters
    // uint16_t distance = echoTime / 58 / 2; // Convert to cm

    // return distance;

    // // Initialize timer
    // TCNT1 = 0; // Reset timer
    // TCCR1B |= (1 << CS10); // Start timer with no prescaler

    // // Wait for echo pin to go high
    // while (!(Read_MCP23017(GPIOA) & (1 << 7)) == 0) { // Check GPA7 (echo pin)
    //     if (TCNT1 > 60000) { // Timeout if echo is not received within the expected time
    //         TCCR1B &= ~(1 << CS10); // Stop timer
    //         return 0; // Indicate a timeout occurred
    //     }
    // }

    // // Note the start time
    // uint32_t startTime = TCNT1;

    // // Wait for echo pin to go low
    // while (Read_MCP23017(GPIOA) & (1 << 7)) {
    //     if (TCNT1 - startTime > 60000) { // Timeout if echo stays high too long
    //         TCCR1B &= ~(1 << CS10); // Stop timer
    //         return 0; // Indicate a timeout occurred
    //     }
    // }

    // // Stop timer and calculate echo time
    // uint32_t endTime = TCNT1;
    // TCCR1B &= ~(1 << CS10); // Stop timer
    // uint32_t echoTime = endTime - startTime;

    // // Calculate distance
    // uint16_t distance = (uint16_t)((echoTime / 58.0) / 2); // cm
    // return distance;

    // TCNT1 = 0;
    // TCCR1B |= (1 << CS10);
	// TIFR1 |= (1 << ICF1); // Clear the ICP flag
	// TIFR1 |= (1 << TOV1); // Clear the TOV flag

    // // Wait for the rising edge on the echo pulse
    // while (!(TIFR1 & (1 << ICF1))) {
    //     if (TCNT1 > 50000) {
    //         // If the echo signal is not received within a timeout, exit the loop
    //         TCCR1B &= ~(1 << CS10); // Stop timer
    //         return 0;
    //     }
    // }

    // TCCR1B &= ~(1 << CS10); // Stop timer

    // // Calculate echo time
    // uint16_t echoTime = ICR1;
    // // Convert echo time to distance in cm
    // return (echoTime * 10) / 58;
}
