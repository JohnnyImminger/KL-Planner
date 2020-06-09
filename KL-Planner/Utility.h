//
// Created by stein on 08.06.2020.
//

#ifndef KL_PLANNER_UTILITY_H
#define KL_PLANNER_UTILITY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Utility {
public:
    static vector<string> splitString(string &s, char delimiter);
    static string removeChars(string &s, string &charsToRemove);
};



#endif //KL_PLANNER_UTILITY_H
