/*	Author: Dakota Heredia
 *  	Partner(s) Name: none 
 *	Lab Section: 023
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

enum States {start, init, flip}  state;	

void Tick() { switch(state) {//transitions	
unsigned char tmpb = 0x00;
unsigned char tmpa = 0x00;

case start:
state=init;
break;

case init:

tmpa=PINA&0x01;
if (tmpa==0x01) {
tmpb= (~PORTB) & 0x03;//alternate pins
PORTB = tmpb;
state = flip; }
else if (tmpa==0) {
	state = init; 
}
break;

case flip:
tmpa=PINA&0x01;
if  (tmpa==0x01) {
	state = flip; }
else if (tmpa == 0) {
	state = init; }

break;

//case wait:
//tmpa=PINA&0x01;
//state = (tmpa==1)? flip:wait;
//break;

}//transitions
	
//switch(state) {//State actions	

//case init:
//PORTB = 0x01; // initial LED is on
//break;

//case flip:
//tmpb= (~PORTB) & 0x03;//alternate pins
//PORTB = tmpb;
//break;

//case wait: break; //just wait

//}// state actions	
} //voidTick()
	
int main(void)	{	
PORTB = 0x01;        //initiliaze outputs	
state = start;   //Indicates intial call	
while(1) { Tick(); }

return 0;
}
