/*
This file deals with the movement of the 2 axis machine
*/
#include "PortBindings.c"
const int NUM_MODULES = 2;
const int DRIVING_WHEEL_SPEED = 50;
const int MESHING_WHEEL_SPEED = DRIVING_WHEEL_SPEED - 40;

const int MESHING_DELTA_Y = 15;
int xCoords[NUM_MODULES];
int yCoords[NUM_MODULES];



/*
initializes the coordinates of the robot
*/
void initializeCoordinates()
{
	xCoords[0] = -200; // 1
	xCoords[1] = 200; // 2

	yCoords[0] = 1150; // 1
	yCoords[1] = 1500; // 2
}
/*
moves the drive wheel on the horizontal axis
*/
void moveHorizontally(int col) {
	motor[HORIZ_AXIS_MOTOR] = /*(xCoords[1]/abs(xCoords[1]))**/DRIVING_WHEEL_SPEED;
	while(abs(nMotorEncoder[HORIZ_AXIS_MOTOR]) < xCoords[col]) {}
	motor[HORIZ_AXIS_MOTOR] = 0;
	wait1Msec(500);
}

/*
unwinds the string for the pulley system. unwinds the distance by spliting it up into wheel diameters.
*/
void moveVertically(int destEnc) {
	//int sign = (nMotorEncoder(VERT_AXIS_MOTOR) - yCoords[1])/(abs(nMotorEncoder(VERT_AXIS_MOTOR) - yCoords[1]));
	//select distance and move that distance
	motor[VERT_AXIS_MOTOR] = DRIVING_WHEEL_SPEED;
	while(abs(nMotorEncoder[VERT_AXIS_MOTOR]) < destEnc) {}
	//stop the motor
	motor[VERT_AXIS_MOTOR] = 0;
	wait1Msec(500);
}

/*
recalibrates the motors and reset position
*/
void recalibrateX () {
	//recalibrate horizontally
	motor[HORIZ_AXIS_MOTOR] = -1*DRIVING_WHEEL_SPEED;
	wait1Msec(5000);
	motor[HORIZ_AXIS_MOTOR] = 0;
	wait1Msec(1000);
	motor[HORIZ_AXIS_MOTOR] = DRIVING_WHEEL_SPEED;
	while(nMotorEncoder[HORIZ_AXIS_MOTOR] < 175){}
	motor[HORIZ_AXIS_MOTOR] = 0;
	wait1Msec(1000);
}
void recalibrateY () {
	//recalibrate vertically
	motor[VERT_AXIS_MOTOR] = -1*DRIVING_WHEEL_SPEED;
	while(!SensorValue[TOUCH_SENSOR_VERT]){}
	motor[HORIZ_AXIS_MOTOR] = 0;
	wait1Msec(1000);
}
void spinWheel() {
	//spin the meshed wheel
	motor[MESHED_WHEEL_MOTOR] = 30;
	//wait for 1 second
	wait1Msec(1000);
}
void grabDrink() {
	int curEncVal = nMotorEncoder(VERT_AXIS_MOTOR);
	motor[VERT_AXIS_MOTOR] = MESHING_WHEEL_SPEED;
	while(abs(nMotorEncoder(VERT_AXIS_MOTOR)) < curEncVal + MESHING_DELTA_Y) {
	}
	motor[VERT_AXIS_MOTOR] = 0;
	wait1Msec(500);
	spinWheel();
	motor[VERT_AXIS_MOTOR] = -1*MESHING_WHEEL_SPEED;
	while(abs(nMotorEncoder(VERT_AXIS_MOTOR)) > curEncVal) {
	}
	motor[VERT_AXIS_MOTOR] = 0;
	wait1Msec(500);
}
/*
spins the meshed wheel to dispense drink
*/
void moveToDrink(int col, int row) {
	eraseDisplay();
	displayBigTextLine(5, "%d %d", col, row);
	wait1Msec(5000);
	moveHorizontally(col);
	/*
	int x = xCoords[row];
	int y = yCoords[col];
	moveVertically(y);
	moveHorizontally(x);
	grabDrink();
	recalibrateX();
	recalibrateY();
	*/
}

	/*


//--------------------------------------------------------------------------------------------------------------------
	int MAX_HEIGHTBEFOREMESH = 1500;
	int MOTORSPEED = 50;
	int MIDX = 175;

	nMotorEncoder(motorA)=0;
	nMotorEncoder(motorB)=0;
	nMotorEncoder(motorC)=0;

	//Move the carrier to the left end of the x-axis
	motor[motorA] = MOTORSPEED;
	while(nMotorEncoder(motorA) < (700))
	{}

	//Park the carrier at the end for a little bit
	motor[motorA] = 0;
	wait1Msec(1000);

	//Bring the carrier back to the right-most end of the x-axis
	motor[motorA] = -MOTORSPEED;
	while(nMotorEncoder(motorA) > -50)
	{}

	//Park the carrier at the start point for a little bit
	motor[motorA] = 0;
	wait1Msec(1000);

	//Drive the carrier to the center of the x-axis
	motor[motorA] = MOTORSPEED;
	while(nMotorEncoder(motorA) < MIDX)
	{}

	//With the carrier at the center, move the y-axis up the the max height, right underneath the height for wheel meshing
	motor[motorB] = MOTORSPEED + 30;
	motor[motorA] = 0;
	while(nMotorEncoder(motorB) < (MAX_HEIGHTBEFOREMESH))
	{}

	//At the top center, right under the meshing wheel, pause for 5 seconds
	wait1Msec(5000);

	//Bring the carrier to the right-most end of the x-axis
	motor[motorB] = 0;
	motor[motorA] = -MOTORSPEED;
	while(nMotorEncoder(motorA) > -300)
	{}

	//Now to mesh the carrier with the module, slightly raise the y-axis
	motor[motorB] = 10;
	motor[motorA] = 0;
	while(nMotorEncoder(motorB) < (MAX_HEIGHTBEFOREMESH + 15))
	{}

	//At module 4, now meshed
	wait1Msec(5000);

	//Spin the meshed wheel to get your new drink
	motor[motorC] = MOTORSPEED - 10;
	motor[motorA] = 0;
	motor[motorB] = 0;
	while(nMotorEncoder(motorC) < (10))
	{}

	//After the drink has entered the carrier, we pause for 5 seconds
	wait1Msec(5000);

	//Then unmesh the module from the carrier by lowering the y-axis a little bit
	motor[motorC] = 0;
	motor[motorA] = 0;
	motor[motorB] = -10;
	wait1Msec(1000);

	//Bring the carrier back to the middle of the x-axis
	nMotorEncoder(motorA) = 0;
	motor[motorC] = 0;
	motor[motorA] = MOTORSPEED - 25;
	motor[motorB] = 0;
	while(nMotorEncoder(motorA) < MIDX)
	{}

	//Now you can lower the y-axis down to the bottom
	motor[motorB] = -MOTORSPEED - 30;
	motor[motorA] = 0;
	while(nMotorEncoder(motorB) > 0)
	{}

	//Bring the carrier to the rightmost end
	motor[motorC] = 0;
	motor[motorA] = -MOTORSPEED;
	motor[motorB] = 0;
	while(nMotorEncoder(motorA) > -50)
	{}
//--------------------------------------------------------------------------------------------------------------------
}
*/
