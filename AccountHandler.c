#include "PortBindings.c"
#include "PC_FileIO.c"

// Define structure to store account information
struct Account {
    string name;
    int ID;
    float balance;
};

const string FILE_NAME = "userAccounts.txt";
const int NUM_ACC = 4;
Account accounts[NUM_ACC];

void downloadData() {
    TFileHandle fin;
    int id = 0;
    float balance = 0.0;
    string name;

    if(openReadPC(fin, "userAccounts.txt")) {

    		eraseDisplay();
        displayTextLine(1, "File successfully loaded");
        wait1Msec(1000);


        for(int i = 0; i < NUM_ACC; i++) {

            readIntPC(fin, id);
            readTextPC(fin, name);
            readFloatPC(fin, balance);

            accounts[i].ID = id;
            accounts[i].name = name;
            accounts[i].balance = balance;
        }
    } else {
    		eraseDisplay();
        displayTextLine(1, "File not found!!!");
        wait1Msec(5000);
    }
    closeFilePC(fin);
}

void uploadData() {
    TFileHandle fout;
    eraseDisplay();
    bool openedFile = openWritePC(fout, FILE_NAME);
    displayTextLine(5, "%d", openedFile);
    wait1Msec(2000);
    if(openedFile) {
        for(int i = 0; i < NUM_ACC; i++) {
            string output;
            sprintf(output, "%d %s %.2f\n", accounts[i].ID, accounts[i].name, accounts[i].balance);
            writeTextPC(fout, output);
        }
    } else {
    	displayTextLine(5, "FAILED TO WRITE TO FILE");
    }
    closeFilePC(fout);
}

bool buyProduct(int userID, float cost) {
    eraseDisplay();
    for(int i = 0; i < NUM_ACC; i++) {
        if(accounts[i].ID == userID && cost <= accounts[i].balance) {
        	eraseDisplay();
        		displayTextLine(5, "%s has been billed $20!", accounts[i].name);
            accounts[i].balance -= cost;
            return true;
        }
    }
    return false;
}
