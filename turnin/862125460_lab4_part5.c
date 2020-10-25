/*	Author: Dakota Heredia
 *  	Partner(s) Name: none 
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, wait, read, lock}  state;	
unsigned char tmp = 0x00;
unsigned char i;
unsigned char cnt = 0x00;
unsigned char check = 0x00;
unsigned char result = 0x00;

char code[] ={ 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01};
char input[8];

void Tick() {

//state transitions
switch(state) {

case start:
state = wait;
break;

case wait:
tmp = PINA & 0x87;
if (tmp== 0x80) {
	state = lock; }
else {
	state = (cnt == 7) ? read : wait;
}

break; 

case read:

tmp = PINA & 0x87;
if (tmp == 0x80) {
        state = lock; }
	else { state = wait; }

break; 

case lock:
state = wait; 
break;

}

//state actions
switch(state) { 	
case start:	
break;

case wait:

tmp = PINA & 0x87;

if (cnt<8) {
	input[cnt] = tmp;
	cnt++; }

else if (cnt==8) {
	cnt=0; }

break;


case read:

for (i=0; i<8 ;i++) {
	if (input[i] == code[i]) {
		check++; }
}

result = (check == 8) ? ((~PINB) & 0x01) : PINB ;
PORTB = result;
		
break;

case lock:
PORTB = 0x00;
break;

}} //voidTick()

int main(void) {
DDRA = 0x00; PORTA = 0x00;
DDRB = 0xFF; PORTB = 0x00;
//DDRD = 0xFF; PORTD = 0x00; 
PORTB = 0x00;
state = start;	

while(1) { Tick(); }
return 1;
}

