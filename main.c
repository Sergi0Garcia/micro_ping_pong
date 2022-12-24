#include <xc.h>
#include "configuration_bits.h"

#define n 4 //velocidad
#define _XTAL_FREQ  8000000
int leds[] = {0,0,0,0,0,0,0,0};
int game;
 
void inicializar () {
    int i;
    for (i = 0; i < 8; i++)
	{
        leds[i] = 0;
    }
    TRISA=0x00;
    TRISB=0b00000011;
    ANSELH=0x00;
    ANSEL=0x00;
}
void alltozero(){
        RA0=0;
        RA1=0;
        RA2=0;
        RA3=0;
        RA4=0;
        RA5=0;
        RB2=0;
        RB3=0;     
}
 
void encenderLeds (){
    RA0 = leds[0];
    RA1 = leds[1];
    RA2 = leds[2];
    RA3 = leds[3];
    RA4 = leds[4];
    RA5 = leds[5];
    RB2 = leds[6];
    RB3 = leds[7]; 
}
 
void LedsIda(){
    for(int i=2; i<6;i++)
	{
        leds[i]=1;
        encenderLeds();
        leds[i]=0;
        delay_ms(300/n);
    } 
}
 
void LedsVuelta(){
    for(int j=5; j>1; j--)
	{
        leds[j]=1;
        encenderLeds();
        leds[j]=0;
        delay_ms(300/n);
    }
}
void main() {
    inicializar(); 
    
    while (1){
    
        if (RB0==0){
            game=0;
        }
        
        if (RB1==0){
            game=1;
        }
        
        while(game==0)
		{
            leds[1]=1;
            encenderLeds();
       		delay_ms(300/n);
            if (RB0!=1)
			{
	            delay_ms (100/n);
	            leds[1]=0;
	            LedsIda();
	            leds[6]=1;
	            encenderLeds();
	            elay_ms(200/n);
	            if (RB1==0)
				{
		            delay_ms(150/n);
		            leds[6]=0;
		            LedsVuelta();
	            }
				else 
				{
		            delay_ms(200/n);
		            leds[6]=0;
		            leds[7]=1;
		            encenderLeds();
		            delay_ms(350);
		            game=2;
				}
            }
			else
			{
            	leds[1]=0;
            	leds[0]=1;
            	encenderLeds();
            	delay_ms(350/n);
            	game=2;
			}
        }
        
        while(game==1)
		{
            leds[6]=1;
            encenderLeds();
       		delay_ms(300/2);
            if (RB1!=1)
			{
            	delay_ms (100/n);
	            leds[6]=0;
	            LedsVuelta();
	            leds[1]=1;
	            encenderLeds();
	            delay_ms(200/n);
            	if (RB0==0)
				{
           			delay_ms(150/n);
            		leds[1]=0;
            		LedsIda();
            	}
				else 
				{
            		delay_ms(200/n);
            		leds[1]=0;
		            leds[0]=1;
		            encenderLeds();
		            __delay_ms(350);
		            game=2
				}
            }
			else
			{
            	leds[6]=0;
            	leds[7]=1;
            	encenderLeds();
            	delay_ms(350);
            	game=2
			}
        }
        game=2;
        leds[0]=0;
        leds[7]=0;
        if (game==2)
            alltozero();
	}
}
