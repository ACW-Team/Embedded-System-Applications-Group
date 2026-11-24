#include <xc.h>
#include "lm35-temperature.h"
#include "seven-segment-display.h"
#include "lcd-display.h"

// EasyPIC lab setup: external 8 MHz crystal
// Code taken and adapted from Lab 5

#pragma config FOSC = HSMP
#pragma config PLLCFG = OFF
#pragma config PRICLKEN = ON
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRTEN = OFF
#pragma config BOREN = OFF
#pragma config WDTEN = OFF
#pragma config PBADEN = OFF
#pragma config MCLRE = INTMCLR
#pragma config LVP = OFF

static void timer2_init(void)
{
    // At 8 MHz, Fosc/4 = 2 MHz.
    // A 1:16 prescaler gives 8 us per count.
    // 125 counts x 8 us = 1 ms.
    T2CON = 0;
    T2CONbits.T2CKPS = 2;
    TMR2 = 0;
    PR2 = 124;
    PIR1bits.TMR2IF = 0;
    T2CONbits.TMR2ON = 1;
}

/*
 * The 1 ms Timer2 setup matches Wiktor's lab_w8.X/newmain_w8.c.
 * At 8 MHz, a 1:16 prescaler gives 8 us per count. PR2 = 124 gives
 * 125 counts per tick. Our main loop polls the Timer2 flag; Wiktor's
 * Week 8 example enables the Timer2 interrupt.
 */
void main(void)
{
    unsigned int raw;
    unsigned int celsius10;
    unsigned char sample_pending = 1;
    unsigned char elapsed_ms = 0;

    OSCCONbits.SCS = 0;    // Use the primary oscillator

    lm35_init();
    sevenseg_init();
    lcd_init();
    timer2_init();

    lm35_start_sample();   // Take the first reading immediately

    while (1) {
        // 1 ms tick advances the seven-segment display
        // by one digit and gives the LCD time for one write. Every 200 ticks, 
        // request a new LM35 reading. This keeps the approximate 200 ms sampling
        // interval used in Week 5 while both displays continue to update.
        if (PIR1bits.TMR2IF) {
            PIR1bits.TMR2IF = 0;

            sevenseg_refresh(); // Light the next seven-segment digit
            lcd_refresh();      // Send one LCD command or character

            elapsed_ms++;
            if (elapsed_ms >= 200) {
                elapsed_ms = 0;

                if (!sample_pending) {
                    lm35_start_sample();
                    sample_pending = 1;
                }
            }
        }
        // Task 1-3 intergration completed ADC resi;ts and converts to Celsius, 
        //5 V reference and an LM35 at 10 mV/degree, 249 mV represents 24.9 degrees C.
        //Adding 512 rounds before division.
        if (sample_pending && ADCON0bits.GO == 0) {
            raw = ((unsigned int)ADRESH << 8) | ADRESL;

            // Assumes a 5.0 V ADC reference. The LM35 gives 10 mV
            // per degree C, so 1 mV represents 0.1 degree C.
            celsius10 = (unsigned int)
                (((unsigned long)raw * 5000UL + 512UL) / 1024UL);

            sevenseg_set_temperature(celsius10);
            lcd_set_temperature(celsius10);

            sample_pending = 0;
        }
    }
}