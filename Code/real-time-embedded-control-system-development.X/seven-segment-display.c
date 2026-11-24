#include <xc.h>
#include "seven-segment-display.h"

/* Week 5 lab mapping task 2 resuing week 4 lab to display the segemnets, holding PORTD petter from 0-9
 * Enabaling physical digits from left to right; RA3 ro RA0
 */ 


static const unsigned char segments[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
static const unsigned char enables[] = {8, 4, 2, 1};
static unsigned char frame[4];
static unsigned char position;

/*
 * Week 5 Lab Solutions, Task 2: configure RD0-RD7 as segment outputs
 * and RA0-RA3 as digit-select outputs. Start with all digits blank.
 */
void sevenseg_init(void)
{
    LATA &= 0xF0;
    LATD = 0;
    ANSELA &= 0xF0;
    ANSELD = 0;
    TRISA &= 0xF0;
    TRISD = 0;
}

/*
 * Based on Week 5 Lab Solutions, Task 3: display Celsius to one decimal place.
 * Split the reading in tenths into digits and prepare their segment patterns.
 * For example, 249 becomes 24.9, with the decimal point on the 4.
 */
void sevenseg_set_temperature(unsigned int tenths)
{
    frame[0] = tenths >= 1000u ? segments[(tenths / 1000u) % 10u] : 0;
    frame[1] = tenths >= 100u ? segments[(tenths / 100u) % 10u] : 0;
    frame[2] = segments[(tenths / 10u) % 10u] | 0x80;
    frame[3] = segments[tenths % 10u];
}
/*
 * Uses the multiplexing method from Week 5 Lab Solutions, Task 2.
 * Blank the digits, change the segment pattern, then enable the next digit.
 * In this project each call handles one digit, timed by the 1 ms tick in main.c.
 */
void sevenseg_refresh(void)
{
    LATA &= 0xF0;  // Blank all digits before changing PORTD.
    LATD = frame[position];
    LATA |= enables[position];
    position = (position + 1u) % 4u;
}
