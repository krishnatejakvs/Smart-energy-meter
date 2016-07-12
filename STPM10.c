
#include <mega88a.h>
#include <stdio.h>       
#include <delay.h>
#include <spi.h>            
#include "STPM10.h"
#include "GlobalDefinitions.h"
#include "utility.h"



char DAP[4];
char DRP[4];
char DSP[4];
char DFP[4];
char DEV[4];
char DMV[4];
char CFL[4];
char CFH[4];


static void enable_spi(void);
static void diable_spi(void);



static void enable_spi()
{
     DDRB=0xEC; 
     SPCR=0x5E;  

}

static void diable_spi()
{
   SPCR=0x00;
   DDRB=0xFC;

}


void display_stpm10()
{
    char i=0;
    for(i=0;i<4;i++)
       putchar(DAP[i]); 
       putchar(0x0d);
   for(i=0;i<4;i++)
       putchar(DRP[i]);
       putchar(0x0d);
   for(i=0;i<4;i++)
       putchar(DSP[i]);
       putchar(0x0d);  
   for(i=0;i<4;i++)
       putchar(DFP[i]);
       putchar(0x0d);  
   for(i=0;i<4;i++)
       putchar(DEV[i]);
       putchar(0x0d);  
   for(i=0;i<4;i++)
       putchar(DMV[i]);
       putchar(0x0d);  
   for(i=0;i<4;i++)
       putchar(CFL[i]);
       putchar(0x0d);  
   for(i=0;i<4;i++)
      putchar(CFH[i]);
      putchar(0x0d);  
      
     
}



void read_stpm10(void)
{

   int i=0;  
 
   //Data latch to transmission reg   
   SCS=1;
   D(100);
   SYN=1;
   D(100);   
   
   SYN=0;
   D(500);
   
   SYN=1;      
   D(30);
   
   SCS=0;
   D(5);      //Reset counter 
   SYN=0;
   D(5);
   SYN=1;
   D(5);           
   
   
  // Read data from SPI global variables  
  for(i=0;i<4;i++)
     DAP[i]=spi(0);
   for(i=0;i<4;i++)
     DRP[i]=spi(0);
   for(i=0;i<4;i++)
     DSP[i]=spi(0);  
   for(i=0;i<4;i++)
     DFP[i]=spi(0);  
   for(i=0;i<4;i++)
     DEV[i]=spi(0);  
   for(i=0;i<4;i++)
     DMV[i]=spi(0);  
   for(i=0;i<4;i++)
     CFL[i]=spi(0);  
   for(i=0;i<4;i++)
     CFH[i]=spi(0);           
     
     
     //Swap data bytes 
   
     swap(&DAP[0],&DAP[3]);   swap(&DAP[1],&DAP[2]);    
     swap(&DRP[0],&DRP[3]);   swap(&DRP[1],&DRP[2]); 
     
     swap(&DSP[0],&DSP[3]);   swap(&DSP[1],&DSP[2]);    
     swap(&DFP[0],&DFP[3]);   swap(&DFP[1],&DFP[2]); 
     
     swap(&DEV[0],&DEV[3]);   swap(&DEV[1],&DEV[2]);    
     swap(&DMV[0],&DMV[3]);   swap(&DMV[1],&DMV[2]); 
     
     swap(&CFL[0],&CFL[3]);   swap(&CFL[1],&CFL[2]);    
     swap(&CFH[0],&CFH[3]);   swap(&CFH[1],&CFH[2]); 

       
//    if (parity(&DAP[0]) || parity(&DRP[0]) || /* DAP and DRP data record */
//        parity(&DSP[0]) || parity(&DFP[0]) || /* DSP and DFP data record */
//        parity(&DEV[0]) || parity(&DMV[0]) || /* DEV and DMV data record */
//        parity(&CFL[0]) || parity(&CFH[0]))   /* CFL and CFH data record */ 
//    {
//    
//            puts("Parity Failed");
//    
//    }
//    else
//    {
//        
//            puts("Parity ok!");
//    }        
//    
    
}    
    

void write_stpm10(char data)
{

    int j=0;  
    diable_spi();
     
    SYN=1;
    SCL=1;
    SCS=1; 
    SDA=1;
    D(30); 
      
       
    SCS=0;
    D(30);   
    SYN=0;
    D(30);   
       
    for(j=0;j<8;j++)
    {  
           
        SCL=0;              
               
        if((0x80 >> j)& data) 
        {
            SDA=1;
        }  
        else
        {    
            SDA=0;
        }  
               
        D(10);
        SCL=1;
        D(10);

    }       
         
                 
    SCL=0;
    D(10);
    SCL=1;
    D(10);
                         
    SYN=1;
    D(30);
    SCS=1;   
             
    enable_spi();
     
}

void reset_stpm10(void)
{

   diable_spi();
   
   SCS=1;
   SYN=1;
   SCL=1;
   SDA=1;
   D(30);   
   
   SCS=0;
   D(30);
   SYN=0;
   D(30);
   SCL=0;  
   D(30);
   SDA=0;
   D(30);
   
   
   SDA=1;
   D(30);
   SDA=0;
   D(30);
   SDA=1;
   D(60);
   
   SCL=1;
   D(30);
   SYN=1;
   D(30);
   SCS=1;     
   
   enable_spi();  

}
