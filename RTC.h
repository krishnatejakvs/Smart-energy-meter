
#ifndef DS1339_H
#define DS1339_H




#define RTC_ADDRESS        0b11010000
#define RTC_ENABLE_OSC  0x3E


void rtc_write(unsigned char address, unsigned char data);
unsigned int rtc_read(unsigned char address);
void DS1339_init(char sec,char min ,char hour,char day,char date,char month,char year);


#endif 