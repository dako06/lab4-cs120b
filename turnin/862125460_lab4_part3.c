/*	Author: Dakota Heredia
 *  	Partner(s) Name: none 
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, init, pound, wait, lock}  state;	
unsigned char tmp = 0x00;
void Tick() {

//state transitions
switch(state) {

case start:
state = init;
break;

case init: 
tmp = PINA & 0x87;
if (tmp == 0x04) {
	state = pound;}

else if (tmp == 0x80) { 
	state = lock; }
break; 

case pound: 
tmp = PINA & 0x87;

if (tmp == 0x04) {
	state = pound; }

else if (tmp == 0x00) {
	state = wait; }

else if (tmp == 0x80) {
	state = lock; }

else { state = init; }

break;

case wait:
tmp = PINA & 0x87;

if (tmp == 0x02) {
	PORTB = 0X01;
	state = init; }

else if (tmp == 0x00) {
	state = wait; }

else if (tmp == 0x80)  {
	state = lock; }
else 
	{ state = init; }
break; 


case lock:
state = init; 
break;

}

//state actions
switch(state) { 	

	
case start:	
break;

case init:
PORTD = 0x01;
break;

case pound:
PORTD = 0x02;
break;

case wait:
PORTD = 0x04;
break;


case lock:
PORTD = 0x08;
PORTB = 0x00; 
break;

}} //voidTick()
	
int main(void) {
DDRA = 0x00; PORTA = 0x00;
DDRB = 0xFF; PORTB = 0x00;
DDRD = 0xFF; PORTD = 0x00; 
state = start;	
while(1) { Tick(); }
return 1;
}
