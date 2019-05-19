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

#ifndef __ATTINY_LCD_H__
#define __ATTINY_LCD_H__

#include <stdbool.h>

#define CLEAR_DISPLAY	0b00000001
#define	HOME_DISPLAY	0b00000010

#define CURSOR_LEFT		0b00010000
#define	CURSOR_RIGHT	0b00010100
#define SHIFT_LEFT		0b00011000
#define	SHIFT_RIGHT		0b00011100

#define LINE_1			0b10000000
#define LINE_2			0b11000000

#define LCD_ADDR		0x20

void init_display(void);
void disp_text(char *str);
void disp_2line_text(char *str1, char *str2);

void set_backlight(bool state);
void shift_screen(uint8_t direction, uint8_t count);

void configure_display(uint8_t cmd);
#endif