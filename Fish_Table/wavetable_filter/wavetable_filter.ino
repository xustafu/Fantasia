#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=341,294
AudioSynthWaveform       waveform2;      //xy=345,355
AudioFilterStateVariable filter1;        //xy=508,314
AudioOutputI2S           i2s1;           //xy=662,331
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(waveform2, 0, filter1, 1);
AudioConnection          patchCord3(filter1, 0, i2s1, 0);
AudioConnection          patchCord4(filter1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=658,182
// GUItool: end automatically generated code


// GUItool: end automatically generated code

// GUItool: end automatically generated code

//SD CARD PINS
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

int PotPort1 = A0; // select the input pins for the potentiometers
int PotPort2 = A1;
int PotPort3 = A2;
int PotPort4 = A3;

int Boton1 = 2;    // pushbutton connected to digital pinS
int Boton2 = 5; 
int Boton3 = 25; 
int Boton4 = 27; 
int Gate1 = 3; 
int Gate2 = 6; 
int Encoderbut = 4;

 // Variables to store port values 
float PotValue1 = 0; 
float PotValue2 = 0;
float PotValue3 = 0;
float PotValue4 = 0;
int BotonValue1 = 0;   
int BotonValue2 = 0;
int BotonValue3 = 0;
int BotonValue4 = 0;
int GateValue1 = 0;
int GateValue2 = 0;
int EncoderbutValue = 0;


const int16_t v1_array[256] = {-18317, -8507, 1624, 178, -8197, -10834, -13313, -15176, -16759,
-18391, -19843, -20636, -21158, -21500, -21931, -22365, -22595, -23013, -23157, -23561, 
-24020, -24257, -24493, -24024, -24306, -25886, -27201, -27584, -27809, -28338, -29520, 
-30722, -30687, -30393, -30365, -30991, -31921, -31583, -31030, -31681, -32604, -32768, 
-32058, -31497, -31423, -30648, -29462, -27731, -24909, -21081, -17061, -12863, -9943,
-7478, -4865, -2743, 155, 3490, 5805, 7619, 8992, 10630, 12605, 14289, 15797, 17085, 
18480, 20417, 22629, 24827, 26368, 27611, 28975, 30194, 31080, 31938, 32734, 32768, 
32552, 32262, 31765, 31129, 30441, 29581, 28465, 27029, 25131, 22949, 20704, 18594, 
16869, 15496, 14610, 14053, 13633, 13488, 13817, 14041, 14143, 14235, 14230, 14112, 
13952, 13960, 14052, 14439, 14605, 15402, 16406, 17082, 18377, 19622, 20716, 21403, 
21352, 20839, 19949, 18828, 17349, 15334, 13057, 10670, 8034, 5224, 2359, -440, -3058,
-5737, -8316, -10456, -12372, -13821, -15108, -15804, -15164, -14109, -12228, -9191, 
-5891, -2556, 1137, 4922, 8848, 12267, 15227, 17991, 20490, 22618, 23934, 25049, 25929,
26091, 26195, 25793, 24881, 24037, 22857, 21597, 20072, 18276, 16362, 14390, 12624, 10633,
8557, 6490, 4502, 2692, 757, -843, -2088, -2990, -3577, -3426, -3157, -2066, -236, 1379,
2952, 5261, 7204, 8641, 10164, 11715, 12906, 13858, 14666, 15467, 15675, 16015, 16934, 
17871, 18591, 18886, 18917, 18682, 18460, 17985, 16875, 15481, 14030, 12458, 10692, 
8978, 7345, 5756, 4194, 2792, 1666, 738, -56, -599, -209, 230, 1365, 2435, 3364, 4227, 
5452, 6594, 7544, 8595, 10007, 11472, 13101, 14400, 15432, 16682, 17964, 18954, 19566, 
20163, 20126, 19686, 19041, 18211, 17585, 16379, 14782, 12933, 10661, 8393, 6224, 3937, 
1264, -1255, -3376, -4913, -6327, -7932, -9668, -11171, -12639, -13968, -15141, -15843};



const int16_t phi1_array[256] =  {21774, 19862, 18714, 18866, 20243, 22013, 23116, 22653, 
20199, 16525, 12576, 9537, 7807, 6905, 5880, 4660,3171, 1439, -955, -4181, -8185, -12761,
-17459, -22675, -27109, -29937, -29186, -24614, -17684, -10087, -3037, 2881, 7589, 11266,
13478, 14495, 14799, 15159, 16237, 17808, 19900, 21983, 23846, 25332, 26534, 27513, 27641, 
26970, 25918, 24854, 24266, 23999, 24042, 24078, 24074, 23971, 24016,23942, 23519, 22552, 
21385, 20854, 21250, 22561, 24401, 26413, 27859, 28682, 28860, 28986, 29100, 29066, 28814,
28193, 27532, 26991, 26752, 26886, 27547, 27997, 27954, 27506, 27110, 27507, 28623, 30103, 
31120, 31482, 31417, 31375, 31510, 31853, 32222, 32346, 32456, 32531, 32711, 32768, 32757, 
32413, 31867, 31032, 29984, 28857, 28199, 28269, 28932, 29793, 30462, 30745, 30523, 30140, 
29554, 29131, 28691, 27895, 27293, 26809, 26324, 26372, 26945, 27942, 28738, 29309, 29188,
28596, 27730, 27185, 27335, 27745, 28131, 27745, 26889, 25683, 24909, 25168, 26121, 27371, 
28165, 28224, 27440, 25749, 23339, 20749, 18648, 17044, 16761, 17597, 18826, 20033, 20794, 
20987, 20396, 19241, 16881, 13450, 8898, 4681, 1684, 757, 2307, 5432, 8922, 11261, 12330, 
11510, 8246, 2477, -5625, -15091, -23973, -30166, -32768, -32026, -28788, -24747, -20523, 
-15793, -10958, -6914, -4215, -2986, -2546, -1338, 1118, 5002, 8983, 11975, 13569, 14036, 
13910, 14319, 15947, 18731, 22356, 25790, 28129, 28982, 28654, 27673, 26810, 26312, 26041,
25624, 24867, 23959, 23173, 23094, 23709, 24537, 25317, 25977, 26226, 26175, 25615, 24595,
23645,23225, 23651, 24367, 24589, 23991, 22682, 21007, 20039, 20109, 21196, 22796, 24564, 
26094, 27328, 28440, 29495, 30276, 30567, 30567, 30409,30422, 30324, 30341, 30216, 29683, 
29191, 28761, 28732, 29264, 30262, 31422, 32216, 32319, 31707, 30837, 30014, 29660, 29715, 
30033};

bool toggle = true;
int lastButtonState = 0; 
bool toggle2 = true;
int lastButtonState2 = 0;
bool toggle3 = true;
int lastButtonState3 = 0;
bool toggle4 = true;
int lastButtonState4 = 0;


void setup() {
//Audio setup
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(36);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);

  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(Boton1, INPUT_PULLUP);    // sets the digital pin 2 as input
  pinMode(Boton2, INPUT_PULLUP); 
  pinMode(Boton3, INPUT_PULLUP); 
  pinMode(Boton4, INPUT_PULLUP); 
  pinMode(Gate1, INPUT_PULLUP); 
  pinMode(Gate2, INPUT_PULLUP); 
  pinMode(Encoderbut, INPUT_PULLUP); 



  pinMode(30, OUTPUT);    
  pinMode(32, OUTPUT); 
  pinMode(33, OUTPUT); 
  pinMode(28, OUTPUT); 
  pinMode(31, OUTPUT); 
  pinMode(26, OUTPUT); 
  pinMode(29, OUTPUT); 
  pinMode(9, OUTPUT); 

  // Wavetable variables
  int wavetype = WAVEFORM_ARBITRARY;
  waveform1.begin(wavetype);
  waveform2.begin(wavetype);

  
  waveform1.amplitude(1);
  waveform2.amplitude(1);
  filter1.octaveControl(4);

}


