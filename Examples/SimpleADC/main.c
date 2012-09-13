/*
 * This is a code example using the Analog to Digital converter on a
 * ATmega8/128/328.  This code was build from information obtained
 * from qeekiki (link below) and the example code there was used for
 * refernce.
 *
 * Reference: https://sites.google.com/site/qeewiki/books/avr-guide/analog-input
 */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>


/** Prototypes **/

/* This function will set up the ADC, Digitizes and returns the
 * value. The ADC is used in single read mode using refrence voltage
 * on pin AVcc and the prescale is set for an 8MHz clock. No interupts
 * or anything fancey is used.  */ 

uint8_t read_ADC(uint8_t adcPin);


int main()
{
  // Use PB0 for output to LED.
  DDRB |= _BV(PB0);

  // Used to hold our calculated delay
  // based on LDR input.
  uint16_t delay;

  // no exit stratigy. 
  // simplifies my life.
  for(;;) {

    // Request delay from LDR on pin PC0.
    // and compute delay duration.
    delay = read_ADC(PC0) << 8;

    // Turn LED ON.
    PORTB |= _BV(PB0);

    // Wait for computed delay time.
    _delay_loop_2(delay);
    
    // Turn LED OFF.
    PORTB &= ~_BV(PB0);

    // Wait for computed delay time.
    _delay_loop_2(delay);
  }

  return 0;    
}


/* This function will set up the ADC, Digitizes and returns the
 * value. The ADC is used in single read mode using refrence voltage
 * on pin AVcc and the prescale is set for an 8MHz clock. No interupts
 * or anything fancey is used. */

uint8_t read_ADC(uint8_t adcPin)
{
  uint8_t _iRet;

  // select the pin by setting the Multiplexer channel.
  // Filter to only bottom 4 bits. (sanitized input).
  ADMUX = adcPin & 0x0F;

  // set ADC Data Register to use 8 bit resolution.
  ADMUX |= _BV(ADLAR);

  // Setup voltage refrence to use
  // AVcc with external capacitor on AREF.
  ADMUX |= (1 << REFS0);

  // Dependent on your clock speed, you will need to 
  // set your clock prescale to get any amount of
  // accuracy on the ADC readings. This code assumes
  // you are running on a 8MHz internal clock.
  ADCSRA  = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // 128 Prescale.

  // Enable and Start ADC Conversions
  ADCSRA |= _BV(ADEN);
  ADCSRA |= _BV(ADSC);

  // Wait for the conversion to complete.
  // ADC disables the ADCSC bit once conversion is complete.
  // so we just wait for it to clear.
  while (ADCSRA & _BV(ADSC));
  
  // Only using 8-bit resolution in this example.
  // return the value.
  _iRet = ADCH;

  return _iRet;
}

