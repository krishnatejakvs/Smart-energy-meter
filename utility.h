
#ifndef UTILITY_H
#define UTILITY_H

extern long int seconds;
void init(void);
int parity(unsigned char *bp);
void swap(char*,char*);
void bcdToascii(unsigned char value);
void floattoascii(float x, char y);
void bin2bcd( unsigned int val ) ;
void longinttoascii(long int x);



#endif 