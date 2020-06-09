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
    //void addPruefung(Anmeldung &anmeldung, vector<Pruefung> &pruefungenListe); //added den Index aus Pruefungen in den Vector über identifikation in Anmeldung
    void addKlausur(int klausurIndex);
private:
    Student(int matikelNr, string studiengang); //Konstruktor

    int matrikelNr;
    string studiengang;
    //auslastung
    int anzKlausuren;
    vector<int> klausurIndizes; //speicherindex der Pruefung im Pruefungsarray

};


#endif //KL_PLANNER_STUDENT_H
