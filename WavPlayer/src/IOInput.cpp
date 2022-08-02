#include "PrjIncludes.h"


bool CVInput::ReadInput(){
    if(!bInit) return false;
    _AnagIn->update();
    int newval = _AnagIn->getValue();
    //analogRead(_pin);
    if( newval/_Chgthreshold == Currentval/_Chgthreshold){
        bChanged = false;
        //Serial.printf("Input %d/%d\n", _pin, Currentval);
        return false;
    }
    bChanged = true;
    Currentval = newval;

    if(bChanged && OnChange!=nullptr) OnChange(this);
    return bChanged;
}

bool DigInput::ReadInput(){
    if(!bInit) return false;
    bChanged = _DigIn->update();
    Currentval = !_DigIn->read();

    if(bChanged && OnChange!=nullptr) OnChange(this);
    return bChanged;
}