//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
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
    /*
     * Attribute
     */
    vector <Klausur> klausuren;
    vector <Anmeldung> anmeldungen;
    vector <Raum> raeume;
    vector <Professor> professoren;
    vector <Student> studenten;

    /*_____________________________________
     * Methoden:
     */

    //füllt alle Daten auf
    void init();

private:
    /*_____________________________________
     * Methoden:
     */

    //ruft alle parse Methoden für die csv-Dateien auf
    void parseInput();
    //füllt den vector professoren anhand der Klausurenliste, speichert in jedem Prof die Indizes der Klausuren
    void createProfs();
    //methode um einen prof zu verarbeiten und duplizierten code zu vermeiden
    void processProf(int klausurIndex, int id, const string &name);
    //durchsucht einen vector von Professoren anhand der Identifikationsnummer und gibt den index zurück ist der Professor nicht enthalten, ist der rückgabewert -1
    int isProfInVector(int identNr);

    //darf erst gerufen werden, nachdem die Studenten erzeugt wurden!! - weist jeder klausur eine Liste von Studenten zu
    void attachStudentsToKlausur();

    //TODO add comment like Prof
    void createStudenten();
    int isStudentInVector(int matrikelNr);
    int findKlausurIndex(int pNummer, int pVersion);
};


#endif //KL_PLANNER_READINPUT_H
