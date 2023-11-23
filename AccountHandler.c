/*
This file will handle the accounts
*/
//set up parallel arrays
#include "PortBindings.c"
#include "PC_FileIO.c"

/**
structure that groups all the information related to accounts together
*/
struct Account {
	string name;
	int ID;
	float balance;
};
const int NUM_ACC = 4;
Account accounts[NUM_ACC];

/*
downloads data into an array
*/
void downloadData() {
	//declare input variables
	TFileHandle fin;
	int id = 0;
	float balance = 0.0;
	string name;
	//open the file and read int it
	if(openReadPC(fin, "accounts.txt")) {
		for(int i = 0; i < NUM_ACC; i++) {
			if(i == 0) {
				readTextPC(fin,name);
				} else if (i == 1) {
				readIntPC(fin,id);
				} else {
				readFloatPC(fin,balance);
			}
			Account account;
			account.ID = id;
			account.name = name;
			account.balance = balance;
			accounts[i] = account;
		}
	}
}
/**
uploads the data in the updated array into the textfile for next use.
*/
void uploadData() {
	TFileHandle fout;
	if(openWritePC(fout,"account.txt")){
		for(int i = 0; i < NUM_ACC; i++) {
			string output = "%d     %s     %f";
			sprintf(output,output,accounts[i].ID,accounts[i].name,accounts[i].balance);

			writeTextPC(fout, output);
		}
	}
}
/**
takes in the studentID and cost and returns whether or not the purchase was successful.
*/
bool buyProduct(int userID, float cost) {
	for(int i = 0; i < NUM_ACC; i++) {
		if(accounts[i].ID == userID && cost <= accounts[i].balance) {
			accounts[i].balance -= cost;
			return true;
		}
	}
	return false;
}
