//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_ANMELDUNG_H
#define KL_PLANNER_ANMELDUNG_H

#include <string>
#include <vector>

using namespace std;

class Anmeldung {
public:
    static vector<Anmeldung> parse(string &filename);
    friend std::ostream& operator<<(std::ostream &out, const Anmeldung &anmeldung);
private:
    Anmeldung(int matrikelNr, string &studiengang, int pVersion, int pNummer, string &pForm, string &dText, int pSemester);
    int matrikelNr;
    string studiengang;
    int pVersion;
    int pNummer;
    string pForm;
    string dText;
    int pSemester;
};


#endif //KL_PLANNER_ANMELDUNG_H
