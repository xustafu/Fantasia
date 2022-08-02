#ifndef Definitions_H
#define Definitions_H

/* // Definitions on command line
#define __IMXRT1062__
#define TEENSYDUINO 152
#define ARDUINO_TEENSY40
#define ARDUINO 10807
#define F_CPU 600000000
#define USB_SERIAL
#define LAYOUT_US_ENGLISH
*/

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13
#define ENC_BUT           4
#define ENCA 0
#define ENCB 1

#define BUT_A 2
#define BUT_B 5
#define BUT_C 24

#define GATE_A 3 
#define GATE_B 6

#define LED_A 22
#define LED_B 27
#define LED_C 25

#define CV_A 17
#define CV_B 16
#define CV_C 15
#define CV_D 14

#define DEBUGMODE
#ifdef DEBUGMODE
#define D(x) x
#else
#define D(x) 
#endif

// Defined on display7seg.cpp 
// byte segmentPins[] = {30, 32, 33, 28, 31, 26, 29, 9};
#define DEBOUNCEMILS 3 /// Debounce for digital inputs

#endif