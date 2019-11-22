/*
   Rotoencoder_Serial
   Created by Olav Kallhovd, Aug 2, 2017.
   
   Rotary encoder :
   A + B + SW must have external 10k pull up resistors
   A + B must have 0.1uF caps to ground, or even better, a RC filter for noise reduction
   The first pin in constructor (clkPin) must be hardware interrupt capable.
   1 or 2 instances (devices) can be used
   To reverse the counting, switch clkPin and dataPin, or set the stepValue to negative value.
   Switch: pressed switch returns 1, released switch returns -1. 
   If the switch is pressed for longer time the returned value will increase with 1 ea passed second
*/

#include <Rotoencoder.h>

//constructor Rotoencoder: clkPin(interrupt pin), dataPin, swPin, stepValue(stepValue can be negative value)
Rotoencoder RotoEnc_1(2, 4, 5, 1); 

int valueToAdjust;

void setup() {
  Serial.begin(9600);
  if(!RotoEnc_1.begin()) Serial.println("Failed to init RotoEnc_1, no interrupt pin");
  
  //RotoEnc_1.setSWdebounceTime(20); // library default switch debounce time is 20ms, adjust if needed
  //RotoEnc_1.setRotoDebounceTime(5); // library default encoder debounce time is 5ms, adjust if needed
}

void loop() {
  
  //update value from rotary encoder:
  int rotovalue;
  rotovalue = RotoEnc_1.getRotoVal();
  valueToAdjust += rotovalue;
  if (rotovalue != 0) {
    Serial.print("value: "); Serial.println(valueToAdjust);
  }
  
  //update switch from rotary encoder::
  int switchval;
  switchval = RotoEnc_1.getSW();
  if (switchval == 2) {
    valueToAdjust = 0; Serial.println("switch pressed for >1 sec, value reset");
  }
  else if (switchval != 0) {
    Serial.print("switch value: "); Serial.println(switchval);
  }
 
}


