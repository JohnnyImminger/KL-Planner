//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_PROFESSOR_H
#define KL_PLANNER_PROFESSOR_H

#include "Utility.h"
#include "Klausur.h"

using namespace std;

class Professor {
public:
    Professor();
    Professor(int identNr, string name);
    friend std::ostream& operator<<(std::ostream &out, const Professor &student);
    void addPruefung(int pIndex);
    int getIdentNr() const;
    const string &getName() const;
    int getAnzPruefungen() const;


private:
    int identNr;
    string name;
    int anzPruefungen;
    vector<int> pAufsichtIndex;
    //auslastung
};


#endif //KL_PLANNER_PROFESSOR_H
