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

#include "attiny_i2c.h"
#include "attiny_lcd.h"

int main(void) {
	init_display();
	disp_2line_text("Hello,", "World!");

	while (1) {};
}
