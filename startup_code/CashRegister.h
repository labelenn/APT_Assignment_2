#ifndef CASH_REGISTER_H
#define CASH_REGISTER_H
#include <iostream>
#include <vector>
#include <cstring>
#include "Coin.h"
#include "Node.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

class CashRegister
{
public:
    // load coin data file into an array
    void loadCoinData(string coinDataFile, Coin *coins);

    // display coin data
    void displayCoins(Coin *coins);

    // reset coin data
    void resetCoins(Coin *coins);

    /**returns a vector of strings containing the change (in cents)
     * to be given to the user after a purchase
    **/    
    vector<string> getChange(int change);

    /** 
     * given a list of coins, map each element to its count in the list and check if it is available in the cash register
     * i.e. the number of coins in the register is enough for the count of each denomination in the list.
    **/ 
    bool checkCoinAvailability(vector<string> change, Coin *coins);

    // Update number of coins after a purchase
    void updateCoinCount(vector<string> coins, Coin *registerCoins, int mode);

    // check if the given amount is a valid denomination
    bool validDenomination(string amount);

    // Get value of cents in dollars
    string getValueInDollars(string);

    // vector of ints of the denominations in the cash register
    vector<int> denoms;

    // Number of denominations in the cash register
    int denomsCount;

};

#endif // CASH_REGISTER_H