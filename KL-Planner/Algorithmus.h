//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_ALGORITHMUS_H
#define KL_PLANNER_ALGORITHMUS_H

#include "ReadInput.h"
#include <map>

using namespace std;

class Algorithmus {

public:
    /*
     * Konstruktoren
     */

    explicit Algorithmus(ReadInput& data);

    /*_____________________________________
     * Methoden:
     */

    void run();
    void initTage();
    void printResult(const string &filename);
    void printRaumplanliste(const string &filename);

private:
    /*
     * Attribute
     */

    ReadInput data;
    vector<Raum> tage [Utility::klausurTage]; //9 Tage
    int lastSortedDay;

    /*_____________________________________
     * Methoden:
     */

    //string ist der studiengangname, vector<int> eine liste mit Indices der dazugehörigen klausuren
    map<string, vector<int>> klausurenGroupByStudiengang();
    //sortiert die vektoren der Map die vorbereitend von klausurenGroupByStudiengang erzeugt wurde. Vergleichswert ist die Anzahl der Teilnehmer der Klausur
    void sortMap(const map<string, vector<int>>& map);
    /*
     * wählt rotierend über die Studiengänge die nächste einzuplanende Klausur aus und entfernt sie aus dem vektor.
     * Ist der Vektor leer wird der Studiengang aus der Map entfernt.
     * Ist die map leer wird -1 zurückgegeben
     * In der Referenz nextStg wird für den nächsten aufruf gespeichert aus welchem studiengang dann gewählt werden soll
     * Klausuren ohne Teilnehmer werden automatisch aussortiert und somit auch nicht eingeplant
     */
    int selectNextKlausur(map<string, vector<int>> &map, string &nextStg);

    //Utility::isTimeSlotTooLong(startTimeSlot, dauerTimeSlot)
    bool isTimeSlotValidForProf(Professor& prof, int startTimeSlot, int dauerTimeSlot, int tag);
    bool isTimeSlotValidForStudent(Student& student, int startTimeSlot, int dauerTimeSlot, int tag);

    /*______________________________________________________________________________________________________________________
     * Klausur einsortieren und buchen
     */
    bool isTimeSlotTooLong(int startTimeSlot, int dauerTimeSlot);
    //versucht die Klausur in das System einzubuchen und das Ergebnis in Prüfung zu hinterlegen --> bei Erfolg return true
    bool einsortierenKlausur(Klausur& klausur);
    bool einsortierenKlausurInGleichGrossenRaum(Klausur &klausur, int maxAbweichung);
    bool checkProfForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag);
    bool checkStudentForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag);
    bool checkRaeumeByKapazitaetForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag,int raumStartIndex);
    bool checkRaeumeByVectorSizeForEinsortieren(Klausur &klausur, int startTag,int raumStartIndex);

    vector<int> findePassendeRaumIndices(int klausurKapazitaet, int maxAbweichung);

    int increaseStartTag(int startTag);
};


#endif //KL_PLANNER_ALGORITHMUS_H
