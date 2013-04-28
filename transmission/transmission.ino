//
// Smash! DTMF | Test Transmission
// Copyright 2012 Hotchkissmade
// Released under the GPL.
//

const int BAUD = 15;

void setup() {
	//
	// Pin Mapping for ATmega168/328. Not portable.
	// (http://www.arduino.cc/en/Reference/PortManipulation)
	//
	DDRB = B00111111;
}


void loop() {
	char test[] = "010020";
	
	transmit(test, sizeof(test));
	
	delay(10000);
}


void transmit(char command[], int length) {

	//
	// Per TP5088N, Logic levels are inverted.
	// (Directly driven - no transistor magic)
	//

	int time = ( 1000 / BAUD ) / 2;

	for ( int i = 0; i < length; i++ ) {
		switch ( command[i] ) {
			case '1':
				PORTB = B00001111;
				break;
			case '2':
				PORTB = B00010111;
				break;
			case '3':
				PORTB = B00000111;
				break;
			case '4':
				PORTB = B00011011;
				break;
			case '5':
				PORTB = B00001011;
				break;
			case '6':
				PORTB = B00010011;
				break;
			case '7':
				PORTB = B00000011;
				break;
			case '8':
				PORTB = B00011101;
				break;
			case '9':
				PORTB = B00001101;
				break;
			case '0':
				PORTB = B00010101;
				break;
			case '*':
				PORTB = B00000101;
				break;
			case '#':
				PORTB = B00011001;
				break;
			case 'A':
				PORTB = B00001001;
				break;
			case 'B':
				PORTB = B00010001;
				break;
			case 'C':
				PORTB = B00000001;
				break;
			case 'D':
				PORTB = B00011111;
				break;
		}

		delay(time);
		PORTB = B00000000;		
		delay(time);
	}
}