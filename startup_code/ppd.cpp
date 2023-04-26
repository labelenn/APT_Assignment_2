#include <iostream>
#include "LinkedList.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
void mainMenuOutput();


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
    cout << "1.Display Items" << endl;
    cout << "2.Purchase Items" << endl;
    cout << " 3.Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "4.Add Item" << endl;
    cout << "5.Remove Item" << endl;
    cout << "6.Display Coins" << endl;
    cout << "7.Reset Stock" << endl;
    cout << "8.Reset Coins" << endl;
    cout << "9.Abort Program" << endl;
    cout << "Select your option (1-9):" << endl;
}
