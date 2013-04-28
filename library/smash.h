//
// Smash! DTMF | Library
// Copyright 2012 Hotchkissmade
// Released under the GPL
//

#ifndef Smash_h
#define Smash_h

#include "Arduino.h"

class Smash {
	public:
		Smash(int baud);
		void transmit(char message[], int length);
		void recieve();
		void dtmfize(char message[], int length);
}

#endif