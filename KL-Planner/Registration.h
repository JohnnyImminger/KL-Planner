//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_REGISTRATION_H
#define KL_PLANNER_REGISTRATION_H

#include "Utility.h"

using namespace std;

class Registration {
public:
    /*
     * Konstruktoren und toString();
     */

    Registration();
    Registration(int matrikelNr, string &course, int examVersion, int examNr, string &kindOfExam, string &description, int examSemester);
    friend std::ostream& operator<<(std::ostream &out, const Registration &registration);

    /*
     * Getter
     */

    int getMatrikelNr() const;
    const string &getCourse() const;
    int getExamVersionNr() const;
    int getExamNr() const;
    const string &getKindOfExamShort() const;
    const string &getKindOfExamLong() const;
    int getExamSemester() const;

    /*_____________________________________
     * Methoden:
     */

    //holt sich die Daten aus der csv
    static vector<Registration> parse(const string& filename);

private:
    /*
     * Attribute
     */

    int martrikelNummer;
    string course;
    int examVersionNr;
    int examNr;
    string kindOfExamShort;
    string KindOfExamLong;
    int examSemester;
};


#endif //KL_PLANNER_REGISTRATION_H
