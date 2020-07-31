/*	Author: Trung Lam
 *	Lab Section: B22
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, init, onPress, onRelease, offPress} state;

void tick(){
	unsigned char button = PINA & 0x01;
	unsigned char leds = 0;

	switch(state) {
		case start:
			state = init;
			break;
		case init:
			state = button ? onPress : init;
			break;
		case onPress:
			state = button ? onPress : onRelease;
			break;
		case onRelease:
			state = button ? offPress : onRelease;
			break;
		case offPress:
			state = button ? offPress : init;
		default:
			state = start;
			break;
	}

	switch(state) {
		case init:
                        leds = 1;
                        break;
                case onPress:
                        leds = 2;
			break;
		case onRelease:
			leds = 2;
                        break;
		case offPress:
			leds = 1;
			break;
	}

	PORTB = leds;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
   	while (1) {
		tick();
    	}
    	return 1;
}
