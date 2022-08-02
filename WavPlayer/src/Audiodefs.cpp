#include "PrjIncludes.h"
/* 
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h */


AudioPlaySdRawResmp playSdWav1;
AudioPlaySdRawResmp playSdWav2;
AudioPlaySdRawResmp playSdWav3;
AudioPlaySdRawResmp playSdWav4;
AudioPlaySdRawResmp *Play[]={&playSdWav1,&playSdWav2,&playSdWav3,&playSdWav4};

/* 
AudioPlaySdWavResmp playSdWav1;
AudioPlaySdWavResmp playSdWav2;
AudioPlaySdWavResmp playSdWav3;
AudioPlaySdWavResmp playSdWav4;
 */

// GUItool: begin automatically generated code
/* AudioPlaySdWav           playSdWav4;     //xy=102,400.0000057220459
AudioPlaySdWav           playSdWav3;     //xy=105,342.0000057220459
AudioPlaySdWav           playSdWav2;     //xy=107,284
AudioPlaySdWav           playSdWav1;     //xy=108,229.00000381469727
 */
AudioInputI2S            i2s1;           //xy=133,112
AudioMixer4              mixer3;         //xy=300,344
AudioMixer4              mixer2;         //xy=304,242
AudioMixer4              mixer1;         //xy=531.0000076293945,72
AudioMixer4              mixer4;         //xy=532.0000076293945,142.00000190734863
AudioOutputI2S           i2s2;           //xy=688.0000076293945,63.00000190734863
AudioConnection          patchCord1(playSdWav4, 0, mixer2, 3);
AudioConnection          patchCord2(playSdWav4, 1, mixer3, 3);
AudioConnection          patchCord3(playSdWav3, 0, mixer2, 2);
AudioConnection          patchCord4(playSdWav3, 1, mixer3, 2);
AudioConnection          patchCord5(playSdWav2, 0, mixer2, 1);
AudioConnection          patchCord6(playSdWav2, 1, mixer3, 1);
AudioConnection          patchCord7(playSdWav1, 0, mixer2, 0);
AudioConnection          patchCord8(playSdWav1, 1, mixer3, 0);
AudioConnection          patchCord9(i2s1, 0, mixer1, 0);
AudioConnection          patchCord10(i2s1, 1, mixer4, 0);
AudioConnection          patchCord11(mixer3, 0, mixer4, 1);
AudioConnection          patchCord12(mixer2, 0, mixer1, 1);
AudioConnection          patchCord13(mixer1, 0, i2s2, 0);
AudioConnection          patchCord14(mixer4, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=123,30.000001907348633
// GUItool: end automatically generated code
