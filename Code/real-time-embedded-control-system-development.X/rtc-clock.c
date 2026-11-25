/*Real-Time Clock (RTC)

    Use an external RTC module such as the Click16 board to maintain accurate time.
    Implement a heating window (for example 06:30?08:00) during which heating can operate. The selected Day or Night target applies only while heating is allowed.
    Show the current time and date on the LCD. They must be updated from the RTC while the system runs.
    Show the set alarm time in the menu. Allow the user to set the RTC time and date and the Day/Night changeover times using the buttons.
    The RTC should keep time independently, without interrupting other tasks.

 * 
 * Notes 
 */

#include <xc.h>
#include "rtc-clock.h"

/*
 * Assignment Task 3: Real-Time Clock
 * First stage from Diagrams.md: initialise I2C communication.
 *
 * PIC18F45K22, external 8 MHz oscillator.
 * MSSP1 uses RC3 for SCL and RC4 for SDA.
 */
void rtc_clock_init(void)
{
    // Disable MSSP1 while configuring the peripheral.
    SSP1CON1bits.SSPEN = 0;

    // Configure the clock and data pins for digital operation.
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;

    // Release both I2C lines. Pull-ups provide the idle high level.
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;

    // Standard-mode I2C at 100 kHz.
    // SSP1ADD = (Fosc / (4 * I2C clock)) - 1
    //         = (8000000 / (4 * 100000)) - 1 = 19
    SSP1STAT = 0x80;       // Disable slew-rate control for standard mode
    SSP1CON2 = 0x00;       // No transaction in progress
    SSP1ADD = 19;

    SSP1CON1 = 0x28;       // Enable MSSP1 in I2C master mode
}