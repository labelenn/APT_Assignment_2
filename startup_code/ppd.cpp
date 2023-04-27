#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "Coin.h"
#include <cstring>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
void mainMenuOutput();
void splitString(string s, vector<string>& tokens, string delimeter);
void loadCoinData(string coinDataFile, Coin *coins);


int main(int argc, char **argv)
{
    /* validate command line arguments */
    try {
        bool validNumArgs = (3 == argc);

        if (validNumArgs == false) {
            throw (validNumArgs);
        }
    }

    catch (bool valid) {
        cout << "Error: invalid arguments passed in." << endl;
        cout << "Correct arguments are:" << endl;
        cout << "       ./ppd <stockfile> <coinfile>" << endl;
        cout << "Where <stockfile> and <coinfile> are two valid files in the expected format." << endl;
        return EXIT_FAILURE;
    }

    // string stockFile = argv[1];
    // TODO: Read in stock file contents for the items and store it into a Linked List

    // Read in data file contents and store it into array
    string dataFile = argv[2];

    Coin x[8];
    Coin *coin = x;
    loadCoinData(dataFile, coin);

    // MAIN MENU
    string menuChoice;
    // display main menu options
    mainMenuOutput();
    cin >> menuChoice;
    if (menuChoice == "1") {
        //display items
    }
    else if (menuChoice == "2") {
        //purchase items
    }
    else if (menuChoice == "3") {
        //save and exit
    }
    else if (menuChoice == "4") {
        //Add item
    }
    else if (menuChoice == "5") {
        //remove item
    }
    else if (menuChoice == "6") {
        //display coins
    }
    else if (menuChoice == "7") {
        //reset stock
    }
    else if (menuChoice == "8") {
        //abort program
    }
    else {
        cout << "Invalid input" << endl;
    }
    
    return EXIT_SUCCESS;
}

void mainMenuOutput() {
    cout << "Main Menu:" << endl;
    cout << "   1.Display Items" << endl;
    cout << "   2.Purchase Items" << endl;
    cout << "   3.Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "   4.Add Item" << endl;
    cout << "   5.Remove Item" << endl;
    cout << "   6.Display Coins" << endl;
    cout << "   7.Reset Stock" << endl;
    cout << "   8.Reset Coins" << endl;
    cout << "   9.Abort Program" << endl;
    cout << "Select your option (1-9):" << endl;
}

void splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

void loadCoinData(string coinDataFile, Coin *coins)
{   
    string fileLine;
    int currIndex = 0;
    std::ifstream dFile;
    dFile.open(coinDataFile);
    
    if (dFile.is_open()) {
        while (dFile.peek() != EOF) {
            std::getline(dFile, fileLine);

            vector<string> coinData;
            splitString(fileLine, coinData, DELIM);

            Coin c;

            Denomination d = c.getDenom(coinData[0]);
            c.denom = d;
            c.count = stoi(coinData[1]);

            *(coins + currIndex) = c;
            currIndex += 1;
        }
        dFile.close();
    }

    else {
        cout << "Cannot open file." << endl;
    }
}
