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
    Professor(int identNr, string name);
    friend std::ostream& operator<<(std::ostream &out, const Professor& professor);

    /*
     * Getter und Setter
     */

    int getIndex() const;
    int getIdentNr() const;
    const string &getName() const;
    int getExamCount() const;
    const vector<int> &getExamIndices() const;

    void setIndex(int index);

    /*_____________________________________
     * Methoden:
     */

    //Methode added nur die Referenz aus dem Exam-Vektor zu dem Studenten
    void addKlausur(int examIndex);

private:
    /*
     * Attribute
     */

    int index;
    int identNr;
    string name;
    int ExamCount;
    vector<int> examIndices;

};

#endif //KL_PLANNER_PROFESSOR_H
