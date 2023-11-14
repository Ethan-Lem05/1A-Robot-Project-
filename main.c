/*
This file is responsible for running all the code as well as storing any constants that all files will need access to.
*/
#include "PortBindings.c";
#include "MovementHandler.c";
#include "UIHandler.c";
#include "AccountHandler.c";
#include "InventoryHandler.c";

enum RobotState
{
	IDLE_STATE,
	SELECTION_STATE,
	PAYMENT_STATE,
	DELIVERY_STATE
};

/*
runs if robot is in idle state
*/
RobotState idleState() {
	clearTimer(T1);
	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}
	return SELECTION_STATE;
}
/*
runs if robot is in selection state
*/
RobotState selectionState () {
	return IDLE_STATE;
}
/*
runs if robot is in payment state
*/
RobotState paymentState () {
	return IDLE_STATE;
}
/*
runs if robot is in delivery state
*/
RobotState deliveryState () {
	return IDLE_STATE;
}

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
/*
	main task
*/
task main()
{
	configuration();
	getDrinkSelection();
	RobotState state = IDLE_STATE;
	while(true) {
		switch(state){
		case IDLE_STATE:
			state = idleState();
			break;
		case SELECTION_STATE:
			state = selectionState();
			break;
		case PAYMENT_STATE:
			state = paymentState();
			break;
		case DELIVERY_STATE:
			state = deliveryState();
			break;
		}
	}
}
