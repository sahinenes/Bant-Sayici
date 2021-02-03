/*
 * hcsr04.h
 *
 * Created: 27.12.2020 15:16:46
 *  Author: Enes
 */ 
#ifndef hcsr04_h
#define hcsr04_h
#ifndef F_CPU
#define F_CPU 16000000
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
void init_hcsr();
int send_echo();
#endif