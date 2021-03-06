/*	Author: Dakota Heredia
 *  	Partner(s) Name: none 
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, wait, inc, dec, clr}  state;	
unsigned char tmp= 0x00;
unsigned char tmp2 = 0x00;
void Tick() {

switch(state) {//transitions

case start:
state=wait;
break;


case wait: 
tmp = PINA & 0x03;
tmp2 = PINC & 0x0F;
if (tmp==0x01) {
	if (tmp2 < 0x09) {
		++tmp2; 
	}
	PORTC = tmp2;
	state = inc;
}

else if (tmp==0x02) {
	if (tmp2 > 0x01) {
		--tmp2;
	}
	PORTC = tmp2;
	state = dec;}

else if (tmp==0x03) {
	PORTC = 0x00;
	state = clr;}

else {
	state = wait;}

break; 
   
case inc: 
tmp = PINA & 0x03;

if (tmp==0x01)
{  state = inc;}
else if (tmp==0x03 ) {
	PORTC = 0x00;
      	state = clr;
}

else {
	state = wait;
}
break;


case dec:
tmp = PINA & 0x03;

if (tmp==0x02) { 
       	state = dec;
}

else if (tmp==0x03 ) {
        PORTC = 0x00;
        state = clr;
}

else {
        state = wait;
}

break; 


case clr:
state = wait;
break;




}//transitions
	
switch(state) {//State actions	

case start:
break;

case wait:
break;

case inc:
break;

case dec: 
break;


case clr:
PORTC = 0x00; 
break;

}// state actions	
} //voidTick()
	
int main(void) {	
DDRA = 0x00; PORTA = 0xFF;
DDRC = 0xFF; PORTC = 0x07; 	
state = start;	

while(1) 
{ Tick(); }

return 1;
}
