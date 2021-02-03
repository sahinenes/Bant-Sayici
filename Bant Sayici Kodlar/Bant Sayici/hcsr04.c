/*
 * hcsr04.c
 *
 * Created: 27.12.2020 15:16:39
 *  Author: Enes
 */ 

#include "hcsr04.h"


uint16_t pulse;
int16_t distance;
char str[16];
uint8_t i;
 
void init_hcsr()
{
	DDRD&=~(1<<PORTD3);
	DDRD|=(1<<PORTD4);
	EIMSK|=(1<<INT1);
	EICRA|=(1<<ISC10);
	
	sei();
	TCNT1=0;
	pulse=0;
	distance=0;
	i=0;
	
	
}
int send_echo()
{
	
	PORTD|=(1<<PORTD4);
	_delay_ms(15);
	PORTD&=~(1<<PORTD4);
	distance = pulse*0.0343;
	 return distance; 


	
	
}

ISR (INT1_vect) 
{
	
   
	
	 if (i==1)
	 {
		 TCCR1B=0;
		 pulse=TCNT1;
		 TCNT1=0;
		 i=0;
	 }
	 if (i==0)
	 {
		 TCCR1B|=(1<<CS10);
		 i=1;
	 }
	

	
}