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

};

#endif // CASH_REGISTER_H