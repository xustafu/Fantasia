
#include "PrjIncludes.h"


void setup() {

  // Debug output
  D( Serial.begin(115200);
   Serial.println(" Begin Test:");)

  //---------------Audio block----------------------
  AudioModule.Init();

  //---------------7Seg block----------------------
  sevseg.init();

  //---------------SD Card block----------------------
  SDCard.init();

  //---------------I/O Block--------------------
  IOModule.Init();
}


long oldPosition = 0;
uint8_t puntero = 1;

void loop()
{

  //---------------analog Read Block--------------------
  IOModule.ReadDigital();
  IOModule.ReadAnalog();

  //---------------Encoder block----------------------
  /* EncButton.update();
  byte enc_but = EncButton.fallingEdge(); // digitalRead(ENC_BUT); */

  long newPosition = IOModule.myEnc->read()/4;

  if (newPosition != oldPosition){
    D(Serial.println(newPosition);)
    
    if (newPosition > oldPosition) {
      puntero ++;
      if (puntero > 4) puntero=4;
      }          
    if (newPosition < oldPosition) {
      puntero --;
      if (puntero < 1) puntero=1;
      }
    sevseg.setNumber(puntero);
    oldPosition = newPosition;
  }
  
  //---------------7Seg block----------------------  
  sevseg.refreshDisplay(); // Must run repeatedly

  //---------------Audio block----------------------
}

/// END ///
