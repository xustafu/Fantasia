#include "PrjIncludes.h"

bool AudioClass::Init(){
   // Audio connections require memory to work.  For more
   // detailed information, see the MemoryAndCpuUsage example
   AudioMemory(16);
   sgtl5000_1.enable();
   sgtl5000_1.volume(0.5);

    // Settup mixers
    mixer2.gain(0, 0.25);
    mixer2.gain(1, 0.25);
    mixer2.gain(2, 0.25);
    mixer2.gain(3, 0.25);
    mixer3.gain(0, 0.25);
    mixer3.gain(1, 0.25);
    mixer3.gain(2, 0.25);
    mixer3.gain(3, 0.25);

    mixer1.gain(0, 0.25);
    mixer1.gain(1, 0.25);
  //  mixer1.gain(2, 0.25);
  //  mixer1.gain(3, 0.25);
    mixer4.gain(0, 0.25);
    mixer4.gain(1, 0.25);
    //mixer4.gain(2, 0.25);
    //mixer4.gain(3, 0.25);

  // Players init
  for (size_t i = 0; i < 4; i++)
  {
    Play[i]->setLoopType(looptype_repeat);
  }

  return true;
}



void AudioClass::playFile(const char *filename, uint8_t port)
{
  //AudioPlaySdWavResmp 
  //AudioPlaySdRawResmp *Play[]={&playSdWav1,&playSdWav2,&playSdWav3,&playSdWav4};
  
  if( Play[port]->isPlaying()){
    D(Serial.print("Stop play: ");
      Serial.println(filename););
    Play[port]->stop();
  }else{
    D(Serial.print("Playing file: ");
      Serial.println(filename););
    Play[port]->play(filename);
  }
  /*
  // Start playing the file.  This sketch continues to
  // run while the file plays.
  if( playSdWav1.isPlaying())
    if( playSdWav2.isPlaying())
        if( playSdWav3.isPlaying())
            if( playSdWav4.isPlaying())
                Serial.println("All channel in use");
            else playSdWav4.play(filename); 
        else playSdWav3.play(filename); 
    else playSdWav2.play(filename);
  else playSdWav1.play(filename);
  */
  // A brief delay for the library read WAV info
  delay(10);

}

AudioClass AudioModule;
