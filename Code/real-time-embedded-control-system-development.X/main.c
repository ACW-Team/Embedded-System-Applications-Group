/*
 * File:   main.c
 * Author: reece
 *
 * Created on November 16, 2026, 3:55 PM
 */


#include <xc.h>
#include "lm35-temperature.h"


// Configuration settings from the Week 5 lab.
#pragma config FOSC = HSMP          // External crystal oscillator, 4?16 MHz range.
#pragma config PLLCFG = OFF         // Use the board's 8 MHz crystal without the 4x PLL.
#pragma config PRICLKEN = ON        // Enable the primary oscillator.
#pragma config FCMEN = OFF          // Disable the fail-safe clock monitor.
#pragma config IESO = OFF           // Disable automatic oscillator switching.
#pragma config PWRTEN = OFF         // Disable the power-up timer.
#pragma config BOREN = OFF          // Disable brown-out reset.
#pragma config WDTEN = OFF          // Disable the watchdog timer.
#pragma config PBADEN = OFF         // Start PORTB pins in digital mode.
#pragma config MCLRE = INTMCLR      // Use the internal master clear.
#pragma config LVP = OFF            // Disable low-voltage programming.

static void timer2_init(void)
{
    T2CON = 0;                 // Stop Timer2 and select a 1:1 postscaler.
    T2CONbits.T2CKPS = 2;      // Select the 1:16 prescaler.
    TMR2 = 0;                  // Start counting from zero.
    PR2 = 124;                 // Count 125 timer steps per tick.
    PIR1bits.TMR2IF = 0;       // Clear any previous tick.
    T2CONbits.TMR2ON = 1;      // Start Timer2.
}

void main(void)
{
    volatile unsigned int raw = 0;
    volatile unsigned int celsius10 = 0;
    unsigned char sample_pending = 1;
    unsigned char elapsed_ms = 0;

    OSCCONbits.SCS = 0; // Use the board's 8 MHz primary oscillator.
    lm35_init(); // Configure RE1/AN6 and enable the ADC.
    timer2_init();
    lm35_start_sample(); // Request the first reading.

    while (1) {
        if (PIR1bits.TMR2IF) {
    PIR1bits.TMR2IF = 0;       // Acknowledge this 1 ms tick.
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
            raw = (unsigned int)ADRESH * 256u + ADRESL;
            celsius10 = (unsigned int)
                (((unsigned long)raw * 5000UL + 512UL) / 1024UL);

            sample_pending = 0;
        }
    }
}
