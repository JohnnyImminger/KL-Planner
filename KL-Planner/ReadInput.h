//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_READINPUT_H
#define KL_PLANNER_READINPUT_H

#include "Utility.h"
#include "Exam.h"
#include "Student.h"
#include "Professor.h"
#include "Registration.h"
#include "Room.h"

using namespace std;

class ReadInput {
public:
    /*
     * Attribute
     */

    vector <Exam> exams;
    vector <Registration> registrations;
    vector <Room> rooms;
    vector <Professor> profs;
    vector <Student> students;

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

    //füllt den vector profs anhand der Klausurenliste, speichert in jedem Prof die Indizes der Klausuren
    void createProfs();

    //methode um einen prof zu verarbeiten und duplizierten code zu vermeiden
    void processProf(int examIndex, int id, const string &name);

    //vergibt allen Profs einen index
    void indexProfs();

    //durchsucht einen vector von Professoren anhand der Identifikationsnummer und gibt den index zurück ist der Professor nicht enthalten, ist der rückgabewert -1
    int isProfInVector(int identNr);

    //darf erst gerufen werden, nachdem die Studenten erzeugt wurden!! - weist jeder klausur eine Liste von Studenten zu
    void attachStudentsToKlausur();

    //füllt den vector student anhand der Anmeldungsliste, speichert in jedem Student die zur Registration zugehörige Exam
    void createStudents();

    //durchsucht einen vector von Studenten anhand der Identifikationsnummer und gibt den index zurück ist der Student nicht enthalten, ist der rückgabewert -1
    int isStudentInVector(int matrikelNr);

    /*
     * Klausuren sind eindeutig definier durch Studiengang, SPO-Version und Prüfungsnummer.
     * Abgebildet durch: string course, int version und id.
     * Methode durchsucht den vector exams danach und gibt den Index der Exam zurück.
     * Kann die klausur nicht gefunden werden ist der Rückgabewert -1.
     */
    int findExamIndex(const string& course, int examVersion, int examNr);
};


#endif //KL_PLANNER_READINPUT_H
