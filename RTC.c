
#include "RTC.h"
// I2C Bus functions

#asm
   .equ __i2c_port=0x08 ;PORTC
   .equ __sda_bit=4
   .equ __scl_bit=5
#endasm
#include <i2c.h>
#include <delay.h>


void DS1339_init(char sec,char min ,char hour,char day,char date,char month,char year)
{

 rtc_write(0x0E,RTC_ENABLE_OSC);  
 rtc_write(0x00,sec);
 rtc_write(0x01,min);
 rtc_write(0x02,hour);
 rtc_write(0x03,day);
 rtc_write(0x04,date);
 rtc_write(0x05,month);
 rtc_write(0x06,year);

}

void rtc_write(unsigned char address, unsigned char data) {
    #asm("cli")
    i2c_start();
    i2c_write(RTC_ADDRESS);
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
    /* 500ms delay to complete the write operation  */ 
    delay_ms(100);
    #asm("sei")
}
unsigned int rtc_read(unsigned char address) {

    unsigned int data;
    #asm("cli")
    i2c_start();
    i2c_write(RTC_ADDRESS);
    i2c_write(address);
    i2c_start();
    i2c_write(RTC_ADDRESS | 1);
    data=i2c_read(0);
    i2c_stop();
    #asm("sei")  
    return data;
}