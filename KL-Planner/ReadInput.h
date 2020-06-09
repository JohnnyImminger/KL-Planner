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
    static vector <Klausur> klausuren;
    static vector <Anmeldung> anmeldungen;
    static vector <Raum> raeume;
    static vector <Professor> professoren;
    static vector <Student> studenten;

    void parseInput();
private:
    /*
     * initialisiert alle Studenten über die Anmeldungen und added direkt die jeweiligen Prueufungen
     */
    static vector<Student> initStudenten(vector<Anmeldung> &anmeldungenListe, vector<Klausur> &pruefungenListe);
    /*
     * durchsucht einen vector von Professoren anhand der Identifikationsnummer und gibt den index zurück
     * ist der Professor nicht enthalten, ist der rückgabewert -1
     */
    static int isProfInVector(vector<Professor> &profs, int nr);
    static vector<Professor> createProfs();

};


#endif //KL_PLANNER_READINPUT_H
