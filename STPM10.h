
#ifndef STPM10_H
#define STPM10_H

#define SCS PORTB.6
#define SYN PORTB.7
#define SCL PORTB.5  //SCK
#define SDA PORTB.4  //MISO
 

extern char DAP[4];
extern char DRP[4];
extern char DSP[4];
extern char DFP[4];
extern char DEV[4];
extern char DMV[4];
extern char CFL[4];
extern char CFH[4];

void read_stpm10(void);
void write_stpm10(char);
void reset_stpm10(void);
void display_stpm10(void);


#endif 