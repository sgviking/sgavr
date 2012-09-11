/*
 * count_1mhz.c 
 * This program puts an eight bit 
 * value in binary on ports C0 - C3.
 *
 * Copywrite 2012 Ian Laird.
 */


/*
 * Our delay function is dependent on
 * the microcontroler frequency. If it
 * was not defined on the comand line,
 * define it here.
 */

#ifndef F_CPU

// Define for 1MHz clock cycle.
#define F_CPU 1000000UL

#endif

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

/** PROTOTYPES **/

/*
 * Initialize all IO port direction.
 */

void ioinit(void);

/*
 * Entry point containing main loop.
 */

int main (void)
{
  // Initialize IO Direction.

  ioinit();

  // Turn off all outputs.

  PORTB = 0x00;
  PORTD = 0x00;


  // Loop through all values of i and
  // set on PortC.

  uint_fast8_t i;
  for(i = 0; ; PORTC = i++ & 0x0F) {
    _delay_ms(250);
  }

  return 0;
}


/*
 * Initialize all IO port direction.
 */

void ioinit (void)
{
  // All ports for output for this example.
  DDRB = 0b11111111;
  DDRC = 0b11111111;
  
  // RXD for serial read on PD0 is input
  DDRD = 0b11111110;
}
