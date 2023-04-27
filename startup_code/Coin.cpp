#include "Coin.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
 
 // implement functions for managing coins; this may depend on your design.
Denomination Coin::getDenom(string amount) {
    Denomination d = FIVE_CENTS;

    if (amount.compare("1000") == 0){
        d = TEN_DOLLARS;
    }

    else if (amount.compare("500") == 0) {
        d = FIVE_DOLLARS;
    }

    else if (amount.compare("200") == 0) {
        d = TWO_DOLLARS;
    }

    else if (amount.compare("100") == 0) {
        d = ONE_DOLLAR;
    }

    else if (amount.compare("50") == 0) {
        d = FIFTY_CENTS;
    }

    else if (amount.compare("20") == 0) {
        d = TWENTY_CENTS;
    }

    else if (amount.compare("10") == 0) {
        d = TEN_CENTS;
    }

    else if (amount.compare("5") == 0) {
        d = FIVE_CENTS;
    }

    return d;
}
