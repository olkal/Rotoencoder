# Rotoencoder

	Arduino library for reading rotary encoder with switch

	1 or 2 instances (devices) can be used, the first pin in the constructor (clkPin) must be hardware interrupt capable.
	To reverse the counting, switch around clkPin and dataPin, or set the stepValue to negative value.
	
	Switch: pressed switch returns 1, released switch returns -1. 
	If the switch is pressed for longer time the returned value will increase with 1 ea passed second

	A + B + SW must have external 10k pull up resistors
	A + B must have 0.1uF caps to ground, or even better, a RC filter for noise reduction
	

