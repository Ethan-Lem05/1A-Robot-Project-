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

/**
runs if robot is in idle state

@returns returns the robots next state.
*/
RobotState idleState() {
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
	//prompt user for input
	drinkChoice = getDrinkSelection(row, col);
	//select the drink choice by reference
	return PAYMENT_STATE;
}
/*
runs if robot is in payment state

@returns returns the robots next state.
*/
RobotState paymentState (int row, int col) {
	//let user scan
	int userID = scanID();
	//buyProduct(userID, choice.cost);
	//validate that user can pay for drink -> if not return the user to the selection drink so they can make a cheaper purchase

	//make the payment
	return DELIVERY_STATE;
}
/*
runs if robot is in delivery state.

@returns returns the robots next state.
*/
RobotState deliveryState () {
	mov
	return IDLE_STATE;
}
/**
configures all the senors and motors to their proper state
*/
void configuration() {
	  // Configure Color Sensor on Port 1
    SensorType[COLOR_SENSOR] = sensorEV3_Color;

    // Configure Ultrasonic Sensor on Port 2
    SensorType[US_SENSOR] = sensorEV3_Ultrasonic;

    // Configure Touch Sensor on Port 3
    SensorType[TOUCH_SENSOR] = sensorEV3_Touch;

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
void initialize() {

}
/*
	main task
*/
task main()
{
	configuration();
	RobotState state = IDLE_STATE;
	int row = 0; // number that ranges from 0-3 indicating which module the drink belongs to
	int col = 0;
	while(true) {
		switch(state){
		case IDLE_STATE:
			state = idleState();
			break;
		case SELECTION_STATE:
			state = selectionState(row,col);
			break;
		case PAYMENT_STATE:
			state = paymentState(row, col);
			break;
		case DELIVERY_STATE:
			state = deliveryState();
			break;
		}
	}
}
