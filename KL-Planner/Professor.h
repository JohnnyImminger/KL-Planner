//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_PROFESSOR_H
#define KL_PLANNER_PROFESSOR_H

#include "Utility.h"
#include "Klausur.h"

using namespace std;

class Professor {
public:
    /*
     * Konstruktoren und toString();
     */
    Professor();
    Professor(int identNr, string name);
    friend std::ostream& operator<<(std::ostream &out, const Professor &student);
    /*
     * Getter
     */
    void addPruefung(int pIndex);
    int getIdentNr() const;
    const string &getName() const;
    int getAnzPruefungen() const;

    /*_____________________________________
     * Methoden:
     */

private:
    /*
     * Attribute
     */
    int identNr;
    string name;
    int anzPruefungen;
    vector<int> pAufsichtIndex;

    /*_____________________________________
     * Methoden:
     */
};


#endif //KL_PLANNER_PROFESSOR_H
