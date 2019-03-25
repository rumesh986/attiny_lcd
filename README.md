# attiny_lcd
code to display text on an i2c LCD disply with attiny devices

## Usage
Place the files in your project directory and add `#include "attiny_lcd.h"` to your main .c file
This project also requires `attiny_i2c.c` and `attiny_i2c.h` from [my other repo](https://github.com/rumesh986/attiny_i2c).
The `SDA pin` is set as `PB0` and the `SCL pin` is set as `PB2`. This can be changed in `attiny_i2c.h`
The address for the LCD display is set as `0x20`. This can be changed in `attiny_lcd.h`

### void init_display(void);
Setup your display.

### void disp_text(char *str);
print the string at `*str` on the screen (cursor position is not changed before printing).

### void disp_2line_text(char *str1, char *str2);
print two string onto the two lines of the display. (cursor is set to the beginning of each line before printing)

### void set_backlight(bool state);
Switch On/Off the backlight of your display.
#### valid options:
**true**: Switch on backlight

**false**:  Switch off backlight

### void shift_screen(uint8_t direction, uint8_t count);
Shift the text on screen by `count` units left or right.
#### valid options:
**SHIFT_LEFT**: shift text by `count` units to the left.

**SHIFT_RIGHT**: shift text by `count` units to the right.

### void configure_display(uint8_t cmd);
Change the  display settings.
#### valid options:
**CURSOR_LEFT**:  0b00010000

**CURSOR_RIGHT**: 0b00010100

**SHIFT_LEFT**:   0b00011000

**SHIFT_RIGHT**:  0b00011100

**LINE_1**: 0b10000000

**LINE_2**: 0b11000000
