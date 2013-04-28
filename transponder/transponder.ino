//
// Smash! DTMF | GPS Transponder
// Copyright 2012 Hotchkissmade
// Released under the GPL.
//
// This code uses port manipulation 
// rather than the write function to
// keep this as snappy as possible.
// Only works on ATmega168/328 (Uno)
//
// Pin Mapping:
// - 3: GPS in
// - 4: GPS out
// - 8: Trigger
// - 9-12: Parallel Data Out
//
#include <SoftwareSerial.h>

const int BAUD = 15;
SoftwareSerial GPS(3, 4);

 
void setup() {
	//
	// Pin Mapping for ATmega168/328. Not portable.
	// (http://www.arduino.cc/en/Reference/PortManipulation)
	//
	DDRB = B00111111;
	
	GPS.begin(4800);
	Serial.begin(9600);
}


void loop() {
	char lat[9];
	char lon[9];
	char position[42];
	boolean reading = true;
	
	// Let the record state that NMEA is the largest pain in the ass evarrr.
	
	callsign();
	
	while ( reading ) {
		
		String NMEA;
		
		if ( GPS.available() ) {
			char now = GPS.read();
			NMEA = NMEA + now;
		
			if ( now == 10 ) { // Part of the CRLF
				if ( NMEA.startsWith("$GPGGA") ) {
						//
						// We still need to cut the other crap that fills our buffer.
						//
							
						int p[14];
						int i = 0;
						
						for (int x = 0; x < NMEA.length(); x++ ) {
							if ( NMEA.charAt(x) == ',' ) {
								p[i] = x;
								
								i++;
							}
							
							if ( NMEA.charAt(x) == '.' ) {
								NMEA.setCharAt(x, '*');
							}
						}
						
						if ( p[3] - p[2] > 1 ) {
							String lat = NMEA.substring(p[1] + 1, p[2]);
							String lon = NMEA.substring(p[3] + 1, p[4]);
							String alt = NMEA.substring(p[8] + 1, p[9]);
							
							String combined = "D" + lat + lon + alt;
							
							combined.toCharArray(position, 42);
						} else {
							position[0] = 'D';
							position[1] = '0';
						}
							
						transmit(position, sizeof(position));
						
						reading = false;
				}		
			}
	  	}
	}
	
	delay(5000);
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


char untangle(char string[], int length) {
	
}

void dot() {
  tone(7, 600);
  delay(75);
  noTone(7);
  delay(75);
}

void dash() {
  tone(7, 600);
  delay(150);
  noTone(7);
  delay(75);
}

void callsign() {
  //
  // We're not flying secrets now.
  //

  dash(); dot(); dash();               // K
  dash(); dot(); dash();               // K
  dot(); dot(); dot(); dot(); dash();  // 4
  dot(); dot(); dash(); dot();         // F
  dot(); dot(); dot(); dash();         // V
  dot(); dot(); dot(); dot();          // H
}