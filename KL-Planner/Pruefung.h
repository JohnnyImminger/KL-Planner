//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_PRUEFUNG_H
#define KL_PLANNER_PRUEFUNG_H

#include "Utility.h"

using namespace std;

class Pruefung {

public:
    Pruefung();
    friend std::ostream& operator<<(std::ostream &out, const Pruefung &anmeldung);
    static vector<Pruefung> parse(string pathToFile);

private:
    Pruefung(string& studiengang, int verteilt, int pVersion, int pNummer, string& pName,
             int pPruefer1, string& pruefer1, int pPruefer2, string& pruefer2,
             float pDauer, string& pForm, int pSemester, bool angeboten);

    string studiengang;
    int verteilt; //maybe bool
    int pVersion;
    int pNummer;
    string pName;
    int pPruefer1;
    string pruefer1;
    int pPruefer2;
    string pruefer2;
    float pDauer;
    string pForm;
    int pSemester;
    bool angeboten;

};

#endif //KL_PLANNER_PRUEFUNG_H
