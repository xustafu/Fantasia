// use: https://github.com/dgduncan/SevenSegment
#include <SegmentDisplay.h>
// https://github.com/newdigate/teensy-variable-playback
#include <TeensyVariablePlayback.h>

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

#define DUMP_POTS 1

// Audio Declarations
AudioControlSGTL5000     sgtl5000_1;     //xy=1125,313

// GUItool: begin automatically generated code
// AudioPlaySdWav           wavPlayer;     //xy=217,501
AudioPlaySdResmp         wavPlayer;     //xy=217,501
AudioOutputI2S           i2s1;           //xy=435,502
AudioConnection          patchCord1(wavPlayer, 0, i2s1, 0);
AudioConnection          patchCord2(wavPlayer, 1, i2s1, 1);
// GUItool: end automatically generated code

//Display LEDs Declaration
// SegmentDisplay segmentDisplay(30, 32, 33, 28, 31, 26, 29, 9);
//                             E   D   C  DP  B   A   G   F
//                             1   2   4  5   6   7   9  10
SegmentDisplay segmentDisplay(31, 28, 33, 9, 32, 30, 26, 29);

//Teensy audio initialization Code
//SD CARD PINS
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

int maxSdReadAttempts = 10;
int numSdReadAttempts = 0;
File root;
enum {
SOUND_BANK_A,
SOUND_BANK_B,
};
String sounds[MAX_NUM_SOUND_BANKS][MAX_NUM_SOUND_FILES];
int soundBank = SOUND_BANK_A;
int soundFile = 0; // display value
String soundFilename;


// select the input pins for the potentiometers
int potPin1 = A0; // play rate
int potPin2 = A1; // start pos
int potPin3 = A2; // size
int potPin4 = A3; // spread
Encoder enc(0,1);

// pushbutton connected to digital pinS
int btnPin1 = 2;
int btnPin2 = 5; 
int btnPin3 = 25; 
int btnPin4 = 27; 
int gatePin1 = 3; 
int gatePin2 =6; 
int encBtnPin =4;

 // Variables to store port values 
float pot1 = 0; 
float pot2 = 0;
float pot3 = 0;
float pot4 = 0;

int btn1 = BUTTON_UP;
int btn2 = BUTTON_UP;
int btn3 = BUTTON_UP;
int btn4 = BUTTON_UP;

int gate1 = 0;
int gate2 = 0;

long oldEncPos = -999;
long encPos = -999;
bool encFlag = 0; // is display decimal flag displayed
int encPressed = 0; // is encoder button pressed
char displayValue = 0;

int playratePotValue = 0;
int startPotValue = 0;
int sizePotValue = 0;
int spreadPotValue = 0;
bool loopWav = true;
bool btn1Down = false;

void setup() {  
  // open the serial port at 9600 bps:
  Serial.begin(9600); 
  Serial.println("Booting Sampler");
  
  audioSetup();
  sdCardSetup();

  loadSoundFiles();
  wavPlayer.playWav("SDTEST1.WAV");
  Serial.println("Playing sound file...");

  pinSetup();

  Serial.print("SOUND_BANK:"); Serial.println(soundBank);
}

void loop() {
  update();

  // Controller values can be used directly: pot1, btn2, encPos, encPressed
  
  // change sample speed
  playratePotValue = max(pot1, 20);
  wavPlayer.setPlaybackRate(getPlaybackRate(playratePotValue));
}

void update() {
  pot1 = analogRead(potPin1);
  pot2 = analogRead(potPin2);
  pot3 = max(analogRead(potPin3), 1);
  pot4 = analogRead(potPin4);
  btn1 = !digitalRead(btnPin1);
  btn2 = !digitalRead(btnPin2);
  btn3 = !digitalRead(btnPin3);
  btn4 = !digitalRead(btnPin4);
  encPressed = !digitalRead(encBtnPin);
  encPos = enc.read() / 4;
  
  updateEncoder(encPos);

#if DUMP_POTS
  Serial.print("potA:");
  Serial.print(pot1);
  Serial.print(" potB:");
  Serial.print(pot2);
  Serial.print(" potC:");
  Serial.print(pot3);
  Serial.print(" potD:");
  Serial.print(pot4);
  Serial.print(" btnA:");
  Serial.print(btn1);
  Serial.print(" btnB:");
  Serial.print(btn2);
  Serial.print(" btnC:");
  Serial.print(btn3);
  Serial.print(" btnD:");
  Serial.print(btn4);
  Serial.print(" display:");
  Serial.print(int(displayValue));
  Serial.print(" dot:");
  Serial.print(encFlag);
  Serial.print(" enc:");
  Serial.print(encPos);
  Serial.print(" encPressed:");
  Serial.print(encPressed);
  Serial.print(" wav:");
  Serial.print(soundFilename);
  Serial.println();
#endif
}

