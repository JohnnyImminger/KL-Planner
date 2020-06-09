//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_STUDENT_H
#define KL_PLANNER_STUDENT_H

#include "Utility.h"
#include "Anmeldung.h"
#include "Pruefung.h"

using namespace std;

class Student {
public:
    Student(); //Konstruktor
    friend std::ostream& operator<<(std::ostream &out, const Student &student); //toString()
    //getter
    int getMatrikelNr() const;
    const string &getStudiengang() const;

    static vector<Student> initStudenten(vector<Anmeldung>& anmeldungenListe, vector<Pruefung>& pruefungenListe); //initialisiert alle Studenten über die Anmeldungen und added direkt die jeweiligen Prueufungen

private:
    Student(int matikelNr, string studiengang); //Konstruktor
    void addPruefung(Anmeldung& anmeldung, vector<Pruefung>& pruefungenListe); //added den Index aus Pruefungen in den Vector über identifikation in Anmeldung

    int matrikelNr;
    string studiengang;
    //auslastung

    vector<int> pruefungsIndex; //speicherindex der Pruefung im Pruefungsarray

};


#endif //KL_PLANNER_STUDENT_H
