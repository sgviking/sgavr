#include <avr/io.h>     
#include <util/delay.h>

// This program will use different bit shifting techniques
// to loop through the LED lights.
flash(int output_pins, int amount, int delay)
{
	int i;
	while (i < amount)
	{
		// On
		PORTB = output_pins;
    		_delay_ms(delay);
    		// Off
         	PORTB = 0b00000000;
		_delay_ms(200);
		i++;
	}
}

int main(void)
{
	// Makes PB1-5 output pins
	int output_pins = output_pins = 0b00011111;

	flash(output_pins, 3, 200);

	while (1)
	{
		asm volatile ("rol %0\n\t" : "=d" (output_pins) : "0" (output_pins));
		
		flash(output_pins, 2, 300);
	}
	
	return 1;
}
