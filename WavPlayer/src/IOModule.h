
#ifndef IOModule_h
#define IOModule_h

class IOClass;
typedef bool (*CallB_Module_Function)(IOClass *pMod, uint8_t id);

class IOClass
{
public:
    bool Init(void);
    bool ReadAnalog(void);
    bool ReadDigital(void);
    void setOnChangeCV(CallB_Module_Function pFunc) { OnChangeCV = pFunc; }
    void setOnChangeGate(CallB_Module_Function pFunc) { OnChangeGate = pFunc; }
    void setOnChangeButt(CallB_Module_Function pFunc) { OnChangeButt = pFunc; }
    void setLED(uint8_t id, bool Status) { digitalWrite(LEDS[id], Status); }
    /* uint16_t AnagA=0, AnagB=0, AnagC=0, AnagD=0;
    bool GateStatus[2]={0};
    bool ButtStatus[3]={0}; */
    CVInput CV[4];      //< CV Inputs
    DigInput Gate[2];   // Gate Inputs
    DigInput Butt[3];   // Button inputs
    uint8_t LEDS[3] = {LED_A, LED_B, LED_C};

    DigInput EncButton;
    Encoder *myEnc;

private:
    // Used for interactions at module level (e.g. for outcome of the function more than one input is needed)
    CallB_Module_Function OnChangeButt=nullptr;
    CallB_Module_Function OnChangeCV=nullptr;
    CallB_Module_Function OnChangeGate=nullptr;
    CallB_Module_Function OnChangeEncBut=nullptr;

};

extern IOClass IOModule;


#endif