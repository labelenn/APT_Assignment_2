#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "Coin.h"
#include "CashRegister.h"
#include <iomanip>
#include <sstream>
#include <cctype>
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
string displayMainMenu();

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


    // Read in data file contents
    LinkedList* stockList = new LinkedList(argv[1]);

    CashRegister* cr = new CashRegister(); 
    string dataFile = argv[2];
    Coin x[8];
    Coin *coin = new Coin;
    coin = x;
    cr->loadCoinData(dataFile, coin);

    

    // MAIN MENU
    bool menu = true;
    while (menu)
    {
        // display main menu options
        string menuChoice = displayMainMenu();

        if (cin.good() && !cin.eof())
        {

            if (menuChoice == "1") 
            {
                //display items
                stockList->displayItems();
            }

            else if (menuChoice == "2") 
            {
                //purchase items

                // Only works if ID is correct
                // Has an inbuilt checker if stock is 0, so stock won't be negative
                string selectedID = "I0003";
                stockList->updateItemCount(selectedID);
            }

            else if (menuChoice == "3") 
            {
                //save and exit
            }

            else if (menuChoice == "4") 
            {   
    
                static int nextId = stockList->lastItemID;
                std::stringstream ss;
                ss << "I" << std::setfill('0') << std::setw(4) << ++nextId;
                string id = ss.str();
                cout << "The id of the new stock will be: " << id << endl;
                
                cout << "Enter the item name: ";
                string newItemName;
                getline(cin, newItemName);
                getline(cin, newItemName);
                // Convert the first letter of each word to uppercase
                bool makeUppercase = true;
                for (int i = 0; i < newItemName.length(); i++) {
                    // check if index is a letter
                    if (makeUppercase && isalpha(newItemName[i])) {
                        newItemName[i] = toupper(newItemName[i]);
                        makeUppercase = false;
                    }
                    else if (newItemName[i] == ' ') {
                        makeUppercase = true;
                    }
                    else if (makeUppercase == false && isalpha(newItemName[i])){
                        newItemName[i] = tolower(newItemName[i]);
                    }
                }
                
                cout << "Enter the item description: ";
                string newItemDescription;
                getline(cin, newItemDescription);
                
                cout << "Enter the price for the item: ";
                string newItemPrice;
                cin >> newItemPrice;
                stockList->addItem(id, newItemName, newItemDescription, newItemPrice);
            }

            else if (menuChoice == "5") 
            {
                //remove item
                cout << "Enter the id of the item you want to remove: " << endl;
                string removeID;
                cin >> removeID;
                stockList->removeItem(removeID);

            }

            else if (menuChoice == "6") 
            {
                // Display coins
                cr->displayCoins(coin);
            }

            else if (menuChoice == "7") 
            {
                //reset stock
            }

            else if (menuChoice == "8") 
            {
                // Reset Coins
                cr->resetCoins(coin);
            }

            else if (menuChoice == "9") 
            {
                //abort program
                menu = false;
            }

            else 
            {
                cout << "Invalid input" << endl;
            }
        }
    }    
    
    
    return EXIT_SUCCESS;
}

string displayMainMenu() {
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
    string menuChoice;
    cin >> menuChoice;
    return menuChoice;
}

