//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_ANMELDUNG_H
#define KL_PLANNER_ANMELDUNG_H

#include "Utility.h"

using namespace std;

class Anmeldung {
public:
    /*
     * Konstruktoren und toString();
     */

    Anmeldung();
    Anmeldung(int matrikelNr, string &studiengang, int pVersion, int pNummer, string &pForm, string &dText, int pSemester);
    friend std::ostream& operator<<(std::ostream &out, const Anmeldung &anmeldung);

    /*
     * Getter
     */

    int getMatrikelNr() const;
    const string &getStudiengang() const;
    int getPVersion() const;
    int getPNummer() const;
    const string &getPForm() const;
    const string &getDText() const;
    int getPSemester() const;

    /*_____________________________________
     * Methoden:
     */

    //holt sich die Daten aus der csv
    static vector<Anmeldung> parse(const string& filename);

private:
    /*
     * Attribute
     */

    int matrikelNr;
    string studiengang;
    int pVersion;
    int pNummer;
    string pForm;
    string dText;
    int pSemester;

    /*_____________________________________
     * Methoden:
     */
};


#endif //KL_PLANNER_ANMELDUNG_H
