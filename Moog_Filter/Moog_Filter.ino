#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//Audio declarations
AudioControlSGTL5000     sgtl5000_1;

// Code
AudioInputI2S            i2s2;           //xy=320.8833312988281,1692.88330078125
AudioFilterLadder        filter_L;        //xy=521.88330078125,1644.5833740234375
AudioFilterLadder        filter_R;        //xy=525.88330078125,1755.88330078125
AudioOutputI2S           i2s1;           //xy=734.88330078125,1688.5833740234375
AudioConnection          patchCord1(i2s2, 0, filter_L, 0);
AudioConnection          patchCord2(i2s2, 1, filter_R, 0);
AudioConnection          patchCord3(filter_L, 0, i2s1, 0);
AudioConnection          patchCord4(filter_R, 0, i2s1, 1);

//SD CARD PINS
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

int PotPort1 = A0; // select the input pins for the potentiometers
int PotPort2 = A1;
int PotPort3 = A2;
int PotPort4 = A3;

int Boton1 = 2;    // pushbutton connected to digital pinS
int Boton2 = 5; 
int Boton3 = 25; 
int Boton4 = 27; 
int Gate1 = 3; 
int Gate2 =6; 
int Encoderbut =4;

 // Variables to store port values 
int PotValue1 = 0; 
float Potmaped1 = 0;
int PotValue2 = 0;
float PotRounded2 = 0;
int PotValue3 = 0;
float Potmaped3 = 0;
int PotValue4 = 0;
float Potmaped4 = 0;


int BotonValue1 = 0;   
int BotonValue2 = 0;
int BotonValue3 = 0;
int BotonValue4 = 0;
int GateValue1 = 0;
int GateValue2 = 0;
int EncoderbutValue =0;


void setup() {

//Audio setup
AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(36); //NEEDED?
      
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(Boton1, INPUT_PULLUP);    // sets the digital pin 2 as input
  pinMode(Boton2, INPUT_PULLUP); 
  pinMode(Boton3, INPUT_PULLUP); 
  pinMode(Boton4, INPUT_PULLUP); 
  pinMode(Gate1, INPUT_PULLUP); 
  pinMode(Gate2, INPUT_PULLUP); 
  pinMode(Encoderbut, INPUT_PULLUP); 

}

void loop() {
 
  // read the value from the pots:
  PotValue1 = analogRead(PotPort1); 
  PotValue2 = analogRead(PotPort2);  
  PotValue3 = analogRead(PotPort3); 
  PotValue4 = analogRead(PotPort4); 

  Potmaped1 = map (PotValue1, 0, 1023, 60, 12000);
  filter_L.frequency(Potmaped1);
  filter_R.frequency(Potmaped1);

  PotRounded2 = map (PotValue2, 0, 1023, 0, 1);

  filter_L.resonance(PotRounded2);
  filter_R.resonance(PotRounded2);

  Potmaped3 = map (PotValue3, 0, 1023, 0, 4);

  filter_L.inputDrive(Potmaped3); //range is 0 to 4.0
  filter_R.inputDrive(Potmaped3);

  Potmaped4 = map (PotValue4, 0, 1023, 0.0, 0.5);

  filter_L.passbandGain(Potmaped4);//range is 0 to 0.5 
  filter_R.passbandGain(Potmaped4);



}

 
