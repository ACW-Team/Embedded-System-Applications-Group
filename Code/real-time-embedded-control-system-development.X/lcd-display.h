#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

void lcd_init(void);
void lcd_set_temperature(unsigned int tenths);
void lcd_refresh(void);

#endif