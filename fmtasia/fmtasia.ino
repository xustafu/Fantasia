/*
  FMTASIA - by Roger Pibernat - GPL3

  FM synth with 2 oscillators (1 modulator and 1 carrier).
  This is still in development stage, it will change with new updates.
  I'll try to keep the docs up to date.

  Use pots with small increments, FM gets crazy very fast.

  POT/CV 1 = CAR FREQ [20..] Hz (left)
  POT/CV 2 = CAR AMP
  POT/CV 3 = MOD FREQ [1-1024] Hz
  POT/CV 4 = MOD AMP
  ENC = WAVEFORM [SINE, SAW, REVSAW, SQUARE, TRI, VARTRI, ARBITRARY, PULSE, S&H
  DISPLAY = Isn't working at the moment.
*/

#include "SegmentDisplay.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Encoder.h>

//Display LEDs Declaration
//                             E   D   C  DP  B   A   G   F
//                             1   2   4  5   6   7   9  10
SegmentDisplay segmentDisplay(31, 28, 33, 9, 32, 30, 26, 29);

//Audio declarations
AudioControlSGTL5000     sgtl5000_1;

//Teensy audio initialization Code
AudioInputI2S            i2s1;           //xy=317.8833312988281,383.8833312988281
AudioSynthWaveform       mod;      //xy=517.8833312988281,310.8833312988281
AudioSynthWaveformSineModulated car;       //xy=675.88330078125,312.8833312988281
AudioOutputI2S           i2s2;           //xy=1034.88330078125,309.8833312988281
AudioConnection          patchCord1(mod, car);
AudioConnection          patchCord2(car, 0, i2s2, 0);
AudioConnection          patchCord3(car, 0, i2s2, 1);




//SD CARD PINS y
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

// select the input pins for the potentiometers
int PotPort1 = A0; 
int PotPort2 = A1;
int PotPort3 = A2;
int PotPort4 = A3;

Encoder enc(0,1);
long oldEncPos = -999;

int waveform = 0;
const int16_t waveforms[13] =  {
    WAVEFORM_SINE,
    WAVEFORM_SAWTOOTH,
    WAVEFORM_BANDLIMIT_SAWTOOTH,
    WAVEFORM_SAWTOOTH_REVERSE,
    WAVEFORM_BANDLIMIT_SAWTOOTH_REVERSE,
    WAVEFORM_SQUARE,
    WAVEFORM_BANDLIMIT_SQUARE,
    WAVEFORM_TRIANGLE,
    WAVEFORM_TRIANGLE_VARIABLE,
    WAVEFORM_ARBITRARY,
    WAVEFORM_PULSE,
    WAVEFORM_BANDLIMIT_PULSE,
    WAVEFORM_SAMPLE_HOLD
};

// pushbutton connected to digital pinS
int Boton1 = 2;    
int Boton2 = 5; 
int Boton3 = 25; 
int Boton4 = 27; 
int Gate1 = 3; 
int Gate2 =6; 
int Encoderbut =4;

 // Variables to store port values 
int PotValue1 = 0; 
int PotValue2 = 0;
int PotValue3 = 0;
int PotValue4 = 0;
int BotonValue1 = 0;   
int BotonValue2 = 0;
int BotonValue3 = 0;
int BotonValue4 = 0;
int GateValue1 = 0;
int GateValue2 = 0;
int EncoderbutValue =0;
char displayValue=0;

void setup() {

//Audio setup
AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(36); //NEEDED?
//  SPI.setMOSI(SDCARD_MOSI_PIN);
//  SPI.setSCK(SDCARD_SCK_PIN);
//  if (!(SD.begin(SDCARD_CS_PIN))) {
//    while (1) {
//      Serial.println("Unable to access the SD card");
//      delay(500);
//    }
//  }
  // open the serial port at 9600 bps:
  Serial.begin(9600); 
  
  // sets the digital pins as inputs and set pullups
  pinMode(Boton1, INPUT_PULLUP);   
  pinMode(Boton2, INPUT_PULLUP); 
  pinMode(Boton3, INPUT_PULLUP); 
  pinMode(Boton4, INPUT_PULLUP); 
  pinMode(Gate1, INPUT_PULLUP); 
  pinMode(Gate2, INPUT_PULLUP); 
  pinMode(Encoderbut, INPUT_PULLUP); 


//Set Display LEDs ports as Outputs 
    pinMode(30, OUTPUT);    
    pinMode(32, OUTPUT); 
    pinMode(33, OUTPUT); 
    pinMode(28, OUTPUT); 
    pinMode(31, OUTPUT); 
    pinMode(26, OUTPUT); 
    pinMode(29, OUTPUT); 
    pinMode(9, OUTPUT); 
  delay(1000);

  car.frequency(200);
  car.amplitude(1);
  mod.frequency(analogRead(PotPort3));
  mod.amplitude(analogRead(PotPort4));
  mod.begin(WAVEFORM_TRIANGLE);
  
}


void loop() {
  PotValue1 = max(analogRead(PotPort1), 20);
  PotValue2 = analogRead(PotPort2);
  PotValue3 = max(analogRead(PotPort3), 1);
  PotValue4 = analogRead(PotPort4);

//  Serial.println(PotValue2);
  
  car.frequency(PotValue1);
  car.amplitude(float(PotValue2) / 1024);
  mod.frequency(PotValue3);
  mod.amplitude(float(PotValue4) / 1024);

  readEncoder();
//  segmentDisplay.testDisplay();
}

void readEncoder() {
  long newEncPos = enc.read() / 4;
  waveform = abs(newEncPos % 16);
//  waveform = newEncPos;/
  Serial.print(newEncPos);
  Serial.print(" : ");
  Serial.println(waveform);
  if(newEncPos != oldEncPos) {
    oldEncPos = newEncPos;
    segmentDisplay.displayHex(waveform, false);
    mod.begin(waveforms[waveform]);
//    segmentDisplay.displayHex(0, false);
  }
}

 
