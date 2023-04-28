#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

class Helper
{
private:
    Helper();

public:

    static void splitString(string s, vector<string>& tokens, string delimeter);

};
#endif