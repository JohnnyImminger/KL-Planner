//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_RAUM_H
#define KL_PLANNER_RAUM_H

#include "Utility.h"

using namespace std;

class Raum {
public:
    /*
     * Konstruktoren und toString();
     */

    Raum();
    Raum(string &art, int adrBau, int adrRaum, int kap);
    friend std::ostream& operator<<(std::ostream &out, const Raum &raum);

    /*
     * Getter
     */

    const string &getRaumArt() const;
    int getAdrBau() const;
    int getAdrRaum() const;
    int getKapazataet() const;

    /*_____________________________________
     * Methoden:
     */

    //holt sich die Daten aus der csv
    static vector<Raum> parse(const string& pathToFile);

private:
    /*
     * Attribute
     */

    string raumArt;
    int adrBau;
    int adrRaum;
    int kapazataet;

    /*_____________________________________
     * Methoden:
     */
};

#endif //KL_PLANNER_RAUM_H
