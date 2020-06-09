//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_UTILITY_H
#define KL_PLANNER_UTILITY_H

/*
 * Klasse bringt alle wichtigen Librarys and bietet nützliche Methoden
 */

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