void audioSetup() {
  Serial.println("Setting up audio...");
  AudioMemory(24);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(36); //NEEDED?

  wavPlayer.enableInterpolation(true);
  wavPlayer.setLoopType(loop_type::looptype_repeat);
  playratePotValue = analogRead(potPin1);
  startPotValue = analogRead(potPin2);
  wavPlayer.setPlaybackRate(getPlaybackRate(playratePotValue));
  wavPlayer.setLoopStart(getStartPosition(startPotValue));

  Serial.println("Audio ready");
}

void sdCardSetup() {
  Serial.println("Setting up SD card...");
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (numSdReadAttempts < maxSdReadAttempts) {
      Serial.println("Unable to access the SD card");
      numSdReadAttempts++;
      delay(500);
    }
    Serial.println("ERROR: Failed to read SD card.");
  }
  numSdReadAttempts = 0;
}

void pinSetup() {
  // sets the digital pins as inputs and set pullups
  Serial.println("Setting digital pins...");
  pinMode(btnPin1, INPUT_PULLUP);
  pinMode(btnPin2, INPUT_PULLUP);
  pinMode(btnPin3, INPUT_PULLUP);
  pinMode(btnPin4, INPUT_PULLUP);
  pinMode(gatePin1, INPUT_PULLUP);
  pinMode(gatePin2, INPUT_PULLUP);
  pinMode(encBtnPin, INPUT_PULLUP);
  Serial.println("done");

  // set Display LEDs ports as Outputs
  Serial.println("Setting display...");
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.println("done");
}

void printDirectory(File dir, int numTabs) {
  while( true ) {
    File entry = dir.openNextFile();
    
    if (!entry) { break; }

    for(uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    
    Serial.print(entry.name());
    
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    
    entry.close();
  }
}

void loadSoundFiles() {
    Serial.println("Loading sound files...");
    Serial.println("Reading root...");
    root = SD.open("/");
    // printDirectory( root, 0 );

    int soundIndex = 0;

    while(true) {
      File entry = root.openNextFile();
      if(!entry) { break; }

      String s(entry.name());
      if (s.endsWith(".wav") || s.endsWith(".WAV")) {
        sounds[soundBank][soundIndex] = entry.name();
        Serial.print(entry.name());
        Serial.print(" : ");
        Serial.println(sounds[soundBank][soundIndex]);
        soundIndex++;
      }
      else {
        Serial.print(entry.name());
        Serial.println(" not supported.");
      }
      entry.close();
    }
    root.close();
    Serial.println("Loading sound files done.");
}

void changeSoundFile( String filename ) {
  Serial.print("change sound: ");
  Serial.println(filename);
  int length = filename.length() + 1;
  char buf [length];
  filename.toCharArray(buf, length);
  wavPlayer.stop();
  wavPlayer.playWav(buf);
}

void updateEncoder(int pos) {

  if (encPressed) { 
    encFlag = !encFlag;
    soundBank = int(encFlag);
    soundFilename = sounds[soundBank][soundFile];
  }

  if (pos != oldEncPos) {
    int hex = abs(pos) % 16;
    if(pos < 0) {
      hex = 16 - hex;
    }

    // safety measure to avoid reading empty slots
    // if( sounds[soundBank][hex].length() <= 0 ) return;
    // if(sounds[soundBank][hex].length() <=0 && pos > 0) updateEncoder(hex+1);
    // if(sounds[soundBank][hex].length() <=0 && pos < 0) updateEncoder(hex-1);

    displayValue = hex;

    soundFilename = sounds[soundBank][hex];
    if (soundFilename.length() != 0) {
      changeSoundFile(soundFilename);
    }
    encPos = pos;
    oldEncPos = pos;
  }
    
  segmentDisplay.displayHex(displayValue, encFlag);
}

double getPlaybackRate(int16_t analog) {
  return (analog - 512.0) / 512.0 * 2;
}

double getStartPosition(int16_t analog) {
  return (analog - 512.0) / 512.0;
}
