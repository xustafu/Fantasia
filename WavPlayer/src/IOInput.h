#ifndef IOInput_h
#define IOInput_h


#define UNDEFPIN 0xff

class IOInput;

typedef bool (*CallB_Function)(IOInput*);

class IOInput{
public:
    bool hasChanged(void) {return bChanged;}
    int getValue(void) { return Currentval; }
    bool Init(uint8_t pin){
        bInit = true;
        _pin = pin;
        return true;
    }
    void setOnChange(CallB_Function pFunc) { OnChange = pFunc; }

protected:
    CallB_Function OnChange=nullptr;
    bool bChanged = false;
    int Currentval = 0;
    bool bInit = false;
    uint8_t _pin = UNDEFPIN;
};


class CVInput: public IOInput
{
public:
    bool Init(uint8_t pin){
        IOInput::Init(pin);
        _AnagIn = new ResponsiveAnalogRead(pin, true, 0.001);
        return true;
    }
    bool ReadInput();
    void setThreshold(uint8_t Thr) { _Chgthreshold = Thr; }

private:
    //int Previousval = 0;
    ResponsiveAnalogRead *_AnagIn=nullptr;
    uint8_t _Chgthreshold=1;
};


class DigInput: public IOInput
{
public:
    bool Init(uint8_t pin){
        IOInput::Init(pin);
        _DigIn = new Bounce(pin, DEBOUNCEMILS);
        pinMode(pin, INPUT_PULLUP); //pull up for digital input
        return true;
    }
    bool ReadInput();
private:
    Bounce *_DigIn=nullptr;
};



#endif