//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_READINPUT_H
#define KL_PLANNER_READINPUT_H

#include "Utility.h"
#include "Pruefung.h"
#include "Professor.h"

using namespace std;

class ReadInput {
public:
    static vector<Pruefung>* getPruefungen();
    /*
     * durchsucht einen vector von Professoren anhand der Identifikationsnummer und gibt den index zurück
     * ist der Professor nicht enthalten, ist der rückgabewert -1
     */
    static int isProfInVector(vector<Professor> &profs, int nr);
    static vector<Professor> createProfs();
};


#endif //KL_PLANNER_READINPUT_H
