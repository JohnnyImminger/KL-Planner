//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_STUDENT_H
#define KL_PLANNER_STUDENT_H

#include "Utility.h"

using namespace std;

class Student {
public:
    Student();
    friend std::ostream& operator<<(std::ostream &out, const Student &student);

    void addPruefung();

private:
    Student(int matikelNr, string& studiengang);

    int matrikelNr;
    string studiengang;
    int anzPruefungen;
    //auslastung

};


#endif //KL_PLANNER_STUDENT_H
