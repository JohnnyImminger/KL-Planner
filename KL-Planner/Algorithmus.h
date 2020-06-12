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
    void printProfpalnliste(const string &filename);
    void printStudentplanliste(const string &filename);

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
     * In der Referenz nextStg wird für den nächsten aufruf gespeichert aus welchem studStudiengang dann gewählt werden soll
     * Klausuren ohne Teilnehmer werden automatisch aussortiert und somit auch nicht eingeplant
     */
    int selectNextKlausur(map<string, vector<int>> &map, string &nextStg);



    /*______________________________________________________________________________________________________________________
     * Klausur einsortieren und buchen
     */

    //versucht die Klausur in das System einzubuchen und das Ergebnis in Prüfung zu hinterlegen --> bei Erfolg return true

    bool findDateAndBookKlausur(Klausur& klausur);

    bool findDateAndBookKlausurIntoSingleRoom(Klausur& klausur);

    /*
     * Suche passende Räume nach verschiedenen Prioritäten
     */

    //Find timeSlots
    vector <int> getFillableStartTimesFromUsedRoom(int raumIndex, int day);

    //Find any room
    vector<int> findAvailableRaumForCapacity(int klausurSize, int minAbweichung, int maxAbweichung, int duration);
    //Find room at any time
    vector<int> findAvailableRaumAtDay(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day);
    //Find exact room
    vector<int> findAvailableRaumAtDayAndTime(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day, int startTime);

    //Used! - Find any room
    vector<int> findAvailableUsedRaumForCapacity(int klausurSize, int minAbweichung, int maxAbweichung, int duration);
    //Used! - Find room at any time
    vector<int> findAvailableUsedRaumAtDay(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day);
    //Used - Find exact room
    vector<int> findAvailableUsedRaumAtDayAndTime(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day, int startTime);

    //Utility
    bool isCapacityInRange(int freeRoomCapacity, int klausurSize, int minAbweichung, int maxAbweichung);

    /*
     * Klausur bei passendem Termin buchen
     */

    bool bookKlausurDate(Klausur& klausur, int startTime, int day, int raumDataIndex, int bookedCapacity);

    /*
     * Teilnehmer Bedingungen
     */
    bool areAllMemberAvailable(Klausur &klausur, int startTime, int duration, int day);
    bool areAllProfsOfKlausurAvailable(Klausur &klausur, int startTime, int duration, int day);
    bool areAllStudentsOfKlausurAvailable(Klausur &klausur, int startTime, int duration, int day);
    bool isProfAvailable(Professor& prof, int askedStartTime, int askedDuration, int day);
    bool isStudentAvailable(Student& student, int askedStartTime, int askedDuration, int day);
    bool isTimeOverlapping(int askedStartTime, int askedEndTime, int busyStartTime, int busyEndTime, int personalBreak);
    /*
     * Array Bedingungen
     */

    bool isTimeArrayLongEnough(int startTime, int duration);
    bool isRaumArrayLongEnough(int raumIndexSource);
    int increaseStartTag(int startTag); //make shure the day array is long enough

};


#endif //KL_PLANNER_ALGORITHMUS_H
