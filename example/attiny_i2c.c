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


#include <avr/io.h>
#include <util/delay.h>

// #include <stdbool.h>
#include <stdlib.h>

#include "avr_i2c.h"

void init_i2c(void) {
	// Initial condition for SDA and SCL lines | both are high
	DDRB |= (1<<SDA | 1<<SCL);
	PORTB |= (1<<SDA | 1<<SCL);
	_delay_us(10);
}

int send_byte(uint8_t byte) {
	int i;
	for (i=7; i>=0; i--) {
		if (byte & (1<<i))	PORTB |= (1<<SDA);
		else				PORTB &= ~(1<<SDA);
		_delay_us(3);

		PORTB |= (1<<SCL);
		_delay_us(5);
		PORTB &= ~(1<<SCL);
		_delay_us(2);
	}
	//Check for ACK
	DDRB &= ~(1<<SDA);
	_delay_us(3);

	PORTB |= (1<<SCL);
	_delay_us(5);
	uint8_t ack = PINB & (1<<SDA);
	PORTB &= ~(1<<SCL);
	_delay_us(2);

	// Ends message with SDA and SCL on high
	DDRB |= (1<<SDA);

	return ack;
}

uint8_t send_bytes(uint8_t address, uint8_t *bytes, size_t size) {
	uint8_t ret_code = 0;
	// Set up initial conditions for i2c communication
	PORTB |= (1<<SDA);
	_delay_us(2);
	PORTB |= (1<<SCL);
	_delay_us(2);

	// START condition
	PORTB &= ~(1<<SDA);
	_delay_us(3);
	PORTB &= ~(1<<SCL);

	int ack = 0;

	// Send address in read mode
	ack = send_byte(address<<1);
	if (ack == 1)	ret_code = 1;

	// Send message bytes
	int i;
	for (i=0; i<size;i++) {
		int ack = send_byte(bytes[i]);
		if (ack == 1)	{
			ret_code = 1;
			PORTB |= (1<<PB3);
		}
	}

	// STOP condition
	PORTB &= ~(1<<SCL);
	_delay_us(2);
	PORTB &= ~(1<<SDA);
	_delay_us(2);
	PORTB |= (1<<SCL);
	_delay_us(2);
	PORTB |= (1<<SDA);

	return ret_code;
}