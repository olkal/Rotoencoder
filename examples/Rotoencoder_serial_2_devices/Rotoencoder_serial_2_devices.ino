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
Rotoencoder RotoEnc_2(3, 6, 7, 1);

int valueToAdjust_1;
int valueToAdjust_2;

void setup() {
  Serial.begin(9600);
  if(!RotoEnc_1.begin()) Serial.println("Failed to init RotoEnc_1, no interrupt pin");
  if(!RotoEnc_2.begin()) Serial.println("Failed to init RotoEnc_2, no interrupt pin");
}

void loop() {
  //update rotor value 1:
  int rotovalue;
  rotovalue = RotoEnc_1.getRotoVal();
  valueToAdjust_1 += rotovalue;
  if (rotovalue != 0) {
    Serial.print("value_1: "); Serial.println(valueToAdjust_1);
  }
  
  //update rotor value 2:
  rotovalue = RotoEnc_2.getRotoVal();
  valueToAdjust_2 += rotovalue;
  if (rotovalue != 0) {
    Serial.print("value_2: "); Serial.println(valueToAdjust_2);
  }
  
  //update rotor switch 1:
  int switchval;
  switchval = RotoEnc_1.getSW();
  if (switchval == 3) {
    valueToAdjust_1 = 0; Serial.println("switch_1 pressed for >1 sec, value_1 reset");
  }
  else if (switchval != 0) {
    Serial.print("switch_1 value: "); Serial.println(switchval);
  }
  
  //update rotor switch 2:
  switchval = RotoEnc_2.getSW();
  if (switchval == 3) {
    valueToAdjust_2 = 0; Serial.println("switch_2 pressed for >1 sec, value_2 reset");
  }
  else if (switchval != 0) {
    Serial.print("switch_2 value: "); Serial.println(switchval);
  }
}


