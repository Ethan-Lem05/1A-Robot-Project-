/*
This file deals with the movement of the 2 axis machine
*/
#include "PortBindings.c"
const int DRIVING_WHEEL_SPEED = 70;
const int ENCODERFLOOR2 = 1800;
const int ENCODERFLOOR1 = 2100;
const int XENCODERMIDDLE = 190;
const int XSIDE = 500;

void moveXRev(int encDist)
{
	int original = nMotorEncoder[HORIZ_AXIS_MOTOR];
	wait1Msec(500);

	motor[HORIZ_AXIS_MOTOR] = -DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[HORIZ_AXIS_MOTOR] > (encDist + original)){}

	motor[HORIZ_AXIS_MOTOR] = 0;
	wait1Msec(500);
}

void moveXFor(int encDist)
{
	int original = nMotorEncoder[HORIZ_AXIS_MOTOR];
	wait1Msec(500);

	motor[HORIZ_AXIS_MOTOR] = DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[HORIZ_AXIS_MOTOR] < (encDist + original)){}

	motor[HORIZ_AXIS_MOTOR] = 0;
	wait1Msec(500);
}

void moveYDown(int encDist)
{
	int original = nMotorEncoder[VERT_AXIS_MOTOR];
	wait1Msec(500);

	motor[VERT_AXIS_MOTOR] = -DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[VERT_AXIS_MOTOR] > (encDist+original)){}

	motor[VERT_AXIS_MOTOR] = 0;
	wait1Msec(500);
}

void moveYUp(int encDist)
{
	int original = nMotorEncoder[VERT_AXIS_MOTOR];
	wait1Msec(500);

	motor[VERT_AXIS_MOTOR] = DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[VERT_AXIS_MOTOR] < (encDist+original)){}

	motor[VERT_AXIS_MOTOR] = 0;
	wait1Msec(500);
}

void deliver()
{
	moveXRev(-700);
	moveXFor(XENCODERMIDDLE);

	motor[VERT_AXIS_MOTOR] = -80;
	while(!SensorValue[TOUCH_SENSOR_VERT])
	{
	}

	moveYUp(200);
}

void defaultPos()
{
	deliver();

	moveYUp(ENCODERFLOOR1);
}

void spinWheel()
{
	motor[MESHED_WHEEL_MOTOR] = 20;
	wait1Msec(2000);

	motor[MESHED_WHEEL_MOTOR] = 0;
	wait1Msec(500);
}

void resetPos()
{
	nMotorEncoder[HORIZ_AXIS_MOTOR] = 0;
	nMotorEncoder[VERT_AXIS_MOTOR] = 0;
	defaultPos();
	nMotorEncoder[HORIZ_AXIS_MOTOR] = 0;
	nMotorEncoder[VERT_AXIS_MOTOR] = 0;
}

void getDrink(int module)
{
	eraseDisplay();
	displayBigTextLine(5, "Resetting");
	resetPos();

	eraseDisplay();
	displayBigTextLine(5, "Getting Drink");
	switch(module)
	{
		case 1:
			moveYUp(ENCODERFLOOR1);
			moveXFor(XSIDE);
			break;
		case 2:
			moveYUp(ENCODERFLOOR1);
			moveXRev(-XSIDE);
			break;
		case 3:
			moveYDown(-300);
			moveXFor(XSIDE);
			break;
		case 4:
			moveYDown(-300);
			moveXRev(-XSIDE);
			break;
	}

	eraseDisplay();
	displayBigTextLine(5, "Obtaining");
	moveYUp(200);
	spinWheel();
	moveYDown(-200);

	eraseDisplay();
	displayBigTextLine(5, "Delivering");
	deliver();
	moveXRev(-XSIDE);
}
