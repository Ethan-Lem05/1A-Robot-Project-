/*
This account will handle the accounts
*/
task main() {
	}

//set up parallel arrays
const int NUM_ACC = 4;
string names[NUM_ACC];
string studentIDs[NUM_ACC];
float balances[NUM_ACC];

int searchByID(string ID) {
	for(int i = 0; i < NUM_ACC; i++) {
		if(ID == studentIDs[i])
				return i;
	}
	return 0;
}
void downloadData(string &names, string &studentIDs, float &balances) {

}

void uploadData() {

}

void buyProduct(string studentID, float cost) {
	int index = searchByID(studentID);
	balances[index] -= cost;

}
