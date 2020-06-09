//
// Created by Johnny on 08.06.2020.
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
