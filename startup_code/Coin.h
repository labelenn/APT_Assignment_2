#ifndef COIN_H
#define COIN_H
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    Coin();
    ~Coin();
    // the denomination type
    enum Denomination denom;
    
    // the count of how many of these are in the cash register
    unsigned count;

    // Function to get the coin's denomination type
    Denomination getDenom(string amount);

};

#endif // COIN_H