void loop() {
  BotonValue1 = digitalRead(Boton1);   
  BotonValue2 = digitalRead(Boton2); 
  BotonValue3 = digitalRead(Boton3); 
  BotonValue4 = digitalRead(Boton4); 
  GateValue1 = digitalRead(Gate1); 
  GateValue2 = digitalRead(Gate2); 
  EncoderbutValue = digitalRead(Encoderbut); 

  // read the value from the pots:
  PotValue1 = (float)analogRead(PotPort1) / 1023.0;
  PotValue2 = (float)analogRead(PotPort2) / 1023.0; 
  PotValue3 = (float)analogRead(PotPort3) / 1023.0; 
  PotValue4 = (float)analogRead(PotPort4) / 1023.0;
  
  waveform1.arbitraryWaveform(v1_array, 300);
  waveform2.arbitraryWaveform(phi1_array, 200);

 if(toggle == true){
     waveform1.frequency(PotValue1*30);
     }
    if(toggle == false){
     waveform1.frequency(PotValue1*150);
    }
    if(toggle2 == true){
     waveform2.frequency(PotValue2*100);
    }
    if(toggle2 == false){
     waveform2.frequency(PotValue2*400);
    }
    if(toggle3 == true){
     filter1.frequency(60 + PotValue3*100);
    }
    if(toggle3 == false){
    filter1.frequency(60 + PotValue3*1111);
    }
    if(toggle4 == true){
     filter1.resonance(0.7 + (PotValue4*5));
    }
    if(toggle4 == false){
     filter1.resonance(0.7 + (PotValue4*1));
    }

if (BotonValue1 != lastButtonState) {
    if (BotonValue1 == HIGH) {
      toggle = !toggle;
    } 
  }
  lastButtonState = BotonValue1;
  
  if (BotonValue2 != lastButtonState2) {
    if (BotonValue2 == HIGH) {
      toggle2 = !toggle2;
    } 
  }
  lastButtonState2 = BotonValue2;
  
  if (BotonValue3 != lastButtonState3) {
    if (BotonValue3 == HIGH) {
      toggle3 = !toggle3;
    } 
  }
  lastButtonState3 = BotonValue3;
 
  if (BotonValue4 != lastButtonState4) {
    if (BotonValue4 == HIGH) {
      toggle4 = !toggle4;
    } 
  }
  lastButtonState4 = BotonValue4;
 

}
