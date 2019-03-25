//	Copyright 2019 Rumesh Sudhaharan

//	This file is part of attiny_i2c.

//	attiny_i2c is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.

//	attiny_i2c is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with attiny_i2c.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __AVR_I2C_H__
#define __AVR_I2C_H__

#include <stdlib.h>

#define SDA	PB0
#define SCL	PB2

void init_i2c(void);
uint8_t send_bytes(uint8_t address, uint8_t *bytes, size_t size);

#endif