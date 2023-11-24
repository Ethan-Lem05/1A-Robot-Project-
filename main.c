/*
This file is responsible for running all the code as well as storing any constants that all files will need access to.
*/
#include "PortBindings.c";
#include "MovementHandler.c";
#include "UIHandler.c";
#include "AccountHandler.c";
#include "InventoryHandler.c";
/**
holds all the different possible robot states
*/

enum RobotState
{
	IDLE_STATE,
	SELECTION_STATE,
	PAYMENT_STATE,
	DELIVERY_STATE
};
const float DRINK_COST = 25;
/**
runs if robot is in idle state

@returns returns the robots next state.
*/
RobotState idleState() {
	eraseDisplay();
	clearTimer(T1);
	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}
	return SELECTION_STATE;
}
/**
runs if robot is in selection state
*/
RobotState selectionState (int & row, int & col) {
	eraseDisplay();
	//prompt user for input
	getDrinkSelection(row, col);
	//select the drink choice by reference
	return PAYMENT_STATE;
}
/*
runs if robot is in payment state

@returns returns the robots next state.
*/
RobotState paymentState () {
	eraseDisplay();
	//let user scan
	int userID = scanID();
	//validate that user can pay for drink -> if not return the user to the selection drink so they can make a cheaper purchase
	//make the payment
	if (buyProduct(userID, DRINK_COST)) {
		eraseDisplay();
		displayBigTextLine(2, "Purchase successful");
		wait1Msec(1000);
		return DELIVERY_STATE;
	} else {
		eraseDisplay();
		displayBigTextLine(2, "Purchase unsuccessful");
		wait1Msec(1000);
		eraseDisplay();
		return SELECTION_STATE;
	}
}
/*
runs if robot is in delivery state.

@returns returns the robots next state.
*/
RobotState deliveryState (int row, int col) {
	eraseDisplay();
	displayBigTextLine(2, "Please wait...");

	if(row == 0) {
		if(col == 0) {getDrink(3); } else { getDrink(4); }
	} else {
		if(col == 0) {getDrink(1); } else { getDrink(2); }
}
	displayBigTextLine(2, "Thank you!");
	wait1Msec(2000);
	return IDLE_STATE;
}
/**
configures all the senors and motors to their proper state
*/
void configuration() {
	  // Configure Color Sensor on Port 1
    SensorType[COLOR_SENSOR] = sensorEV3_Color;

    // Configure touch Sensor on Port 2
    SensorType[TOUCH_SENSOR_VERT] = sensorEV3_Touch;

	  // Configure Motor A
    nMotorEncoder[HORIZ_AXIS_MOTOR] = 0; // Clear encoder target
    nMotorPIDSpeedCtrl[HORIZ_AXIS_MOTOR] = mtrSpeedReg; // Set speed control mode
    nMotorEncoder[HORIZ_AXIS_MOTOR] = 0; // Reset motor encoder
    motor[HORIZ_AXIS_MOTOR] = 0; // Stop motor

    // Configure Motor B
    nMotorEncoder[VERT_AXIS_MOTOR] = 0;
    nMotorPIDSpeedCtrl[VERT_AXIS_MOTOR] = mtrSpeedReg;
    nMotorEncoder[VERT_AXIS_MOTOR] = 0;
    motor[VERT_AXIS_MOTOR] = 0;

    // Configure Motor C
    nMotorEncoder[MESHED_WHEEL_MOTOR] = 0;
    nMotorPIDSpeedCtrl[MESHED_WHEEL_MOTOR] = mtrSpeedReg;
    nMotorEncoder[MESHED_WHEEL_MOTOR] = 0;
    motor[MESHED_WHEEL_MOTOR] = 0;
}
/*
	main task
*/
task main()
{

	configuration();
	downloadData();
	RobotState state = IDLE_STATE;
	int row = 1; // number that ranges from 0-3 indicating which module the drink belongs to
	int col = 1;
	while(true) {
		switch(state){
		case IDLE_STATE:
			state = idleState();
			break;
		case SELECTION_STATE:
			state = selectionState(row,col);
			break;
		case PAYMENT_STATE:
			state = paymentState();
			break;
		case DELIVERY_STATE:
			state = deliveryState(row, col);
			break;
		}
		uploadData();
	}

}
