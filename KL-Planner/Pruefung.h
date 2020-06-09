//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_PRUEFUNG_H
#define KL_PLANNER_PRUEFUNG_H

#include "Utility.h"
#include "Anmeldung.h"

using namespace std;

class Pruefung {

public:
    Pruefung();
    friend std::ostream& operator<<(std::ostream &out, const Pruefung &anmeldung);
    static vector<Pruefung> parse(string pathToFile);
    void collectAnmeldungen(vector<Anmeldung> anmeldungenListe);

    const string &getStudiengang() const;
    int getVerteilt() const;
    int getPVersion() const;
    int getPNummer() const;
    const string &getPName() const;
    int getPPruefer1() const;
    const string &getPruefer1() const;
    int getPPruefer2() const;
    const string &getPruefer2() const;
    float getPDauer() const;
    const string &getPForm() const;
    int getPSemester() const;
    bool isAngeboten() const;
    const vector<Anmeldung> &getAnmeldungen() const;
    int getIndex();
    void setIndex(int index);

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
    int index;

    vector<Anmeldung> anmeldungen;

};

#endif //KL_PLANNER_PRUEFUNG_H
