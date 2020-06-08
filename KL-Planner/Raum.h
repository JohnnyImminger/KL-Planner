//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_RAUM_H
#define KL_PLANNER_RAUM_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include "Raum.h"
#include "Utility.h"

using namespace std;

class Raum {
public:
    Raum();
    Raum(string &art, int adrBau, int adrRaum, int kap);

    friend std::ostream& operator<<(std::ostream &out, const Raum &raum);
    static vector<Raum> parseRaumliste(string pathToFile);

private:
    string raumArt;
    int adrBau;
    int adrRaum;
    int kapazataet;
    //auslastung

    Raum parseRaum(string &s);


};


#endif //KL_PLANNER_RAUM_H
