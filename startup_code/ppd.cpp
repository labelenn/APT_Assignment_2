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
void purchaseItem(LinkedList *stock, CashRegister *cregister, Coin* coins);

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
    while (menu && cin.good() && !cin.eof())
    {
        // display main menu options
        string menuChoice = displayMainMenu();

        if (menuChoice.size() == 0) {
            menu = false;
        }

        else {

            if (menuChoice == "1") 
            {
                //display items
                stockList->displayItems();
            }

            else if (menuChoice == "2") 
            {
                // Purchase Item
                purchaseItem(stockList, cr, coin);
                
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
                // Convert the first letter of each word to uppercase
                bool makeUppercase = true;
                int itemNameLength = newItemName.length();
                for (int i = 0; i < itemNameLength; i++) {
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
                getline(cin, newItemPrice);
                stockList->addItem(id, newItemName, newItemDescription, newItemPrice);
            }

            else if (menuChoice == "5") 
            {
                //remove item
                cout << "Enter the id of the item you want to remove: " << endl;
                string removeID;
                getline(cin, removeID);
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
    std::getline(cin, menuChoice);
    return menuChoice;
}

void purchaseItem(LinkedList *stock, CashRegister *cregister , Coin* coinsRegister) {
    
    // FIND ITEM IN THE LIST
    string itemID;
    bool cancelPurchase = false;

    bool itemFound = false;
    while (itemFound != true)
    {   
        bool inputExiter = false;
        while (cin.good() && !cin.eof() && inputExiter != true)
        {
            cout << "Purchase Item" << endl;
            cout << "-------------" << endl;
            cout << "Please enter the id of the item you wish to purchase: "; 
            getline(cin, itemID);

            if (itemID.size() == 0 || cin.eof()) {
                cout << "The task Purchase Item failed to run successfully." << endl;
                cancelPurchase = true;
                itemFound = true;
                inputExiter = true;
            }
            
            else {
                // Check if item is in stock
                bool itemInInventory = stock->findItem(itemID);
                if (itemInInventory == false) {
                    cout << "Error: the id you entered was not valid. Please try again." << endl;
                }

                else {
                    itemFound = true;
                    inputExiter = true;
                }
            }
        }
    }


    // ITEM FOUND, PROCEED TO PURCHASE PROCESS
    if (cancelPurchase != true) {
        // Store item into a Stock object
        Stock item = stock->getItem(itemID);

        // PURCHASE PROCESS
        bool purchaseDone = false;
        while (purchaseDone != true)
        {   

            // CHECK STOCK AVAILABILITY
            bool available = stock->itemAvailability(itemID);
            if (available == true) {
                vector<string> coins;
                vector<string> changeCoins;
                cout << "You have selected \"" << item.name << " - " << item.description << "\". ";
                cout << "This will cost you $ " << item.price->dollars << "." << item.price->cents << "." << endl;

                // PROMPT FOR PAYMENT UNTIL THE USER QUITS OR THE USER PROVIDES THE REQUIRED AMOUNT
                cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
                cout << "Press enter or ctrl-d on a new line to cancel this purhcase:" << endl;
                bool cancel = false;

                int requiredAmount = (item.price->dollars * 100) + item.price->cents;
                int currAmount = 0;
                while (cin.good() && !cin.eof() && cancel != true && currAmount < requiredAmount) {
                    int remainingAmount = requiredAmount - currAmount;
                    if  (remainingAmount >= 100) {
                        int dollar = (remainingAmount / 100);
                        int cents = remainingAmount - ((remainingAmount / 100) * 100);
                        cout << "You still need to give us $" << dollar << "." << cents << ": ";
                    }

                    else {
                        cout << "You still need to give us $0." << remainingAmount << ": ";
                    }
                    
                    string userAmount;
                    getline(cin, userAmount);

                    if (userAmount.size() == 0 || cin.eof()) {
                        int numCoins = coins.size();
                        cout << "Change of mind - here is your change: ";
                        for (int i = 0; i < numCoins; i++) {
                            cout << cregister->getValueInDollars(coins[i]) << " ";
                        }
        
                        cout << endl << endl;
                        cancel = true;
                        purchaseDone = true;
                    }

                    
                    else {
                        // Check if userAmount is a valid denomination
                        bool valid = cregister->validDenomination(userAmount);

                        if (valid == true) {
                            coins.push_back(userAmount);
                            currAmount += stoi(userAmount);
                        }

                        else {
                            if (stoi(userAmount) >= 100) {
                                int amount = stoi(userAmount);
                                int dollar = (amount/100);
                                int cents = amount - (dollar * 100);
                                cout << "Error: $" << dollar << "." << cents << " is not a valid denomination of money. Please try again." << endl;
                            }

                            else {
                                cout << "Error: $0." << userAmount << " is not a valid denomination of money. Please try again." << endl;
                            }
                        }
                    }
                }

                // PURCHASE COMPLETED - THE USER PROVIDED REQUIRED AMOUNT
                if (currAmount >= requiredAmount) {
                    int change = currAmount - requiredAmount;
                    
                    // Get list of coins for change
                    changeCoins = cregister->getChange(change);
                    int numCoins = changeCoins.size();

                    // Check if there are enough coins in the register to provide the change. If not, display a message, purchase will be cancelled.
                    bool coinsEnough = cregister->checkCoinAvailability(changeCoins, coinsRegister);

                    if (coinsEnough == true) {
                        if  (change >= 100) {
                            int dollar = (change / 100);
                            int cents = change - ((change / 100) * 100);
                            cout << "Here is your " << item.name << " and your change of $" << dollar << "." << cents << ": ";
                        }

                        else {
                            cout << "Here is your " << item.name << " and your change of $0." << change << ": ";

                        }

                        for (int i = 0; i < numCoins; i++) {
                            cout << cregister->getValueInDollars(changeCoins[i]) << " ";
                        }
                    
                        cout << endl << endl;

                        // ADJUST STOCK COUNT AND COIN COUNT
                        cregister->updateCoinCount(coins, coinsRegister, 1);
                        cregister->updateCoinCount(changeCoins, coinsRegister, 0);
                        stock->updateItemCount(itemID);
                    }

                    else {
                        cout << "There is not enough coins in the system to supply the change for the given amount." << endl << endl;
                    }
                    purchaseDone = true;
                }

                
            }

            else {
                cout << "Item unavaiable." << endl;
                purchaseDone = true;
            }  
        }
    }
}

