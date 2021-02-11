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

// Define for 16MHz clock cycle.
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

// Utilties for configuring interrupts.
#define RSNG_EDG 0b011
#define SET_INTTYPE(ctrlr,n,f) (ctrlr |= (f << (n*2)))
#define SET_INTERRUPT(msk,n) (msk |= (1 << n))

#define DELAY_MIN 1
#define DELAY_MAX 20
#define CLOCK_DELAY 10

/** Global Includes **/

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

/** Global Variables **/

/*
 * Volatile Storage for main loop delay.
 * Volatile will keep GCC from optimizing away
 * our shared memory.
 */

volatile uint_fast8_t __dc = DELAY_MAX / 2;


/** PROTOTYPES **/

/*
 * Initialize all IO port direction.
 */

void ioinit(void);

/*
 * Initialize hardware interrupts.
 * This function does NOT set the global
 * interrupt flag.
 */

void isrinit(void);

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

  // Initialize and enable hardware interrupts.

  isrinit();
  sei();

  // Loop through all values of i and
  // set on PortC.

  uint_fast8_t i, dc;
  for(i = 0; ; PORTC = i++ & 0x0F) {

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      dc = __dc;
    }

    do {
      _delay_ms(CLOCK_DELAY);
    } while(dc--);

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


/*
 * Initialize hardware interrupts.
 * This function does NOT set the global
 * interrupt flag.
 */

void isrinit(void)
{
  // Set ISR 0 and 1 to trigger on rising edge.
  SET_INTTYPE(EICRA, 0, RSNG_EDG);
  SET_INTTYPE(EICRA, 1, RSNG_EDG);

  // Enable ISR 0 and 1.
  SET_INTERRUPT(EIMSK, 0);
  SET_INTERRUPT(EIMSK, 1);
}

ISR(INT0_vect)
{
  if(__dc < DELAY_MAX)
    __dc++;
}

ISR(INT1_vect)
{
  if(__dc > DELAY_MIN)
    __dc--;
}
