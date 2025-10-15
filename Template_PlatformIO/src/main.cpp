#include <Arduino.h>
#include <SegmentDisplay.h>
#include <Audio.h>
#include <Encoder.h>

// Audio TEST Declarations
AudioSynthWaveformSine   sine1;          //xy=445.20001220703125,707.5999450683594
AudioOutputI2S           i2s2;           //xy=837.1999969482422,711.6000213623047

AudioConnection          patchCord1(sine1, 0, i2s2, 0);
AudioConnection          patchCord2(sine1, 0, i2s2, 1);

AudioControlSGTL5000     sgtl5000_1;     //xy=1125,313
// End automatically generated code

// Segment display
SegmentDisplay segmentDisplay(30, 32, 33, 28, 31, 26, 29, 9); // Pins connected to A, B, C, D, E, F, G, DP segments

//Encoder init test
Encoder myEnc(0, 1); // Pins connected to encoder A and B outputs

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

void setup() {
 //Audio setup
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(36); //NEEDED?
    
  // open the serial port at 9600 bps:
  Serial.begin(9600); 
  Serial.println("Basic Encoder Test:");

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

//Encoder test variable declarations
long oldPosition  = -999;

void loop() {
  // Seven Segment Test code
  segmentDisplay.testDisplay();
  //Audio
    sine1.frequency(440);
    sine1.amplitude(0.4);
  //Encoder test code
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);

  } 
}

