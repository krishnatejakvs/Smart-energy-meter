/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 6/26/2013
Author  : 
Company : 
Comments: 


Chip type               : ATmega88PA
Program type            : Application
AVR Core Clock frequency: 2.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <stdio.h>
#include <delay.h>
#include <stdlib.h>
#include "STPM10.h"
#include "utility.h"
#include "GlobalDefinitions.h"

#include "RTC.h"
#include <i2c.h>


  
void main(void)
{
 unsigned long int old=0;
signed long int frac=0;
signed long int integ=0;
init();
reset_stpm10();
write_stpm10(0xBF);
i2c_init();

//DS1339_init(0x00,0x45,0x14,0x02,0x01,0x07,0x13);
while (1)
      {  
        char temp,date,x,y,z,m,mnth,year;
        unsigned int c,a,b,r,s,d,e,i;
        signed int f=0; 
        float Vrms,Irms,POW,einteg,efrac,final,Imom; 
        long int pow=0,value=0;
        unsigned long int new;
        unsigned int quot;
        signed int quant;
        
    
      
             read_stpm10();
             a=DEV[0];
             b=DEV[1];
             c= (a<<8);
             d=c|b;
             d= d & 0x07FF;
             Vrms= d*0.2819;
            floattoascii(Vrms,4);
             putchar(0x20);
             r=DEV[2];
             s=DEV[3];
             e= (r<<8);
             f=e|s;
             Irms= f*0.0031;
             floattoascii(Irms,4); 

            putchar(0x20); 
             for(i=0;i<4;i++)
               { 
                
                temp=DAP[i];
                value|=temp;
                value=value<<(8*(3-i));
                pow=pow|value;
                temp=0;
                value=0;
                //putchar(DAP[i]);
                }   
            pow=pow & 0x0FFFFF00;
            pow=pow>>8;
            new=pow;  
            quant=new-old;
           
            old=new;
            frac= frac+quant;
            efrac=(frac * 3.8146);
            efrac=efrac * 0.000001;
           
             if(frac>=2621440)
             {
                integ=integ+1;               
                putchar(integ & 0xff);
                frac=frac-2621440;               
             } 
              einteg=frac*1.000;

             final=((integ*10)+efrac);

            
             floattoascii(final,4);
              putchar(0x20);
           
                
         //RTC write        
             rtc_write(0x0E,0x3E);     
           // RTC read   
            year=rtc_read(0x06);
             delay_ms(10);
             mnth=rtc_read(0x05);
             delay_ms(10);   
             date=rtc_read(0x04);
            delay_ms(10);
             x=rtc_read(0x02);
            delay_ms(10);
             y=rtc_read(0x01);
             delay_ms(10);
             m=rtc_read(0x00);
             delay_ms(10); 
             

             putchar(0x20);
             bcdToascii(date);
             putchar(0x2F); 
             bcdToascii(mnth);
             putchar(0x2F);
             bcdToascii(year);
             
             putchar(0x20);

             bcdToascii(x);
             putchar(0x3A);
             bcdToascii(y);
             putchar(0x3A);
             bcdToascii(m); 
             putchar(0x0D);
          // delay_ms(1000);
      }
}
