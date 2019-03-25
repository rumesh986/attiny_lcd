//	Copyright 2019 Rumesh Sudhaharan

//	This file is part of attiny_lcd.

//	attiny_lcd is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.

//	attiny_lcd is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with attiny_lcd.  If not, see <https://www.gnu.org/licenses/>.

#include <avr/io.h>
#include <util/delay.h>

#include "avr_lcd.h"
#include "avr_i2c.h"

bool backlight_state = true;

void send_instruction(uint8_t rs, uint8_t cmd) {
	uint8_t hbyte, ehbyte;
	uint8_t lbyte, elbyte;
	uint8_t rwrs = 0;

	if (rs)					rwrs |= 0b00000001;
	if (backlight_state)	rwrs |= 0b00001000;

	hbyte = (0xf0 & cmd) | rwrs;
	lbyte = (0xf0 & (cmd<<4)) | rwrs;
	ehbyte = hbyte | 0b00000100;
	elbyte = lbyte | 0b00000100;

	uint8_t byte_str[4] = {hbyte,ehbyte,lbyte,elbyte};

	send_bytes(LCD_ADDR, byte_str, 4);
}

void init_display(void) {
	init_i2c();
	_delay_ms(50);

	uint8_t byte_array[1];

	// Force 4-bit mode for display
	byte_array[0] = 0b00111000;
	send_bytes(LCD_ADDR, byte_array, 1);
	_delay_ms(5);
	send_bytes(LCD_ADDR, byte_array, 1);
	_delay_ms(5);
	send_bytes(LCD_ADDR, byte_array, 1);
	_delay_ms(5);

	byte_array[0] = 0b00101000;
	send_bytes(LCD_ADDR, byte_array, 1);
	_delay_ms(5);
	
	// Configure display for use
	send_instruction(0, 0b00000001);	// Clear display; Set DDRAM Addr to 0
	_delay_ms(2);
	send_instruction(0, 0b00000010);	// Set DDRAM Addr to 0; returns shifted display to original position
	_delay_ms(2);
	send_instruction(0, 0b00001100);	// Set Display: On; Cursor: Off; Cursor Blink: Off
	_delay_us(50);
	send_instruction(0, 0b00011000);	// Set to shift display to left
	_delay_us(50);
	send_instruction(0, 0b00101000);	// Set 4 bit mode; 2 lines display; 5x8 char font
	_delay_us(50);
			
	send_instruction(0, 0b10000000);	// Set Cursor at Start of display
	_delay_us(50);
}

void configure_display(uint8_t cmd) {
	send_instruction(0, cmd);
}

void disp_text(char *str) {
	int i;
	for (i=0;str[i] != '\0'; i++) {
		send_instruction(1, str[i]);
	}
	configure_display(CURSOR_RIGHT);
}

void disp_2line_text(char *str1, char *str2) {
	configure_display(LINE_1);
	_delay_us(50);
	disp_text(str1);

	configure_display(LINE_2);
	_delay_us(50);
	disp_text(str2);
}

void set_backlight(bool state) {
	if (state)	backlight_state = true;
	else		backlight_state = false;
	configure_display(0b00000000);
}

void shift_screen(uint8_t direction, uint8_t count) {
	int i;
	for (i=0; i<count;i++) {
		if (direction == SHIFT_LEFT)		configure_display(SHIFT_LEFT);
		else if (direction == SHIFT_RIGHT)	configure_display(SHIFT_RIGHT);
	}
}