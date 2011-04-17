#include <p24HJ128GP210A.h>
#include "pins.h"
#include "timer.h"
#include "stepper.h"
#include "adc_read.h"
#include "statemachine.h"

float front = 0, rightF = 0, rightR = 0, leftF = 0, leftR = 0, temp = 0;
float angleConv = 4.074;

void SetSpeed (int leftSpeed, int rightSpeed)
{
	if(leftSpeed == 0)
	{
		PR2 = 0;
	}
	else
	{	
		PR2 = leftSpeed*-27+30000;
	}
	if(rightSpeed == 0)
	{
		PR3 = 0;
	}
	else
	{		
		PR3 = rightSpeed*-27+30000;
	}	
}

//sets speed and direction
//direction 0: Forward; 1: Backward
void SetSpeedDir (int leftSpeed, char dirL, int rightSpeed, char dirR)
{
	Dir_L = dirL;
	Dir_R = dirR;
	PR2 = leftSpeed*-27+30000;
	PR3 = rightSpeed*-27+30000;
}

void SetTurn (int speed, char direction, int angle)
{
	resetDistances();
	unsigned int convertAngle;
	convertAngle = (int)(angleConv * angle);
	if((direction == 0)) //CW
	{	
		SetSpeedDir (speed, 0, speed, 1);
	}
	else //CCW
	{
		SetSpeedDir (speed, 1, speed, 0);
	}
	while(getDistanceL() < convertAngle){} //keep turning on angle is reached
	
	SetSpeed(0,0);
}

//follow right wall 
void FollowRightWall (unsigned int speed)
{
	front = Adc_IR(IR_FR);
	front = Adc_IR(IR_FR);
	LED1=~LED1;
	rightF = Adc_IR(IR_RI_F);
	rightF = Adc_IR(IR_RI_F);
	LED1=~LED1;
	rightR = Adc_IR(IR_RI_R);
	rightR = Adc_IR(IR_RI_R);
	LED1=~LED1;
	leftF = Adc_IR(IR_LE_F);
	leftF = Adc_IR(IR_LE_F);
	LED1=~LED1;
	leftR = Adc_IR(IR_LE_R);
	leftR = Adc_IR(IR_LE_R);
	LED1=~LED1;
	
	if(front < 6)
	{
		SetSpeedDir(660, 1, 660, 0);	//SetSpeedDir(250, 0, speed, 0);	
	}	
	else if(rightF > 7)
	{
		SetSpeedDir(speed, 0, 660, 0);
	}
	else if((rightF-rightR) < -1)
	{
		SetSpeedDir(660, 0, speed, 0);
	}
	else if((rightF-rightR) > 1)
	{
		SetSpeedDir(speed, 0, 660, 0);
	}
	else
	{
		SetSpeedDir(speed, 0, speed, 0);
	}	
}

void FollowLeftWall(unsigned int speed)
{
	front = Adc_IR(IR_FR);
	front = Adc_IR(IR_FR);
	LED1=~LED1;
	rightF = Adc_IR(IR_RI_F);
	rightF = Adc_IR(IR_RI_F);
	LED1=~LED1;
	rightR = Adc_IR(IR_RI_R);
	rightR = Adc_IR(IR_RI_R);
	LED1=~LED1;
	leftF = Adc_IR(IR_LE_F);
	leftF = Adc_IR(IR_LE_F);
	LED1=~LED1;
	leftR = Adc_IR(IR_LE_R);
	leftR = Adc_IR(IR_LE_R);
	LED1=~LED1;
	
	if(front < 6)
	{
		SetSpeedDir(660, 0, 660, 1);	//SetSpeedDir(250, 0, speed, 0);	
	}	
	else if(leftF > 7)
	{
		SetSpeedDir(0, 0, speed, 0);
	}
	else if((leftR-leftF) > 1)
	{
		SetSpeedDir(speed, 0, 0, 0);
	}
	else if((leftF-leftR) > 1)
	{
		SetSpeedDir(0, 0, speed, 0);
	}
	else
	{
		SetSpeedDir(speed, 0, speed, 0);
	}	
}

void FrontWall(unsigned int speed)
{
	front = Adc_IR(IR_FR);
	front = Adc_IR(IR_FR);
	LED1=~LED1;
	SetSpeedDir(speed, 0, speed, 0);
	while(front>7)
	{
		front = Adc_IR(IR_FR);
		front = Adc_IR(IR_FR);
		LED1=~LED1;
	}
	SetSpeed(0,0);
}

void DecideTurn()
{
	rightF = Adc_IR(IR_RI_F);
	rightF = Adc_IR(IR_RI_F);
	LED1=~LED1;
	rightR = Adc_IR(IR_RI_R);
	rightR = Adc_IR(IR_RI_R);
	LED1=~LED1;
	leftF = Adc_IR(IR_LE_F);
	leftF = Adc_IR(IR_LE_F);
	LED1=~LED1;
	leftR = Adc_IR(IR_LE_R);
	leftR = Adc_IR(IR_LE_R);
	LED1=~LED1;
	if(rightF>15 && rightR > 15)
	{
		setMainState(5);
	}
	else if(leftF > 15 && leftR > 15)
	{
		setMainState(6);
	}
	else
	{
		SetTurn90(700, 0);
	}
}				

void SetTurn90(unsigned int speed, char direction)
{
	rightF = Adc_IR(IR_RI_F);
	rightF = Adc_IR(IR_RI_F);
	LED1=~LED1;
	rightR = Adc_IR(IR_RI_R);
	rightR = Adc_IR(IR_RI_R);
	LED1=~LED1;
	leftF = Adc_IR(IR_LE_F);
	leftF = Adc_IR(IR_LE_F);
	LED1=~LED1;
	leftR = Adc_IR(IR_LE_R);
	leftR = Adc_IR(IR_LE_R);
	LED1=~LED1;
	SetTurn(speed, direction, 60);
	if(direction == 0)
	{
		while(leftF > (leftR+0.1) || leftF < (leftR-0.1))
		{
			SetSpeedDir(speed, 0, speed, 1);
			leftF = Adc_IR(IR_LE_F);
			leftF = Adc_IR(IR_LE_F);
			LED1=~LED1;
			leftR = Adc_IR(IR_LE_R);
			leftR = Adc_IR(IR_LE_R);
			LED1=~LED1;
		}
		SetSpeed(0,0);
	}
	else if (direction == 1)
	{
		while(rightF > (rightR+0.1) || rightF < (rightR-0.1))
		{
			SetSpeedDir(speed, 0, speed, 1);
			rightF = Adc_IR(IR_RI_F);
			rightF = Adc_IR(IR_RI_F);
			LED1=~LED1;
			rightR = Adc_IR(IR_RI_R);
			rightR = Adc_IR(IR_RI_R);
			LED1=~LED1;
		}
		SetSpeed(0,0);
	}		
}
