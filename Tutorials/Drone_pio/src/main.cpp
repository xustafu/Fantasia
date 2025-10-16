#include <Arduino.h>

// use: https://github.com/dgduncan/SevenSegment
// #include <SegmentDisplay.h>
// https://github.com/newdigate/teensy-variable-playback
// #include <TeensyVariablePlayback.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Encoder.h>

#define MAX_NUM_SOUND_BANKS 2
#define MAX_NUM_SOUND_FILES 16
#define BUTTON_UP 0
#define BUTTON_DOWN 1

// GUItool: begin automatically generated code
AudioSynthWaveform waveform3;      // xy=158,499
AudioSynthWaveform waveform4;      // xy=159,562
AudioSynthWaveform waveform1;      // xy=160,373
AudioSynthWaveform waveform2;      // xy=160,439
AudioInputI2S i2s2;                // xy=163,292
AudioEffectGranular granular1;     // xy=298,722
AudioMixer4 mixer1;                // xy=386,485
AudioEffectWaveFolder wavefolder1; // xy=525,379
AudioEffectDelay delay1;           // xy=723,654
AudioFilterLadder filter1;         // xy=760,394
AudioMixer4 mixer2;                // xy=883,628
AudioOutputI2S i2s1;               // xy=1041,492

AudioConnection patchCord1(waveform3, 0, mixer1, 2);
AudioConnection patchCord2(waveform4, 0, mixer1, 3);
AudioConnection patchCord3(waveform1, 0, mixer1, 0);
AudioConnection patchCord4(waveform2, 0, mixer1, 1);
AudioConnection patchCord5(i2s2, 0, wavefolder1, 1);
AudioConnection patchCord6(mixer1, 0, wavefolder1, 0);
AudioConnection patchCord7(wavefolder1, 0, filter1, 0);
AudioConnection patchCord8(delay1, 0, mixer2, 0);
AudioConnection patchCord9(delay1, 1, mixer2, 1);
AudioConnection patchCord10(filter1, delay1);
AudioConnection patchCord11(mixer2, 0, i2s1, 0);
AudioConnection patchCord12(mixer2, 0, i2s1, 1);

AudioControlSGTL5000 sgtl5000_1; // xy=193,144
// GUItool: end automatically generated code

int button1_pin = 2;
int button2_pin = 5;
int button3_pin = 25;
int button4_pin = 27;

float freq1 = 440;
float freq2 = 442;
float freq3 = 446;
float freq4 = 448;

// Variables to store pot values
int PotValue1 = 0;
float Potmaped1 = 0;
int PotValue2 = 0;
float Potmaped2 = 0;
int PotValue3 = 0;
float Potmaped3 = 0;
int PotValue4 = 0;
float Potmaped4 = 0;

int PotPort1 = A0; // select the input pins for the potentiometers
int PotPort2 = A1;
int PotPort3 = A2;
int PotPort4 = A3;

void setup() {

  AudioMemory(120); // necesaria para que la libreria de audio funcione

  // inicializamos el driver de audio
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);

  // ponemos los botones en modo conectados HIGH por defecto
  // en el esquematico vimos que al pulsar el boton se conectan a tierra (LOW)
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);
  pinMode(button3_pin, INPUT_PULLUP);
  pinMode(button4_pin, INPUT_PULLUP);

  analogReadResolution(12); // pasamos de una definicion de 1024 pasos a 4096

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);
  mixer1.gain(3, 1.0);

  waveform1.amplitude(0.33);
  waveform2.amplitude(0.33);
  waveform3.amplitude(0.33);
  waveform4.amplitude(0.33);

  delay1.delay(0, 110);
  delay1.delay(1, 220);
  delay1.delay(2, 330);

  // bitcrusher1.sampleRate(44100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(button1_pin) == LOW)
  {
    waveform1.begin(WAVEFORM_SINE);
    waveform2.begin(WAVEFORM_SINE);
    waveform3.begin(WAVEFORM_SINE);
    waveform4.begin(WAVEFORM_SINE);
  }
  if (digitalRead(button2_pin) == LOW)
  {
    waveform1.begin(WAVEFORM_SQUARE);
    waveform2.begin(WAVEFORM_SQUARE);
    waveform3.begin(WAVEFORM_SQUARE);
    waveform4.begin(WAVEFORM_SQUARE);
  }
  if (digitalRead(button3_pin) == LOW)
  {
    waveform1.begin(WAVEFORM_TRIANGLE);
    waveform2.begin(WAVEFORM_TRIANGLE);
    waveform3.begin(WAVEFORM_TRIANGLE);
    waveform4.begin(WAVEFORM_TRIANGLE);
  }
  if (digitalRead(button4_pin) == LOW)
  {
    waveform1.begin(WAVEFORM_SAWTOOTH);
    waveform2.begin(WAVEFORM_SAWTOOTH);
    waveform3.begin(WAVEFORM_SAWTOOTH);
    waveform4.begin(WAVEFORM_SAWTOOTH);
  }

  

  // read the value from the pots:
  PotValue1 = analogRead(PotPort1);
  PotValue2 = analogRead(PotPort2);
  PotValue3 = analogRead(PotPort3);
  PotValue4 = analogRead(PotPort4);

  Potmaped1 = map(PotValue1, 0, 4095, 60, 12000);
  filter1.frequency(Potmaped1);
  // filter_R.frequency(Potmaped1);

  // PotRounded2 = map(PotValue2, 0, 1023, 0, 1);

  filter1.resonance(0);
  // filter_R.resonance(0);

  Potmaped3 = map(PotValue3, 0, 4095, 0.0, 3.0);

  filter1.inputDrive(Potmaped3); // range is 0 to 4.0
  // filter_R.inputDrive(Potmaped3);

  Potmaped4 = map(PotValue4, 0, 4095, 16, 1);
  // bitcrusher1.bits(Potmaped4);

  filter1.passbandGain(0.5); // range is 0 to 0.5
  // filter_R.passbandGain(0.5);

  freq1 = map(PotValue2, 0, 4095, 440, 512);
  freq2 = map(PotValue2, 0, 4095, 440, 550);
  freq3 = map(PotValue2, 0, 4095, 440, 600);
  freq4 = map(PotValue2, 0, 4095, 440, 620);

  waveform1.frequency(freq1);
  waveform2.frequency(freq2);
  waveform3.frequency(freq3);
  waveform4.frequency(freq4);
}
