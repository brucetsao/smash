//
// Smash! DTMF | Recieve Serial
// Copyright 2012 Hotchkissmade
// Released under the GPL.
//
// Pin Mapping
// - 8: Trigger
// - 9-12: Parallel Data In
//

const int BAUD = 18;


void setup() {
	DDRB = B00000000;
	
	Serial.begin(9600);
}


void loop() {
	int time = (1000 / BAUD) / 2;
	
	while( PINB & 0 );
	
	switch( PINB ) {
		case 3:
			Serial.print("1");
			break;
		case 5:
			Serial.print("2");
			break;
		case 7:
			Serial.print("3");
			break;
		case 9:
			Serial.print("4");
			break;
		case 11:
			Serial.print("5");
			break;
		case 13:
			Serial.print("6");
			break;
		case 15:
			Serial.print("7");
			break;
		case 17:
			Serial.print("8");
			break;
		case 19:
			Serial.print("9");
			break;
		case 21:
			Serial.print("0");
			break;
		case 23:
			Serial.print("*");
			break;
		case 25:
			Serial.print("#");
			break;
		case 27:
			Serial.print("A");
			break;
		case 29:
			Serial.print("B");
			break;
		case 31:
			Serial.print("C");
			break;
		case 33:
			Serial.print("D");
			break;
	}
	
	delay(time);
}