/*
This account will handle the accounts
*/

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
	if(bEv3FileExists("./TextFiles/Account.txt")){
		string pData = "hello world";
		fileWriteData(500, pData, 20);
	}
}

void buyProduct(string studentID, float cost) {
	int index = searchByID(studentID);
	balances[index] -= cost;

}
