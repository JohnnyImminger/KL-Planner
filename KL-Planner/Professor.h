//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_PROFESSOR_H
#define KL_PLANNER_PROFESSOR_H

#include "Utility.h"

using namespace std;

class Professor {
public:
    /*
     * Konstruktoren und toString();
     */

    Professor();
    Professor(int identNr, string& name);
    friend std::ostream& operator<<(std::ostream &out, const Professor &student);

    /*
     * Getter und Setter
     */

    int getDataIndex() const;
    int getIdentNr() const;
    const string &getName() const;
    int getAnzKlausuren() const;
    const vector<int> &getKlausurDataIndizes() const;

    void setIndex(int index);

    /*_____________________________________
     * Methoden:
     */

    //Methode added nur die Referenz aus dem Klausur-Vektor zu dem Studenten
    void addKlausur(int klausurDataIndex);

private:
    /*
     * Attribute
     */

    int dataIndex;
    int identNr;
    string name;
    int anzKlausuren;
    vector<int> klausurDataIndizes;

};

#endif //KL_PLANNER_PROFESSOR_H
