#!/bin/bash

# Compile instructions for ATTiny45
avr-gcc -mmcu=attiny45 -DF_CPU=1234567Lu bitwiseled.c -o bitwiseled.o
avr-objcopy -j .text -j .data -O ihex bitwiseled.o bitwiseled.hex

# Write to the flash on the ATTiny45
sudo avrdude -c usbtiny -p t45 -U flash:w:bitwiseled.hex

# Clean up object file
rm bitwiseled.o
