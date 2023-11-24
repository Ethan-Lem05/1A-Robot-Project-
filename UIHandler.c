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
void getDrinkSelection(int & row, int & col) {
	//reset values
	// display choose your drink for 5 seconds
	displayTextLine(6, "Input your drink of choice?");
	wait1Msec(5000);
	// display select screen
	eraseDisplay();
	displayBigTextLine(2, "row: %d", row);
	displayBigTextLine(6, "col: %d", col);
	//detect buttons pressed on the EV3
	while(!getButtonPress(buttonEnter)) {
		if(getButtonPress(buttonUp) || getButtonPress(buttonDown)) {
			(row == 1) ? row = 2: row = 1;
			displayBigTextLine(2, "row: %d", row);
		}
		if(getButtonPress(buttonLeft) || getButtonPress(buttonRight)) {
			(col == 1) ? col = 2: col = 1;
			displayBigTextLine(6, "col: %d", col);
		}
	}
	row -= 1;
	col -= 1;
	// once drink is selected return the corresponding module
	//clear screen
}

/*
may not be impleemnted
*/
void detectDrinkRemoved() {

}

/**
gets the user ID using the color sensor

Keep sensor on until a color has been read into the color sensor on the ev3.
ID:
1. Black = Edison
2. Blue = Ethan Lem
3. Green = Ethan Yung
4. Yellow = Luke
0. Other colors = Unknown

@return the ID related to the color the color sensor identifies

*/
int scanID() {
	while(true)
	{
		switch (SensorValue[COLOR_SENSOR])
		{
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		case 5:
			return 5;
		default:
			displayTextLine(2, "Please scan your ID");
			break;
		}
	}
}
