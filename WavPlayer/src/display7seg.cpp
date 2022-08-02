
#include "PrjIncludes.h"


void display7seg::init(void){
        byte numDigits = 1;
        byte digitPins[] = {};
        byte segmentPins[] = {30, 32, 33, 28, 31, 26, 29, 9};
        bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
        byte hardwareConfig = COMMON_ANODE; // See README.md for options
        bool updateWithDelays = false; // Default 'false' is Recommended
        bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
        bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

        SevSeg::begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
        updateWithDelays, leadingZeros, disableDecPoint);
        setBrightness(90);

        sevseg.setNumber(1);
};

display7seg sevseg; //Instantiate a seven segment controller object
