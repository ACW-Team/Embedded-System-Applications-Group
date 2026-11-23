#include <xc.h>
#include "lm35-temperature.h"
#include "seven-segment-display.h"
#include "lcd-display.h"

// EasyPIC lab setup: external 8 MHz crystal
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