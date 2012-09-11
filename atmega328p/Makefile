# Generic Source Makefile
# Copywrite 2011 Ian Laird
# Modified on 2012-09-09 for AVR Project.


# The output name.
# This value will be suffixed with .elf and .hex 
# for the debug and output respectivly.
BIN = Count

# Build Targets
PARTN = atmega328p
CLOCK = 1000000Lu

# Comiler settings
CC = avr-gcc
AS = avr-as
OC = avr-objcopy

# Compiler and installer flags.
AVRFLAGS = -P /dev/ttyUSB0 -b 19200 -c avrisp
CFLAGS = -Os -mmcu=$(PARTN) -DF_CPU=$(CLOCK)
ASFLAGS = -mmcu=$(PARTN) -DF_CPU=$(CLOCK)

# Find all source files (c and asm)
OBJ = $(patsubst %.c, %.c.o, $(wildcard *.c)) \
      $(patsubst %.s, %.s.o, $(wildcard *.s))

$(BIN)_$(PARTN).hex : $(BIN)_$(PARTN).elf
	$(OC) -j .text -j .data -O ihex $< $@

$(BIN)_$(PARTN).elf : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.c.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.s.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<


.PHONY : clean install wfuse_m328p

clean :
	$(RM) $(BIN)_$(PARTN).elf $(BIN)_$(PARTN).hex $(OBJ)

install : $(BIN)_$(PARTN).hex
	@echo "avrdude $(AVRFLAGS) -p $(PARTN) -U flash:w:$(BIN)_$(PARTN).hex:i"

wfuse_m328p :
	@echo "avrdude $(AVRFLAGS) -p m328p -U lfuse:w:0x62:m -U hfuse:w:0xd9:m"
