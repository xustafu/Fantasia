#include "PrjIncludes.h"


bool IOClass::Init(void)
{
    // Init components
    analogReadResolution(10);
    CV[0].Init(CV_A);
    CV[1].Init(CV_B);
    CV[2].Init(CV_C);
    CV[3].Init(CV_D);

    Gate[0].Init(GATE_A);
    Gate[1].Init(GATE_B);

    Butt[0].Init(BUT_A);
    Butt[1].Init(BUT_B);
    Butt[2].Init(BUT_C);

    // Init LEDS
    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_C, OUTPUT);

    // Init Encoder
    myEnc = new Encoder(ENCA, ENCB);
    EncButton.Init(ENC_BUT);

    //////////////////////////
    // Define input callbacks
    EncButton.setOnChange(EncButtonChange);  // Encoder button change
    CV[3].setOnChange(CVAdjustOutputVolume); // CV D Change adjust output volume
    CV[3].setThreshold(4); // 1024/4 = 256 Volume levels
    CV[2].setOnChange(CVAdjustplayRateChange); // CV C Change play speed
    CV[2].setThreshold(32); // 1024/32 = 32 Rate levels
    CV[1].setOnChange(FilePositionChange); // CV B Change loop start position
    CV[1].setThreshold(4); // 1024/32 = 32 file positions
    CV[0].setOnChange(LoopLengthChange); // CV C Change loop length
    CV[0].setThreshold(2); // 1024/4 = 256 file positions

    // Test inputs
    D(
        //CV[0].setOnChange(PrintChanged);
        //CV[1].setOnChange(PrintChanged);
        //CV[2].setOnChange(PrintChanged);
        //CV[3].setOnChange(PrintChanged);

        Gate[0].setOnChange(PrintChanged);
        Gate[1].setOnChange(PrintChanged);
        Butt[0].setOnChange(PrintChanged);
        Butt[1].setOnChange(PrintChanged);
        Butt[2].setOnChange(PrintChanged);
    );

    ///////////////////////////
    // Define Module Callbacks
    setOnChangeButt(ModuleButtonChanged);
    setOnChangeGate(ModuleGateChanged);
    
    return true;
}


bool IOClass::ReadAnalog(void)
{
    bool bChanged = false;
    bool bRet = false;
    for (uint8_t i = 0; i < 4; i++)
    {
        bRet = CV[i].ReadInput();
        if (bRet && OnChangeCV != nullptr) OnChangeCV(this, i);
        bChanged= bChanged | bRet ;
    }

    return bChanged;
}


bool IOClass::ReadDigital(void)
{
    bool bChanged = false;
    bool bRet = false;


    bChanged = bRet = EncButton.ReadInput();
    if (bRet && OnChangeEncBut != nullptr) OnChangeEncBut(this, 0);

    for (uint8_t i = 0; i < 2;i++){
        bRet = Gate[i].ReadInput();
        if (bRet && OnChangeGate != nullptr) OnChangeGate(this, i);
        bChanged= bChanged | bRet ;
        //GateStatus[i]= Gate[i].getValue();
    }
    for (uint8_t i = 0; i < 3;i++){
        bRet = Butt[i].ReadInput();
        if (bRet && OnChangeButt != nullptr) OnChangeButt(this, i);
        bChanged= bChanged | bRet ;
        //ButtStatus[i]= Butt[i].getValue();
        }

    return bChanged;
}


IOClass IOModule;