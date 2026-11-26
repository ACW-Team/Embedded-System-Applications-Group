#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H
// Follows Week 7, Task 7: expose the LCD functions used by main.c and keep pin handling in lcd-display.c.
void lcd_init(void);
void lcd_set_temperature(unsigned int tenths);
void lcd_refresh(void);
void lcd_seconds(unsigned char seconds);
#endif