# Makefile for atttiny85 devices (apparently)

CC = avr-gcc
CFLAGS = -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

FILE = attiny_lcd_example
C_FILE = $(FILE).c
O_FILE = $(FILE).o
ELF_FILE = $(FILE).elf
HEX_FILE = $(FILE).hex

I2C_H_FILE = attiny_i2c.h
I2C_C_FILE = attiny_i2c.c
I2C_O_FILE = attiny_i2c.o

LCD_H_FILE = attiny_lcd.h
LCD_C_FILE = attiny_lcd.c
LCD_O_FILE = attiny_lcd.o

OBJECTS = $(O_FILE) $(I2C_O_FILE) $(LCD_O_FILE)

DEVICE = attiny85
CLOCK = 8000000
FUSES = -U lfuse:w:0x62:m -U hfuse:2:0xdf:m -U efuse:w:0xff:m
FLASH_ARGS = -c usbtiny

AVRDUDE = avrdude $(FLASH_ARGS) -p $(DEVICE)

$(I2C_O_FILE): $(I2C_C_FILE) $(I2C_H_FILE)
	$(CC) -c $(CFLAGS) $(I2C_C_FILE) -o $(I2C_O_FILE)

$(LCD_O_FILE): $(LCD_C_FILE) $(LCD_H_FILE)
	$(CC) -c $(CFLAGS) $(LCD_C_FILE) -o $(LCD_O_FILE)

$(O_FILE): $(C_FILE)
	$(CC) -c $(CFLAGS) $(C_FILE) -o $(O_FILE)

$(ELF_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(ELF_FILE)

$(HEX_FILE): $(ELF_FILE)
	avr-objcopy -j .text -j .data -O ihex $(ELF_FILE) $(HEX_FILE)
	avr-size --format=avr --mcu=$(DEVICE) $(ELF_FILE)

.PHONY: flash build fuse clean
flash: $(HEX_FILE)
	$(AVRDUDE) -U flash:w:$(HEX_FILE):i

build: $(HEX_FILE)

fuse: 
	$(AVRDUDE) $(FUSES)

clean:
	rm $(HEX_FILE) $(ELF_FILE) $(OBJECTS)
