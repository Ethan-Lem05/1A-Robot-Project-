/*
This File will be used for UI input from the EV3 brick
*/
#include "PortBindings.c"
#include "AccountHandler.c"
#include "PC_FileIO.c"

/**
Allows the user to select a drink module to buy from

@returns the relevant module
*/
int getDrinkSelection() {
	// display choose your drink for 5 seconds
	displayBigTextLine(6, "Input your drink of choice?");
	wait1Msec(5000);
	// display select screen
	int row = 0;
	int col = 0;
	char rowVal = 'a';
	eraseDisplay();
	displayBigTextLine(2, "row: %d", row);
	displayBigTextLine(6, "col: %d", col);
	//detect buttons pressed on the EV3
	while(!getButtonPress(buttonEnter)) {
		if(getButtonPress(buttonUp) || getButtonPress(buttonDown)) {
			row == 1 ? row = 0: row = 1;
			displayBigTextLine(2, "row: %d", row);
		}
		if(getButtonPress(buttonLeft) || getButtonPress(buttonRight)) {
			col == 1 ? col = 0: col = 1;
			displayBigTextLine(6, "col: %d", col);
		}
	}
	// once drink is selected return the corresponding module
	return row + col; // equation for selecting module
}

/*
may not be impleemnted
*/
void detectDrinkRemoved() {

}

/**
 gets the user ID using the color sensor

 @return the ID related to the color the color sensor identifies
*/
int scanID() {
	return SensorValue[COLOR_SENSOR];
}
