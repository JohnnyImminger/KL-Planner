//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_KLAUSUR_H
#define KL_PLANNER_KLAUSUR_H

#include "Utility.h"
#include "Anmeldung.h"
#include "Student.h"


using namespace std;

class Klausur {

public:
    /*
     * Konstruktoren und toString();
     */

    Klausur();
    Klausur(string& studiengang, int verteilt, int pVersion, int pNummer, string& pName,
            int pPruefer1, string& pruefer1, int pPruefer2, string& pruefer2,
            float pDauer, string& pForm, int pSemester, bool angeboten);
    friend std::ostream& operator<<(std::ostream &out, const Klausur &anmeldung);

    /*
     * Getter und Setter
     */

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
    const vector<int> &getStudenten() const;
    int getIndex();
    void setIndex(int index);
    int getAnzTeilnehmer() const;

    int getPDauerTimeSlots() const;

    /*_____________________________________
     * Methoden:
     */

    //holt sich die Daten aus der csv
    static vector<Klausur> parse(string pathToFile);

    //added den Index des Studenten
    void addStudent(int studentenIndex);

private:
    /*
     * Attribute
     */

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
    int pDauerTimeSlots;
    string pForm;
    int pSemester;
    bool angeboten;
    int index;

    vector<int> studenten;
    int anzTeilnehmer;

    /*_____________________________________
     * Methoden:
     */

};

#endif //KL_PLANNER_KLAUSUR_H
