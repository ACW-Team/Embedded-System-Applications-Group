#ifndef RTC_CLOCK_H
#define RTC_CLOCK_H

/* Configure the PIC's I2C external RTC. */
void rtc_clock_init(void);
typedef enum {rtc_pending, rtc_ready, rtc_error} rtc_results;
rtc_results rtc_clock_tick(unsigned char *seconds);


#endif