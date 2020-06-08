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
    Anmeldung();
    friend std::ostream& operator<<(std::ostream &out, const Anmeldung &anmeldung);
    static vector<Anmeldung> parse(string filename);

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
