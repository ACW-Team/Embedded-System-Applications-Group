#define _XTAL_FREQ 8000000UL

#include <xc.h>
#include "lcd-display.h"

#define LCD_RS      0x10u  // RB4
#define LCD_E       0x20u  // RB5
#define FIELD_WIDTH 5u     // Enough space for "123.4"

static char field[FIELD_WIDTH];

// Positions 1 to 5 send characters. Position 6 means finished.
static unsigned char position = FIELD_WIDTH + 1u;

static void lcd_nibble(unsigned char value)
{
    // Put four data bits on RB0-RB3 and preserve RB4-RB7.
    LATB = (LATB & 0xF0u) | (value & 0x0Fu);
    __delay_us(1);

    LATB |= LCD_E;
    __delay_us(2);
    LATB &= ~LCD_E;
    __delay_us(2);
}

static void lcd_write(unsigned char value, unsigned char is_data)
{
    if (is_data) {
        LATB |= LCD_RS;    // Character
    } else {
        LATB &= ~LCD_RS;   // Command
    }

    // The LCD expects the upper four bits first.
    lcd_nibble(value >> 4);
    lcd_nibble(value);
    __delay_us(50);        // R/W is grounded, so use the lab's fixed delay.
}

void lcd_init(void)
{
    const char *heading = "LM35 temperature";

    ANSELB &= 0xC0u;       // RB0-RB5 digital
    LATB   &= 0xC0u;       // Start with data, RS and E low
    TRISB  &= 0xC0u;       // RB0-RB5 outputs

    __delay_ms(50);        // Allow the LCD to power up

    // Week 7 sequence to enter 4-bit mode.
    lcd_nibble(0x03);
    __delay_ms(5);
    lcd_nibble(0x03);
    __delay_us(150);
    lcd_nibble(0x03);
    __delay_us(150);
    lcd_nibble(0x02);
    __delay_us(150);

    lcd_write(0x28, 0);    // 4-bit interface, two rows
    lcd_write(0x0C, 0);    // Display on, cursor hidden
    lcd_write(0x06, 0);    // Move cursor right after each character
    lcd_write(0x01, 0);    // Clear once at startup
    __delay_ms(2);

    while (*heading) {
        lcd_write(*heading++, 1);
    }

    // Leave the first five cells of row 2 for the temperature.
    lcd_write(0xC5, 0);
    lcd_write(' ', 1);
    lcd_write('C', 1);
}

void lcd_set_temperature(unsigned int tenths)
{
    // Example: 249 tenths becomes " 24.9".
    // Leading spaces erase old digits when the reading gets shorter.
    field[0] = tenths >= 1000u ? '0' + tenths / 1000u : ' ';
    field[1] = tenths >= 100u  ? '0' + (tenths / 100u) % 10u : ' ';
    field[2] = '0' + (tenths / 10u) % 10u;
    field[3] = '.';
    field[4] = '0' + tenths % 10u;

    position = 0;
}

void lcd_refresh(void)
{
    if (position == 0) {
        lcd_write(0xC0, 0);                 // Start of row 2
    } else if (position <= FIELD_WIDTH) {
        lcd_write(field[position - 1u], 1); // Send one character
    } else {
        return;                            // Field already displayed
    }

    position++;
}