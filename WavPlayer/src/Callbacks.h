#ifndef Callbacks_h
#define Callbacks_h

bool FilePositionChange(IOInput *pBut);
bool LoopLengthChange(IOInput *pBut);
bool EncButtonChange(IOInput *pBut);
bool CVAdjustOutputVolume(IOInput *pInput);
bool CVAdjustplayRateChange(IOInput *pBut);
bool PrintChanged(IOInput *pInput);

bool ModuleButtonChanged(IOClass *pMod, uint8_t id);
bool ModuleGateChanged(IOClass *pMod, uint8_t id);

#endif