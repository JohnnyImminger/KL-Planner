//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_STUDENT_H
#define KL_PLANNER_STUDENT_H

#include "Utility.h"

using namespace std;

class Student {
public:
    /*
     * Konstruktoren und toString();
     */
    Student();
    Student(int matikelNr, string studiengang);
    friend std::ostream& operator<<(std::ostream &out, const Student &student);
    /*
     * Getter
     */
    int getMatrikelNr() const;
    const string &getStudiengang() const;
    int getAnzKlausuren() const;
    const vector<int> &getKlausurIndizes() const;

    /*_____________________________________
     * Methoden:
     */

    //Methode added nur die Referenz aus dem Klausur-Vektor zu dem Studenten
    void addKlausur(int klausurIndex);

private:
    /*
     * Attribute
     */
    int matrikelNr;
    string studiengang;
    int anzKlausuren;
    vector<int> klausurIndizes; //speicherindex der Klausur im Pruefungsarray

    /*_____________________________________
     * Methoden:
     */

};
#endif //KL_PLANNER_STUDENT_H
