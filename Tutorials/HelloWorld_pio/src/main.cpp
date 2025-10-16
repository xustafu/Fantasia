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
AudioSynthWaveformSine sine1; // xy=181,272
AudioOutputI2S i2s1;          // xy=418,266

AudioConnection patchCord1(sine1, 0, i2s1, 0);
AudioConnection patchCord2(sine1, 0, i2s1, 1);

AudioControlSGTL5000 sgtl5000_1; // xy=172,336
// GUItool: end automatically generated code

//declarar un objeto sgtl5000 es necesario para que se configure correctamente nuestra 'mini tarjeta de sonido'

// put function declarations here:
int myFunction(int, int);

float frecuencia = 440;
float amplitud = 0.5;

int button1_pin = 2;
int button2_pin = 5;
int button3_pin = 25;
int button4_pin = 27;




void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  AudioMemory(8); // necesaria para que la libreria de audio funcione

  sine1.amplitude(amplitud); // amplitud a medio volumen para empezar

  // ponemos los botones en modo conectados HIGH por defecto
  // en el esquematico vimos que al pulsar el boton se conectan a tierra (LOW)
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);
  pinMode(button3_pin, INPUT_PULLUP);
  pinMode(button4_pin, INPUT_PULLUP);

  analogReadResolution(12); //pasamos de una definicion de 1024 pasos a 4096
}

void loop() {
  // temas de frecuencia y botones
  if (digitalRead(button1_pin) == LOW)
  {
    frecuencia = 440;
  }
  if (digitalRead(button2_pin) == LOW)
  {
    frecuencia = 512;
  }
  if (digitalRead(button3_pin) == LOW)
  {
    frecuencia = 660;
  }
  if (digitalRead(button4_pin) == LOW)
  {
    frecuencia = 880;
  }
  sine1.frequency(frecuencia);

  // temas de amplitud y lecturas analogicas
  sine1.amplitude((float)analogRead(14) / 4095.0f); // cast y escalado a 0-1

  // delay1.delay(4, analogRead(15)/4095.0f * 600)
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }