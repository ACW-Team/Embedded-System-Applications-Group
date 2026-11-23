#include <xc.h>
#include "seven-segment-display.h"

// Week 5 lab mapping: PORTD = segments a-g and decimal point.
// Left to right the digit enables are RA3, RA2, RA1 and RA0.
static const unsigned char segments[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
static const unsigned char enables[] = {8, 4, 2, 1};
static unsigned char frame[4];
static unsigned char position;

void sevenseg_init(void)
{
    LATA &= 0xF0;
    LATD = 0;
    ANSELA &= 0xF0;
    ANSELD = 0;
    TRISA &= 0xF0;
    TRISD = 0;
}

void sevenseg_set_temperature(unsigned int tenths)
{
    frame[0] = tenths >= 1000u ? segments[(tenths / 1000u) % 10u] : 0;
    frame[1] = tenths >= 100u ? segments[(tenths / 100u) % 10u] : 0;
    frame[2] = segments[(tenths / 10u) % 10u] | 0x80;
    frame[3] = segments[tenths % 10u];
}

void sevenseg_refresh(void)
{
    LATA &= 0xF0;  // Blank all digits before changing PORTD.
    LATD = frame[position];
    LATA |= enables[position];
    position = (position + 1u) % 4u;
}
