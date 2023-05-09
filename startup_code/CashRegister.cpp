#include "CashRegister.h"
#include "helper.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <ios>
#include <iomanip>
#include <algorithm>
#include <map>

using std::cin;
using std::count;
using std::cout;
using std::endl;
using std::map;
using std::setw;
using std::sort;
using std::string;
using std::vector;

void CashRegister::loadCoinData(string coinDataFile, Coin *coins)
{
    string fileLine;
    int currIndex = 0;
    std::ifstream dFile;
    dFile.open(coinDataFile);

    if (dFile.is_open())
    {
        while (dFile.peek() != EOF)
        {
            std::getline(dFile, fileLine);

            vector<string> coinData;
            Helper::splitString(fileLine, coinData, DELIM);

            Coin *c = new Coin;

            Denomination d = c->getDenom(coinData[0]);
            c->denom = d;
            c->count = stoi(coinData[1]);

            *(coins + currIndex) = *c;
            denoms.push_back(stoi(coinData[0]));
            currIndex += 1;
        }
        dFile.close();
        denomsCount = currIndex;
    }

    else
    {
        cout << "Cannot open file." << endl;
    }
}

CashRegister::~CashRegister() {
    cout << "Cash Register destroyed" << endl;
}

void CashRegister::displayCoins(Coin *coins)
{
    cout << "Coins Summary" << endl;
    cout << "-------------" << endl;
    cout << "Denomination    |    Count" << endl;
    cout << "---------------------------" << endl;

    for (int i = 7; i >= 0; --i)
    {
        if ((coins + i)->denom == 7)
        {
            cout << "10 Dollars" << setw(7) << "|";
        }

        else if ((coins + i)->denom == 6)
        {
            cout << "5 Dollars" << setw(8) << "|";
        }

        else if ((coins + i)->denom == 5)
        {
            cout << "2 Dollars" << setw(8) << "|";
        }

        else if ((coins + i)->denom == 4)
        {
            cout << "1 Dollar" << setw(9) << "|";
        }

        else if ((coins + i)->denom == 3)
        {
            cout << "50 Cents" << setw(9) << "|";
        }

        else if ((coins + i)->denom == 2)
        {
            cout << "20 Cents" << setw(9) << "|";
        }

        else if ((coins + i)->denom == 1)
        {
            cout << "10 Cents" << setw(9) << "|";
        }

        else if ((coins + i)->denom == 0)
        {
            cout << "5 Cents" << setw(10) << "|";
        }
        cout << setw(10) << (coins + i)->count << endl;
    }
}

void CashRegister::resetCoins(Coin *coins)
{
    for (int i = 0; i < 8; ++i)
    {
        (coins + i)->count = DEFAULT_COIN_COUNT;
    }

    cout << "All coins has been reset to the default level of " << DEFAULT_COIN_COUNT << endl;
}

vector<string> CashRegister::getChange(int change)
{
    sort(denoms.begin(), denoms.end());

    // Initialize result
    vector<string> coins;

    // Traverse through all denomination
    for (int i = denomsCount - 1; i >= 0; i--)
    {

        // Find denominations
        while (change >= denoms[i])
        {
            change -= denoms[i];
            coins.push_back(std::to_string(denoms[i]));
        }
    }

    return coins;
}

bool CashRegister::checkCoinAvailability(vector<string> change, Coin *coins)
{
    bool coinsAvailable = true;
    map<string, int> coinCount;

    int numChange = change.size();
    for (int i = 0; i < numChange; i++)
    {
        coinCount[change[i]] = count(change.begin(), change.end(), change[i]);
    }

    map<string, int>::iterator it = coinCount.begin();
    while (it != coinCount.end())
    {
        Coin c;
        c.denom = c.getDenom(it->first);

        for (int i = 0; i < denomsCount; i++)
        {
            if (c.denom == (coins + i)->denom)
            {
                int count = (coins + i)->count;
                if (it->second > count)
                {
                    coinsAvailable = false;
                }
            }
        }
        ++it;
    }

    return coinsAvailable;
}

void CashRegister::updateCoinCount(vector<string> coins, Coin *registerCoins, int mode)
{

    int numCoins = coins.size();
    for (int i = 0; i < numCoins; i++)
    {
        for (int j = 0; j < denomsCount; j++)
        {
            Coin c;
            c.denom = c.getDenom(coins[i]);

            if (c.denom == (registerCoins + j)->denom)
            {
                if (mode == 1)
                {
                    (registerCoins + j)->count += 1;
                }

                else
                {
                    (registerCoins + j)->count -= 1;
                }
            }
        }
    }
}

bool CashRegister::validDenomination(string amount)
{
    bool validDenom = false;
    for (int i = 0; i < denomsCount; i++)
    {
        if (stoi(amount) == denoms[i])
        {
            validDenom = true;
        }
    }

    return validDenom;
}

string CashRegister::getValueInDollars(string userAmount)
{
    int amount = stoi(userAmount);
    string value;

    if (amount >= 100)
    {
        value = "$" + std::to_string(amount / 100);
    }

    else
    {
        value = std::to_string(amount) + "c";
    }

    return value;
}

string CashRegister::exportData(Coin *coins)
{

    string exportData;

    for (int i = 0; i <= 7; ++i)
    {
        string count = std::to_string((coins + i)->count);

        if ((coins + i)->denom == 0)
        {
            exportData += "5," + count + "\n";
        }
        else if ((coins + i)->denom == 1)
        {
            exportData += "10," + count + "\n";
        }
        else if ((coins + i)->denom == 2)
        {
            exportData += "20," + count + "\n";
        }
        else if ((coins + i)->denom == 3)
        {
            exportData += "50," + count + "\n";
        }
        else if ((coins + i)->denom == 4)
        {
            exportData += "100," + count + "\n";
        }
        else if ((coins + i)->denom == 5)
        {
            exportData += "200," + count + "\n";
        }
        else if ((coins + i)->denom == 6)
        {
            exportData += "500," + count + "\n";
        }
        else if ((coins + i)->denom == 7)
        {
            exportData += "1000," + count + "\n";
        }
    }

    return exportData;
}