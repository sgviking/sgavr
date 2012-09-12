BIN = adc

MCU = atmega328p
CLOCK = 10000000Lu

CC = avr-gcc
AS = avr-as
OC = avr-objcopy

AVRFLAGS = -P /dev/ttyUSB0 -b 19200 -c avrisp
CFLAGS = -Os -mmcu=$(MCU) -DF_CPU=$(CLOCK) -std=c99
ASFLAGS = -mmcu=$(MCU) -DF_CPU=$(CLOCK)

OBJ = $(patsubst %.c, %.c.o, $(wildcard *.c)) \
      $(patsubst %.s, %.s.o, $(wildcard *.s))

$(BIN)_$(MCU).hex : $(BIN)_$(MCU).elf
	$(OC) -j .text -j .data -O ihex $< $@

$(BIN)_$(MCU).elf : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.c.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.s.o : %.s
	$(AS) $(ASFLAGS) -o $@ $<

.PHONY : clean install wfuse_internal_1mhz_m328p

clean : 
	$(RM) $(BIN)_$(MCU).{elf,hex} $(OBJ)

install : $(BIN)_$(MCU).hex
	@echo "avrdude $(AVRFLAGS) -p $(MCU) -U flash:w:$(BIN)_$(MCU).hex:i"

# this is hardware specific so the part is hardcoded in.
# to execute this you must run make as a return string.
wfuse_internal_1mhz_m328p :
	@echo "avrdude $(AVRFLAGS) -p m328p -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0x07:m"
