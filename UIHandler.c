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
	displayBigTextLine(6, "Input your drink of choice?");
	wait1Msec(5000);
	// display select screen
	char rowVal = 'a';
	eraseDisplay();
	displayBigTextLine(2, "row: %d", row);
	displayBigTextLine(6, "col: %d", col);
	//detect buttons pressed on the EV3
	while(!getButtonPress(buttonEnter)) {
		if(getButtonPress(buttonUp) || getButtonPress(buttonDown)) {
			row == 1 ? row = 2: row = 1;
			displayBigTextLine(2, "row: %d", row);
		}
		if(getButtonPress(buttonLeft) || getButtonPress(buttonRight)) {
			col == 1 ? col = 0: col = 1;
			displayBigTextLine(6, "col: %d", col);
		}
	}
	// once drink is selected return the corresponding module
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
	bool flag = true;
	int ID = 0;
	while(flag)
	{
		switch (SensorValue[COLOR_SENSOR])
		{
		case 1:
			ID = 1;
			flag = false;
			displayBigTextLine(2, "Welcome back Edison H.!");
			break;
		case 2:
			ID = 2;
			flag = false;
			displayBigTextLine(2, "Welcome back Ethan L.!");
			break;
		case 3:
			ID = 3;
			flag = false;
			displayBigTextLine(2, "Welcome back Ethan Y.!");
			break;
		case 4:
			ID = 4;
			flag = false;
			displayBigTextLine(2, "Welcome back Luke Q.!");
			break;
		default:
			displayBigTextLine(2, "Please scan your ID");
			break;
		}
	}

	//Dunno, maybe the main code or the rest of the UI Handler would benefit,
	//like, the accounting system might need to know how much money is left in the account
	return ID;
}
