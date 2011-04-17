#include "pins.h"
#include <p24HJ128GP210A.h>
#include "adc_read.h"

char go_now = 0, start_state = 0;
unsigned int soundQuiet = 0, soundCounter = 0;

void start()
{
	int temp = 0;
	if(STARTSWITCH && start_state == 0)
	{
		while(temp < 500)
		{
			if(!STARTSWITCH)
			{
				temp++;
			}
			else
			{
				temp = 0;
			}
		}
		start_state = 3;
	}
	if(start_state == 3)
	{
		go_now = 1;
		PR5 = 0x1C1D;
		start_state = 4;
	}	 
}

char get_start_state()
{
	return start_state;
}

void set_start_state(char sss)
{
	start_state = sss;
}	
		
char go()
{
	return go_now;
}
