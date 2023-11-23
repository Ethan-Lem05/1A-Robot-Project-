/*
This file deals with the movement of the 2 axis machine
*/
#include "PortBindings.c"
const int NUM_MODULES = 4;
const float WHEEL_DIAMETER = 3.25;
const int DRIVING_WHEEL_SPEED = 30;

const int X_BASE = 0;
const int Y_BASE = 0;
int xCoords[NUM_MODULES];
int  yCoords[NUM_MODULES];



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
	motor[HORIZ_AXIS_MOTOR] = DRIVING_WHEEL_SPEED;
	while(abs(nMotorEncoder[HORIZ_AXIS_MOTOR]) < abs(xCoords[col])) {}
	motor[HORIZ_AXIS_MOTOR] = 0;
}

/*
unwinds the string for the pulley system. unwinds the distance by spliting it up into wheel diameters.
*/
void moveVertically(int row) {
	//select distance and move that distance
	motor[VERT_AXIS_MOTOR] = DRIVING_WHEEL_SPEED;
	while(abs(nMotorEncoder[VERT_AXIS_MOTOR]) < abs(xCoords[row])) {}
	//stop the motor
	motor[VERT_AXIS_MOTOR] = 0;
}

/*
recalibrates the motors and reset position
*/
void recalibrate () {
	//recalibrate horizontally
	motor[HORIZ_AXIS_MOTOR] = -1*DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[HORIZ_AXIS_MOTOR] > 0){}
	motor[HORIZ_AXIS_MOTOR] = 0;
	wait1Msec(2000);
	//recalibrate vertically
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
void moveToDrink(int module) {
	int x = xCoords[module];
	int y = yCoords[module];
  // move vertical axis
	moveVertically(y);
  // move horizontal axis
	moveHorizontally(x);
	//grab drink
	spinWheel();
	//recalibrate
	recalibrate();
}
