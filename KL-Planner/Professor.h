//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_PROFESSOR_H
#define KL_PLANNER_PROFESSOR_H

#include "Utility.h"

using namespace std;

class Professor {
public:
    Professor();
    friend std::ostream& operator<<(std::ostream &out, const Professor &student);

    void addPruefung();

private:
    Professor(int identNr, string& name);

    int identNr;
    string name;
    int anzPruefungen;
    //auslastung
};


#endif //KL_PLANNER_PROFESSOR_H
