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

typedef enum {
    idle, start_sent, write_address_sent, pointer_sent, restart_sent,
    read_address_sent, receiving, nack_sent, stop_sent
} bus_phase_t;


static bus_phase_t phase;
static unsigned int until_read;
static unsigned char wait_ticks;
static unsigned char candidate;

rtc_results rtc_clock_tick(unsigned char *seconds)
{
    if (until_read != 0u){
        --until_read;
    }
    
    if (phase == idle){
        if (until_read != 0u) return rtc_pending;
        until_read = 1000u;
        candidate = 0xffu;
        if (!PORTCbits.RC3 || !PORTCbits.RC4) return rtc_error;
        PIR1bits.SSP1IF = 0;
        PIR2bits.BCL1IF = 0;
        SSP1CON2bits.SEN = 1;
        phase = start_sent;
        wait_ticks = 0;
        return rtc_pending;
    }
    
    if (PIR2bits.BCL1IF || SSP1CON1bits.WCOL || SSP1CON1bits.SSPOV ||
        ++wait_ticks >= 20u) {
        rtc_clock_init();
        phase = idle;
        return rtc_error;
    }
    if (!PIR1bits.SSP1IF) return rtc_pending;

    PIR1bits.SSP1IF = 0;
    wait_ticks = 0;
    switch (phase) {
    case start_sent:
        SSP1BUF = 0x64;  // 7-bit address 0x32, write
        phase = write_address_sent;
        break;
    case write_address_sent:
    case pointer_sent:
    case read_address_sent:
        if (SSP1CON2bits.ACKSTAT) {
            SSP1CON2bits.PEN = 1;
            phase = stop_sent;
        } else if (phase == write_address_sent) {
            SSP1BUF = 0x00;  // Seconds register and transfer format 0
            phase = pointer_sent;
        } else if (phase == pointer_sent) {
            SSP1CON2bits.RSEN = 1;
            phase = restart_sent;
        } else {
            SSP1CON2bits.RCEN = 1;
            phase = receiving;
        }
        break;
    case restart_sent:
        SSP1BUF = 0x65;  // Same device, read
        phase = read_address_sent;
        break;
    case receiving: {
        unsigned char bcd = SSP1BUF;
        unsigned char tens = bcd >> 4;
        unsigned char ones = bcd & 0x0f;
        if (tens <= 5u && ones <= 9u) candidate = tens * 10u + ones;
        SSP1CON2bits.ACKDT = 1;  // Final byte: NACK then STOP
        SSP1CON2bits.ACKEN = 1;
        phase = nack_sent;
        break;
    }
    case nack_sent:
        SSP1CON2bits.PEN = 1;
        phase = stop_sent;
        break;
    case stop_sent:
        phase = idle;
        if (candidate > 59u) return rtc_error;
        *seconds = candidate;
        return rtc_ready;
    default:
        phase = idle;
        return rtc_error;
    }
    return rtc_pending;
}