/*
 * Masa  Yardýmcýsý.c
 *
 * Created: 10.01.2021 16:51:10
 * Author : Enes
 
 
 
 https://www.avrfreaks.net/projects/ds1302-timekeeping-chip-library ds1302 library
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include "lcd1602.h"
#include "Keypad.h"
#include "hcsr04.h"
#include <util/delay.h>
#include <stdlib.h>







char str[50];





uint8_t sayi_gir;
uint8_t sayi_durum;
uint8_t say_;

char binler_c;
char yuzler_c;
char onlar_c;
char birler_c;

int binler_i;
int yuzler_i;
int onlar_i;
int birler_i;

int hedef;

int yapilan;

int kalan;

 
volatile char key;


int urun_varmi;
uint8_t urun_kontrol;

int main(void)
{

	//mesafe
	
	init_hcsr();
	
	///keypad
		
		key = Key_None;	
		sayi_durum=0;
		sayi_gir=0;
		say_=0;
		binler_c=0;
		yuzler_c=0;
		onlar_c=0;
		birler_c=0;
	
		binler_i=0;
	    yuzler_i=0;
	    onlar_i=0;
		birler_i=0;
		hedef=0;
		yapilan=0;
		kalan=0;
		
		urun_kontrol=0;
		urun_varmi=600;
		
		KP_Setup();
		
	////
	


	///lcd
	
	lcd1602_init();
	lcd1602_clear();
    ///
	
	

   
	
  
	
   ////
   
    while (1) 
    {
		
             
				
				///Keypad
				         key=KP_GetKey();
				


				      
						if(key=='A'&&sayi_durum!=2)
						{  //alarm kuruluyor
							lcd1602_clear();
							sayi_durum=1;
							sayi_gir=1;
							say_=1;
						}
						if(key=='B')
						{   //alarm var
							lcd1602_clear();
							binler_i=(int)binler_c-48;
							yuzler_i=(int)yuzler_c-48;
							onlar_i=(int)onlar_c-48;
							birler_i=(int)birler_c-48;
							int new_binler=binler_i*1000;
							int new_yuzler=yuzler_i*100;
							int new_onlar=onlar_i*10;
							int new_birler=birler_i*1;
							hedef=new_binler+new_yuzler+new_onlar+new_birler;
							sayi_durum=2;
							sayi_gir=0;
							
						}
						if(key=='C')
						{   //alarm yok
							lcd1602_clear();
							sayi_durum=0;
							sayi_gir=0;
						
							binler_c=0;
							yuzler_c=0;
							onlar_c=0;
							birler_c=0;
						}
						
				        if (sayi_durum==0)
				        {  
					        lcd1602_goto_xy(0,0);
					        lcd1602_send_string("HEDEF YOK");
							lcd1602_goto_xy(0,1);
							lcd1602_send_string("A AYARLAR A GIT");
				        }
				        if (sayi_durum==1)
				        {  
					        lcd1602_goto_xy(0,0);
					        lcd1602_send_string("AYAR:");
							lcd1602_goto_xy(5,0);
							lcd1602_send_string("B ONY C SIL");
							
				        }
						if (sayi_durum==2)
						{
							 
							 
                              lcd1602_goto_xy(0,0);
                              lcd1602_send_string("HEDEF:");
							  lcd1602_goto_xy(6,0);
							  itoa(hedef,str,10);
							  lcd1602_send_string(str);
							  lcd1602_goto_xy(0,1);
							  lcd1602_send_string("YAP:");
							  lcd1602_goto_xy(4,1);
							  itoa(yapilan,str,10);
							  lcd1602_send_string(str);
							   lcd1602_goto_xy(8,1);
							  lcd1602_send_string("KLN:");
							  kalan=hedef-yapilan;
							  lcd1602_goto_xy(12,1);
							  itoa(kalan,str,10);
							  lcd1602_send_string(str);
						
						
						     
		                     urun_varmi=send_echo();
							 
							 
							 if (urun_varmi<500 && urun_kontrol==0)
							 {
								  
								 lcd1602_clear();
								
								 
								 yapilan++;
								 urun_kontrol=1;
								 
							 }
							 if (urun_varmi>500)
							 {
								 urun_kontrol=0;
							 }

						
							
						}
						
						
						if(sayi_gir==1 && key!='A' && key!='B' && key!='C'&& key!='D'&& key!='E'&& key!='F')
						{
							
								
							lcd1602_goto_xy(0,1);
							lcd1602_send_string("HEDEF:");
							lcd1602_goto_xy(7,1);
							lcd1602_send_char(binler_c);
							lcd1602_goto_xy(8,1);
							lcd1602_send_char(yuzler_c);
							lcd1602_goto_xy(9,1);
							lcd1602_send_char(onlar_c);
							lcd1602_goto_xy(10,1);
							lcd1602_send_char(birler_c);
							
							
							if (say_==1 && key != Key_None)
							{
								binler_c=(char)key;
								_delay_ms(500);
								key=Key_None;
								say_++;
								
							}
							if (say_==2&& key != Key_None && binler_c!=0)
							{
								yuzler_c=(char)key;
								_delay_ms(500);
								key=Key_None;
								say_++;
	
							}
							if (say_==3&& key != Key_None &&yuzler_c!=0)
							{
								onlar_c=(char)key;
								_delay_ms(500);
								key=Key_None;
								say_++;

							}
							if (say_==4&& key != Key_None && onlar_c!=0)
							{
								birler_c=(char)key;
								key=Key_None;
								say_=0;
							}
							

							
						}
				
				
				
		
				
				

				 

				

				
				
				  
			
		}
		
    }



