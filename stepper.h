#ifndef STEPPER_H
#define STEPPER_H

void SetSpeed (int leftSpeed, int rightSpeed);
void SetSpeedDir (int leftSpeed, char dirL, int rightSpeed, char dirR);
void SetTurn (int speed, char direction, int angle);
void FollowRightWall(unsigned int speed);
void FollowLeftWall(unsigned int speed);
void FrontWall(unsigned int speed);
void DecideTurn();
void SetTurn90(unsigned int speed, char direction);
#endif
