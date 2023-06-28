/*
  Rotoencoder.cpp - Library for reading rotary encoders
  Created by Olav Kallhovd, Aug 2, 2017.
*/

#include <Rotoencoder.h>

Rotoencoder* Rotoencoder::_device[] = {0, 0};
uint8_t Rotoencoder::_deviceCount = 0;

//constructor:
Rotoencoder::Rotoencoder(const uint8_t clkPin, const uint8_t dataPin, const uint8_t swPin, const int stepValue)  //clkPin is the interrupt pin
{
	_clkPin = clkPin;
	_dataPin = dataPin;
	_swPin = swPin;
	_stepValue = stepValue;
	_deviceIndex = 0xff;
}

bool Rotoencoder::begin() 
{
	int _intnum = digitalPinToInterrupt(_clkPin);
	if (_intnum == NOT_AN_INTERRUPT)
	return false;
	pinMode(_clkPin, INPUT_PULLUP); pinMode(_dataPin, INPUT_PULLUP); pinMode(_swPin, INPUT_PULLUP);
	if (_deviceCount <= 1)
	    _deviceIndex = _deviceCount++;
	else
	    return false; // Too many devices
	_device[_deviceIndex] = this;
    if (_deviceIndex == 0)
		attachInterrupt(_intnum, isr0, FALLING);
    else if (_deviceIndex == 1)
		attachInterrupt(_intnum, isr1, FALLING);
	return true;
}



// ISR glue routines
void Rotoencoder::isr0()
  {
	if (_device[0])
	_device[0]->handleInterrupt();
  }  
  
  void Rotoencoder::isr1()
  {
	if (_device[1])
	_device[1]->handleInterrupt();
  }  
  
void Rotoencoder::handleInterrupt() {
  //uint8_t _sreg;
  //_sreg = SREG;
  if (millis() > (lastRotoTime + rotoDebounceTime)) {
	uint8_t _data;
	_data = digitalRead(_dataPin);
    if (!_data) { //_dataPin is LOW
      _rotocounter += _stepValue;
    }
    else { //_dataPin is HIGH
      _rotocounter -= _stepValue;
    }
    lastRotoTime = millis();
  }
  //SREG = _sreg;
}

int Rotoencoder::getRotoVal() {
  noInterrupts();
  int v = _rotocounter;
  _rotocounter = 0;
  interrupts();
  return v;
}

int Rotoencoder::getSW() {
  bool swstate = digitalRead(_swPin);
  int sw = 0;
  if (swstate != lastSWstate) {
    if ((lastSWtime + SWdebounceTime) < millis()) {
      if (!swstate) { //knob has been pressed
        sw = 1;
        SWhold = true;
        SWholdTime = 0;
      }
      else { //knob has been released
        SWhold = false; {
          sw = -1;
        }
      }
      lastSWstate = swstate;
      lastSWtime = millis();
    }
  }
  else if (SWhold) { //knob is still pressed 
    long t = (millis() - lastSWtime);
    if ((SWholdTime + SWITCH_HOLD_INCR_INTERVAL) < t) {
      sw = 1 + (t / SWITCH_HOLD_INCR_INTERVAL);
      SWholdTime = t;
    }
  }
  return sw;
}

void Rotoencoder::setSWdebounceTime(int t) {
	SWdebounceTime = t;
}

void Rotoencoder::setRotoDebounceTime(int t) {
	rotoDebounceTime = t;
}
