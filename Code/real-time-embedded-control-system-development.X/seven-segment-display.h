#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H
// Public functions for the Week 5 display: initialise it, set the value and scan one digit.
void sevenseg_init(void);
void sevenseg_set_temperature(unsigned int tenths);
void sevenseg_refresh(void);

#endif
