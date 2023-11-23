/*
This file deals with the movement of the 2 axis machine
*/
#include "PortBindings.c"
const int NUM_MODULES = 4;
const float WHEEL_DIAMETER = 2.75;
const int DRIVING_WHEEL_SPEED = 30;

float xCoords[NUM_MODULES];
float yCoords[NUM_MODULES];

/*
initializes the coordinates of the robot
*/
void initializeCoordinates() {
		for(int i = 0; i < NUM_MODULES; i++) {
			// TODO: initalize xCoords and yCoords
		}
}
/*
moves the drive wheel on the horizontal axis
*/
void moveHorizontally(int col) {
	float dist = (xCoords[col]/(2*PI*WHEEL_DIAMETER))*360;
	motor[HORIZ_AXIS_MOTOR] = DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[HORIZ_AXIS_MOTOR] < dist) {}
	motor[HORIZ_AXIS_MOTOR] = 0;
}

/*
unwinds the string for the pulley system. unwinds the distance by spliting it up into wheel diameters.
*/
void moveVertically(int row) {
	//select distance and move that distance
	float dist = (xCoords[row]/(2*PI*WHEEL_DIAMETER))*360;
	motor[VERT_AXIS_MOTOR] = DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[VERT_AXIS_MOTOR] < dist) {}
	//stop the motor
	motor[VERT_AXIS_MOTOR] = 0;
}

/*
recalibrates the motors and reset position
*/
void returnToBase() {
	//move horizontally
	motor[HORIZ_AXIS_MOTOR] = -1*DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[HORIZ_AXIS_MOTOR] > 0){}
	motor[HORIZ_AXIS_MOTOR] = 0;
	wait1Msec(2000);
	//move vertically
	motor[VERT_AXIS_MOTOR] = -1*DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[VERT_AXIS_MOTOR] > 0){}
	motor[HORIZ_AXIS_MOTOR] = 0;
}

/*
spins the meshed wheel to dispense drink
*/
void spinWheel() {
	//spin the meshed wheel
	motor[MESHED_WHEEL_MOTOR] = 30;
	//wait for 1 second
	wait1Msec(1000);
}
