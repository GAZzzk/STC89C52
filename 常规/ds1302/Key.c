#include <REGX52.H>
#include "Delay.h"
#define Key1 P3_1
#define Key2 P3_0
#define Key3 P3_2
#define Key4 P3_3

unsigned char Key_Scan()
{
	unsigned char KeyNumber=0;
	if(Key1 == 0){Delayms(20);while(Key1==0);Delayms(20);KeyNumber=1;}
	if(Key2 == 0){Delayms(20);while(Key2==0);Delayms(20);KeyNumber=2;}
	if(Key3 == 0){Delayms(20);while(Key3==0);Delayms(20);KeyNumber=3;}
	if(Key4 == 0){Delayms(20);while(Key4==0);Delayms(20);KeyNumber=4;}
	return KeyNumber;
}