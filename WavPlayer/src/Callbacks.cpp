#include "PrjIncludes.h"

extern uint8_t puntero;
//const char *RawFiles[] = {"out1_1.RAW", "out1_2.RAW", "out2_1.RAW", "out2_2.RAW"};
const char *RawFiles[] = {"out1_1.RAW", "out2_1.RAW", "SDTEST3.RAW", "SDTEST4.RAW"};
const char *WavFiles[] = {"SDTEST1.WAV", "SDTEST2.WAV", "SDTEST3.WAV", "SDTEST4.WAV"};


/////////////////////////////////////////
// Inputs callbacks

bool LoopLengthChange(IOInput *pBut){
    int ival = pBut->getValue() ;
    float val =  ival / 1024.;
    uint32_t lenMillis = Play[puntero - 1]->lengthMillis();
    uint32_t lenSamples = Play[puntero - 1]->getFileSizeSamples();
    uint32_t stLoop = Play[puntero - 1]->getLoopStart();

    uint32_t finLoop = stLoop + 2000000 * val;

    D(Serial.printf("Position End: %1.3f/%lu/%lu\n", val, finLoop-stLoop, finLoop );)
    Play[puntero-1]->setLoopFinish( finLoop);
    return true;
}

bool FilePositionChange(IOInput *pBut)
{
    int ival = pBut->getValue() ;
    float val =  ival / 1024.;
    //return playSdWav1.seek(val);
    uint32_t start = Play[puntero-1]->getFileSizeSamples() * val;
    start = (start / AUDIO_BLOCK_SAMPLES/ 4) * AUDIO_BLOCK_SAMPLES * 4 ;

    D(Serial.printf("Position Start: %1.3f/%ld\n", val, start );)
    Play[puntero-1]->setLoopStart( start);
    //playSdWav1.play(RawFiles[puntero-1]);

    return true;
}


bool EncButtonChange(IOInput *pBut)
{

    if (pBut->getValue() == true)
    {
        AudioModule.playFile(RawFiles[puntero-1],puntero-1);
    }
  return true;
}

bool CVAdjustOutputVolume(IOInput* pInput){
  // CV_D use for volumen
    float vol4 = pInput->getValue();
    vol4 = vol4 / 1024;

    /* 
    mixer1.gain(1, vol4*0.8);// / 4.0);
    mixer4.gain(1, vol4*0.8);// / 4.0); 
    */
    mixer2.gain(puntero-1, vol4*0.8);// / 4.0);
    mixer3.gain(puntero-1, vol4*0.8);// / 4.0); 


    D(Serial.printf("volume: %1.3f\n", vol4 );)
    //D(Serial.println(vol4););

    return true;
}

//int sensorValue = 0;
bool CVAdjustplayRateChange(IOInput *pInput){

    int newsensorValue = pInput->getValue();
    //if (newsensorValue / 32 != sensorValue / 32) {
    //    sensorValue = newsensorValue;
        float rate = (newsensorValue - 512.0) / 256.0; //512.0;
        Play[puntero-1]->setPlaybackRate(rate);
        Serial.printf("rate: %1.3f %d\n", rate, newsensorValue );
    //}
    return true;
}

bool PrintChanged(IOInput* pInput)
{
    D(Serial.println(pInput->getValue()););
    return true;
}


/////////////////////////////////////////
// Module Callbacks
bool ModuleButtonChanged(IOClass *pMod, uint8_t id){
    pMod->setLED(id, pMod->Butt[id].getValue());

    return true;
}

bool ModuleGateChanged(IOClass *pMod, uint8_t id){
    pMod->setLED(id, pMod->Gate[id].getValue());

    return true;
}

