/*
Measure the Temperature (LM35 Sensor)

    Use the LM35 sensor connected to AN6/RE1 for analogue temperature measurement.
    Convert the ADC voltage to temperature in ?C using correct calibration and scaling.
    Continuously update the measured value on both the 4-digit seven-segment display and the LCD, without flicker or delay.
    Display refresh should be smooth and concurrent with other system functions.

 * Notes
 * Code taken and adapted from Lab 5
 */


#include <xc.h>
#include "lm35-temperature.h"
/*
 * Based and adapted from week 5 lab, for analogue temperature measurement.
 * Convert the ADC voltage to temperature inlab uses RE2/AN7. Our assignment uses RE1/AN6, so this version
 * selects channel 6 and configures RE1 as an analogue input.
 * VDD and VSS provide the reference voltages for the 10-bit reading.
 */

void lm35_init(void) {
    TRISEbits.TRISE1 = 1; // Sets RE1 as input
    ANSELEbits.ANSE1 = 1; // Enables analouge on RE1
    ADCON0bits.CHS = 6; // Selects channel
    
    //Measure the sensor voltage relative
    ADCON1bits.PVCFG = 0; // Use the PIC supply voltage (VDD) as the upper reference.
    ADCON1bits.NVCFG = 0; // Use ground as lowwer reference point
    
    // Set result format and sapling on the 8Mhz clock
    ADCON2bits.ADFM = 1; // Right align with 10-bit ADC result
    ADCON2bits.ADCS = 5; //Fosc/16 gives 2 ?s ADC clock period
    ADCON2bits.ACQT = 5; // Allow 12 ADC clock periods (24 us) for acquisition.
    
    ADCON0bits.ADON = 1; // Enable ADC 
}

/*
 * starts a ADC conversion within this function and returns the value immediately. maind.c checks when the "GO" setting is clear
 * the displays can continue refreshing while the ADC is working.
 */

void lm35_start_sample(void)
{
    ADCON0bits.GO = 1; // Starts one ADC conversion
}
