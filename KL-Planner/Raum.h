//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_RAUM_H
#define KL_PLANNER_RAUM_H

#include "Utility.h"

using namespace std;

class Raum {
public:
    Raum();
    friend std::ostream& operator<<(std::ostream &out, const Raum &raum);
    static vector<Raum> parseRaumliste(const string& pathToFile);

    const string &getRaumArt() const;
    int getAdrBau() const;
    int getAdrRaum() const;
    int getKapazataet() const;

private:
    Raum(string &art, int adrBau, int adrRaum, int kap);

    string raumArt;
    int adrBau;
    int adrRaum;
    int kapazataet;
    //auslastung
};

#endif //KL_PLANNER_RAUM_H
