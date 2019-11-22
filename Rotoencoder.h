/*
  Rotoencoder.h - Library for reading rotary encoders
  Max 2 devices/instances, ea rotoencoder use 1 interrupt
  Created by Olav Kallhovd, Aug 2, 2017.
*/
#ifndef Rotoencoder_h
#define Rotoencoder_h

#include "Arduino.h"

#define SWITCH_HOLD_INCR_INTERVAL 1000 

class Rotoencoder
{
	static void isr0();
	static void isr1();
	static Rotoencoder* _device[];
	static uint8_t _deviceCount;
	uint8_t _deviceIndex;
	volatile int _rotocounter;
	volatile long lastRotoTime;
	uint8_t _clkPin;
	uint8_t _dataPin;
	uint8_t _swPin;
	int _stepValue;
	bool lastSWstate = 1;
	long lastSWtime;
	bool SWhold;
	int SWholdTime;
	int SWdebounceTime = 20;
	int rotoDebounceTime = 5;
    void handleInterrupt();
	
public:
    Rotoencoder(const uint8_t clkPin, const uint8_t dataPin, const uint8_t swPin, const int stepValue); //pinA is the interrupt pin
    bool begin();
	int getRotoVal();	
	int getSW();
	int getSWholdTime();
	int setSWdebounceTime(int t);
	int setRotoDebounceTime(int t);

};

#endif