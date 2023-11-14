/*
This File will be used for UI input from the EV3 brick
*/
#include "PortBindings.c"

/*
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
	int
	// once drink is selected
}

/*
*/
void detectDrinkRemoved() {

}

/*
*/
void scanID() {

}
