/*
This file is responsible for running all the code as well as storing any constants that all files will need access to.
*/
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
}

/*
runs if robot is in idle state
*/
RobotState idleState(RobotState &currentState) {
	return IDLE_STATE;
}
/*
runs if robot is in selection state
*/
RobotState selectionState (RobotState &currentState) {
	return IDLE_STATE;
}
/*
runs if robot is in payment state
*/
RobotState paymentState (RobotState &currentState) {
	return IDLE_STATE;
}
/*
runs if robot is in delivery state
*/
RobotState deliveryState (RobotState &currentState) {
	return IDLE_STATE;
}

/*
	main task;
*/
task main()
{
	uploadData();
	while(true) {
		RobotState state = IDLE_STATE;
		switch(state){
		case IDLE_STATE:
			idleState(state);
			break;
		case SELECTION_STATE:
			selectionState(state);
			break;
		case PAYMENT_STATE:
			paymentState(state);
			break;
		case DELIVERY_STATE:
			deliveryState(state);
			break;
		}
	}
}
