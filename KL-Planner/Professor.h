//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_PROFESSOR_H
#define KL_PLANNER_PROFESSOR_H

#include "Utility.h"
#include "Pruefung.h"
#include "ReadInput.h"

using namespace std;

class Professor {
public:
    Professor();
    friend std::ostream& operator<<(std::ostream &out, const Professor &student);
    static vector<Professor> createProfs();

    void addPruefung(int pIndex);
    int getIdentNr() const;
    const string &getName() const;
    int getAnzPruefungen() const;


private:
    Professor(int identNr, string& name);
    /*
     * durchsucht einen vector von Professoren anhand der Identifikationsnummer und gibt den index zurück
     * ist der Professor nicht enthalten, ist der rückgabewert -1
     */
    static int isProfInVector(vector<Professor> &profs, int nr);
    int identNr;
    string name;
    int anzPruefungen;
    vector<int> pAufsichtIndex;
    //auslastung
};


#endif //KL_PLANNER_PROFESSOR_H
