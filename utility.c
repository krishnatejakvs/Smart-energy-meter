
#include <mega88a.h>
#include <delay.h>
#include <stdio.h>
#include <spi.h>
#include <i2c.h>
#include <stdlib.h>
#include "serial.h"
#include "STPM10.h"
#include "utility.h"
#include "GlobalDefinitions.h"
long int seconds;

// unsigned long int old=0;
//signed long int frac=0;
//signed long int integ=0;

void swap(char *a, char *b)
{
   char temp;
   
   temp = *b;
   *b   = *a;
   *a   = temp;   
}


 void bin2bcd( unsigned int val ) 
{   char digit[5];
  char i; 

  i = '0' - 1; 
  do 
    i++; 
  while( !((val -= 10000) & 0x8000) ); 
  digit[4] = i; 

  i = '0' + 10; 
  do 
    i--; 
  while( (val += 1000) & 0x8000 ); 
  digit[3] = i; 

  i = '0' - 1; 
  do 
    i++; 
  while( !((val -= 100) & 0x8000) ); 
  digit[2] = i; 

  i = '0' + 10; 
  do 
    i--; 
  while( (val += 10) & 0x8000 ); 
  digit[1] = i; 

  digit[0] = val | '0'; 
  
  
   putchar(digit[4]); 
   putchar(digit[3]);
   putchar(digit[2]);
   putchar(digit[1]);
   putchar(digit[0]);  
} 


void bcdToascii(unsigned char value){

    
    char tmp;
    
	tmp = value;
	tmp = tmp & 0xf0;
	tmp = tmp >> 4;
	tmp = tmp | 0x30;
	putchar(tmp);
	tmp = value;
	tmp = tmp & 0x0f;
	tmp = tmp | 0x30;
	putchar(tmp); 
    
}

void floattoascii(float x, char y)
{           char buffer1[8];
            char *str=buffer1;
             ftoa(x,y,str);
             putchar(buffer1[0]);
             putchar(buffer1[1]);
             putchar(buffer1[2]);
             putchar(buffer1[3]);
             putchar(buffer1[4]);
             putchar(buffer1[5]);
             putchar(buffer1[6]);
             putchar(buffer1[7]); 
             
}
void longinttoascii(long int x)
{        char buffer1[8];
        char *str=buffer1;
             ltoa(x,str);
             putchar(buffer1[0]);
             putchar(buffer1[1]);
             putchar(buffer1[2]);
             putchar(buffer1[3]);
             putchar(buffer1[4]);
             putchar(buffer1[5]);
             putchar(buffer1[6]);
             putchar(buffer1[7]);
 }             




int parity(unsigned char *bp)
{

        register unsigned char prty; /* temporary register */
        prty = *bp; /* take the 1st byte of data */
        prty ^= *(bp+1); /* XOR it with the 2nd byte */
        prty ^= *(bp+2); /* and with the 3rd byte */
        prty ^= *(bp+3); /* and with the 4th byte */
        prty ^= prty<<4;
        prty &= 0xF0;/* combine and remove the lower nibble */
        return (prty != 0xF0); /* returns 1, if bad parity */


}
interrupt [TIM0_COMPA] void timer0_compa_isr(void)
{
//        char temp,a,b,r,s;
//        unsigned int c,d,e,f,i; 
//        float Vrms,Irms,POW,einteg,efrac,final; 
//        long int pow=0,value=0;
//        unsigned long int new;
//        unsigned int quot;
//        signed int quant;
//        
//    
//      
//             read_stpm10();
//             a=DEV[0];
//             b=DEV[1];
//             c= (a<<8);
//             d=c|b;
//             d= d & 0x07FF;
//             Vrms= d*0.2819;
//            // floattoascii(Vrms,4);
//            // putchar(0x20);
//             r=DEV[2];
//             s=DEV[3];
//             e= (r<<8);
//             f=e|s;
//             f= f & 0x07FF;
//             Irms= f*0.0031;
//           //  floattoascii(Irms,4);  
//             for(i=0;i<4;i++)
//               { 
//                
//                temp=DAP[i];
//                value|=temp;
//                value=value<<(8*(3-i));
//                pow=pow|value;
//                temp=0;
//                value=0;
//                //putchar(DAP[i]);
//                }   
//            pow=pow & 0x0FFFFF00;
//            pow=pow>>8;
//            new=pow;  
//            quant=new-old;
//           // putchar((quant & 0xff00)>>8);
//          //  putchar(quant & 0x00ff);
//            old=new;
//            frac= frac+quant;
//            efrac=(frac * 3.8146);
//            efrac=efrac * 0.000001;
//            //floattoascii(efrac,4);
//             if(frac>=2621440)
//             {
//                integ=integ+1;               
//                putchar(integ & 0xff);
//                frac=frac-2621440;               
//             } 
////              einteg=frac*1.000;
////             floattoascii(einteg,4);
////             putchar(0x0D); 
////             putchar(integ & 0xff);
//             
////             putchar(0x0D);
////             longinttoascii(seconds);
////             putchar(0x0D);
//             final=((integ*10)+efrac);
//             floattoascii(final,4);
//             putchar(0x0D);


}
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{

      seconds++; 
}

void init()
{

// Declare your local variables here

// Crystal Oscillator division factor: 4
#pragma optsize-
CLKPR=0x80;
CLKPR=0x02;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=In Func3=Out Func2=Out Func1=In Func0=In 
// State7=0 State6=0 State5=0 State4=T State3=0 State2=0 State1=T State0=T 
PORTB=0x00;
DDRB=0xEC;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=Out 
// State6=T State5=T State4=T State3=T State2=T State1=0 State0=0 
PORTC=0x00;
DDRC=0x03;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;
// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 7.813 kHz
// Mode: CTC top=OCR0A
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x02;
TCCR0B=0x04;
TCNT0=0x00;
OCR0A=0xF5;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off

TCCR1A=0x00;
TCCR1B=0x0D;
TCNT1H=0x00;
TCNT1L=0x02;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0b00000111;
OCR1AL=0b11000001;
//OCR1A = 7812/4;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x00;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: Off
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x02;

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x02;

// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=0x00;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART0 Mode: Asynchronous
// USART Baud Rate: 9600
UCSR0A=0x00;
UCSR0B=0xD8;
UCSR0C=0x06;
UBRR0H=0x00;
UBRR0L=0x0C;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;
DIDR1=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI Type: Master
// SPI Clock Rate: 31.250 kHz
// SPI Clock Phase: Cycle Half
// SPI Clock Polarity: High
// SPI Data Order: MSB First
SPCR=0x5E;
SPSR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// I2C Bus initialization
i2c_init();
SREG=0x80;
seconds=0;

// Global enable interrupts
#asm("sei")


}