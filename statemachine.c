#include <p24HJ128GP210A.h>
#include "pins.h"
#include "adc_read.h"
#include "stepper.h"
#include "start_command.h"
#include "timer.h"

unsigned int state = 0, comingfrom = 0, spray = 0;
unsigned int countLightL = 0, countLightR = 0, countLightRe = 0;
const unsigned int NORMSPEED = 943;

void stateOfDeepThought()
{	
	if(state == 0)
	{
//		SetSpeedDir(NORMSPEED, 0, NORMSPEED, 0);
FollowRightWall(NORMSPEED);
	}	
	else if(state == 1)
	{
		FollowRightWall(NORMSPEED);	
	}
	else if(state == 2)
	{
		FollowLeftWall(NORMSPEED);
	}
	else if (state == 3)
	{
		FrontWall(NORMSPEED);
		state = 4;
	}
	else if (state == 4)
	{
		//decide turn
		DecideTurn();
	}
	else if (state == 5)
	{
		SetTurn90(700, 0);
		state = 3;
	}
	else if (state == 6)
	{
		SetTurn90(700, 1);
		state = 3;
	}		
		
}	

void setMainState(unsigned int stateGoto)
{
	state = stateGoto;
}
