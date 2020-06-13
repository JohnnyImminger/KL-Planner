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
    Klausur(string& studiengang, string& vertiefung, int pVersion, int pNummer, string& pName,
            int pPruefer1, string& pruefer1, int pPruefer2, string& pruefer2,
            float pDauer, string& pForm, int pSemester, bool angeboten);
    friend std::ostream& operator<<(std::ostream &out, const Klausur &anmeldung);

    /*
     * Getter und Setter
     */

    int getDataIndex();
    const string &getStudiengang() const;
    const string &getVertiefung() const;
    int getVersion() const;
    int getNummer() const;
    const string &getName() const;
    int getPruefer1IdentNr() const;
    const string &getPruefer1Name() const;
    int getPruefer2IdentNr() const;
    const string &getPruefer2Name() const;
    float getDauerFloat() const;
    int getDauerTimeSlots() const;
    const string &getKlausurForm() const;
    int getSemester() const;
    bool isAngeboten() const;
    bool isPlanbar() const; //TODO Planbar is never used?
    bool isEingeplant() const;

    vector<int> getProfs();
    const vector<int> &getStudenten() const;
    int getAnzTeilnehmer() const;

    vector<int> getRaumRefs();
    int getTag() const;
    int getStartZeitTimeSlot() const;


    void setIndex(int index);
    void setPlanbar(bool planbar);
    void setEingeplant(bool eingeplant);

    void setTag(int tag);
    void setStartZeitTimeSlot(int startZeitTimeSlot);

    /*_____________________________________
     * Methoden:
     */

    //holt sich die Daten aus der csv
    static vector<Klausur> parse(const string& pathToFile);

    //added den Index des Studenten
    void addStudent(int studentDataIndex);
    void addProf(int profDataIndex);
    void addRaumRef(int raumRef);
    void removeRaumRef(int index);

private:
    /*
     * Attribute
     */

    int dataIndex;
    string studiengang;
    string vertiefung;
    int version;
    int nummer;
    string name;
    int pruefer1IdentNr;
    string pruefer1Name;
    int pruefer2IdentNr;
    string pruefer2Name;
    float dauer;
    int dauerTimeSlots;
    string klausurForm;
    int semester;
    bool angeboten;
    bool planbar;
    bool eingeplant;

    vector<int> profRefs;
    vector<int> studenten;
    int anzTeilnehmer;

    vector<int> raumRefs;
    int tag;
    int startZeitTimeSlot;

    /*_____________________________________
     * Methoden:
     */
    static void outputIgnored(const string& line);

};

#endif //KL_PLANNER_KLAUSUR_H
