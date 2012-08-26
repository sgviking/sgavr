#include <avr/io.h>     
#include <util/delay.h>

// This program will use different bit shifting techniques
// to loop through the LED lights.

int main(void)
{
	// Makes PB1-5 output pins
	DDRB = 0b00011111;
	int pin_pattern = 0b00000001;
	int i;

	while (1)
	{
		// Left shift through the outputs
		/*for (i=0; i<5; i++) {
			PORTB = pin_pattern;
			pin_pattern <<= 1;
			_delay_ms(150);
			PORTB = 0b00000000;
			_delay_ms(150);
		}*/

		/*pin_pattern = 0b00010000;

		// Right shift through the outputs
		for (i=0; i<5; i++) {
			PORTB = pin_pattern;
			pin_pattern >>= 1;
			_delay_ms(150);
			PORTB = 0b00000000;
			_delay_ms(150);
		}*/

		// Twiddle (flip) some bits
		pin_pattern = 0b00010101;

		PORTB = pin_pattern;
		_delay_ms(250);
		PORTB = ~pin_pattern;
		_delay_ms(250);
		PORTB = pin_pattern;
		_delay_ms(250);
		PORTB = ~pin_pattern;
		_delay_ms(150);
	
		pin_pattern = 0b00000001;
		
		//asm volatile 
		//(
		//	"rol %0\n\t" : "=d" (pin_pattern) : "0" (pin_pattern)
		//);
	}
	
	return 1;
}
