#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// Audio Declarations
AudioSynthWaveform       waveform1;      //xy=684,318
AudioOutputI2S           i2s1;           //xy=913,314
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1125,313
// GUItool: end automatically generated code


//Display LEDs Declaration
//SegmentDisplay segmentDisplay(30, 32, 33, 28, 31, 26, 29, 9);


//Teensy audio initialization Code

//SD CARD PINS
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

// select the input pins for the potentiometers
int PotPort1 = A0; 
int PotPort2 = A1;
int PotPort3 = A2;
int PotPort4 = A3;

// pushbutton connected to digital pinS
int Boton1 = 2;    
int Boton2 = 5; 
int Boton3 = 25; 
int Boton4 = 27; 
int Gate1 = 3; 
int Gate2 =6; 
int Encoderbut =4;

 // Variables to store port values 
float PotValue1 = 0; 
float PotValue2 = 0;
float PotValue3 = 0;
float PotValue4 = 0;
int BotonValue1 = 0;   
int BotonValue2 = 0;
int BotonValue3 = 0;
int BotonValue4 = 0;
int GateValue1 = 0;
int GateValue2 = 0;
int EncoderbutValue =0;

int mywaveform = 0;

void setup() {

//Audio setup
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(36); //NEEDED?
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  
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


}


void loop() {

 
  
}
