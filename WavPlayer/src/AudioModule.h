

#ifndef AudioModule_h
#define AudioModule_h

class AudioClass
{
public:
    bool Init(void);
    void playFile(const char *filename, uint8_t port);
};

extern AudioClass AudioModule;

// Copy from Audiodefs.cpp generated code
extern AudioPlaySdRawResmp playSdWav1;
extern AudioPlaySdRawResmp playSdWav2;
extern AudioPlaySdRawResmp playSdWav3;
extern AudioPlaySdRawResmp playSdWav4;
extern AudioPlaySdRawResmp *Play[];
/* 
extern AudioPlaySdWavResmp playSdWav1;
extern AudioPlaySdWavResmp playSdWav2;
extern AudioPlaySdWavResmp playSdWav3;
extern AudioPlaySdWavResmp playSdWav4;
 */
/* 
extern AudioPlaySdWav           playSdWav3;     //xy=105,342.0000057220459
extern AudioPlaySdWav           playSdWav4;     //xy=102,400.0000057220459
extern AudioPlaySdWav           playSdWav2;     //xy=107,284
extern AudioPlaySdWav           playSdWav1;     //xy=108,229.00000381469727
 */
extern AudioInputI2S            i2s1;           //xy=133,112
extern AudioMixer4              mixer3;         //xy=300,344
extern AudioMixer4              mixer2;         //xy=304,242
extern AudioMixer4              mixer1;         //xy=531.0000076293945,72
extern AudioMixer4              mixer4;         //xy=532.0000076293945,142.00000190734863
extern AudioOutputI2S           i2s2;           //xy=688.0000076293945,63.00000190734863
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioControlSGTL5000     sgtl5000_1;     //xy=123,30.000001907348633

#endif