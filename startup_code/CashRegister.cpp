#include "CashRegister.h"
#include "helper.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>


using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

void CashRegister::loadCoinData(string coinDataFile, Coin *coins) {
    string fileLine;
    int currIndex = 0;
    std::ifstream dFile;
    dFile.open(coinDataFile);
    
    if (dFile.is_open()) {
        while (dFile.peek() != EOF) {
            std::getline(dFile, fileLine);

            vector<string> coinData;
            Helper::splitString(fileLine, coinData, DELIM);

            Coin *c = new Coin;

            Denomination d = c->getDenom(coinData[0]);
            c->denom = d;
            c->count = stoi(coinData[1]);

            *(coins + currIndex) = *c;
            currIndex += 1;
        }
        dFile.close();
    }

    else {
        cout << "Cannot open file." << endl;
    }
}

void CashRegister::displayCoins(Coin *coins)
{
    cout << "Coins Summary" << endl;
    cout << "-------------" << endl;
    cout << "Denomination    |    Count" << endl;
    cout << "---------------------------" << endl;

    for (int i = 7; i >= 0; --i){
        if ((coins + i)->denom == 7){
            cout << "10 Dollars      |";
        }

        else if ((coins + i)->denom == 6) {
            cout << "5 Dollars       |";
        }

        else if ((coins + i)->denom == 5) {
            cout << "2 Dollars       |";
        }

        else if ((coins + i)->denom == 4) {
            cout << "1 Dollar        |";
        }

        else if ((coins + i)->denom == 3) {
            cout << "50 Cents        |";
        }

        else if ((coins + i)->denom == 2) {
            cout << "20 Cents        |";
        }

        else if ((coins + i)->denom == 1) {
            cout << "10 Cents        |";
        }

        else if ((coins + i)->denom == 0) {
            cout << "5 Cents         |";
        }
        cout << "        " << (coins + i)->count << endl;
    }
}

void CashRegister::resetCoins(Coin *coins)
{
    for (int i = 0; i < 8; ++i) {
            (coins + i)->count = DEFAULT_COIN_COUNT;
    }

    cout << "All coins has been reset to the default level of " << DEFAULT_COIN_COUNT << endl;
}