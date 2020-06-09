//
// Created by Johnny on 08.06.2020.
//

#ifndef KL_PLANNER_READINPUT_H
#define KL_PLANNER_READINPUT_H

#include "Utility.h"
#include "Klausur.h"
#include "Student.h"
#include "Professor.h"
#include "Anmeldung.h"
#include "Raum.h"

using namespace std;

class ReadInput {
public:
    vector <Klausur> klausuren;
    vector <Anmeldung> anmeldungen;
    vector <Raum> raeume;
    vector <Professor> professoren;
    vector <Student> studenten;

    void init();
private:
    void parseInput();
    /*
     * initialisiert alle Studenten über die Anmeldungen und added direkt die jeweiligen Prueufungen
     */
    vector<Student> initStudenten(vector<Anmeldung> &anmeldungenListe, vector<Klausur> &pruefungenListe);
    /*
     * durchsucht einen vector von Professoren anhand der Identifikationsnummer und gibt den index zurück
     * ist der Professor nicht enthalten, ist der rückgabewert -1
     */
    int isProfInVector(int nr);
    /*
     * füllt den vector professoren anhand der Klausurenliste, speichert in jedem Prof die Indizes der Klausuren
     */
    void createProfs();
    /*
     * weist jeder klausur eine Liste von Studenten zu
     * !! darf erst gerufen werden, nachdem die Studenten erzeugt wurden
     */
    void attachStudentsToKlausur();
};


#endif //KL_PLANNER_READINPUT_H
