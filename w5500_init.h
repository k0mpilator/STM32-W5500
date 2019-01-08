#ifndef __W5500_INIT_H__
#define __W5500_INIT_H__

void Delay(volatile unsigned int nCount);
void myprintf(char *fmt, ...);
void W5500_Init(void);
void display_Net_Info();
void Net_Conf();
void Net_Conn ();

#endif
