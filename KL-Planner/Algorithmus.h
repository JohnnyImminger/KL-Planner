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

    //gibt einen sortierten vektor mit Klausurindices nach Größe und Länge zurück
    vector<int> sortKlausurenBySize();

    /*
     * gibt den nächsten index aus dem Vektor zurück, es sei denn
     */
    int selectNextKlausur(vector<int> &indices);
    /*______________________________________________________________________________________________________________________
     * Klausur einsortieren und buchen
     */
    bool scheduleKlausur(Klausur& klausur);
    vector<int> getRoomIndicesForKlausur(Klausur& klausur, int day, int start);
    vector<int> getSelectableRoomIndices(Klausur& kl, int day, int start);
    void sortRoomIndicesBySize(vector<int>& indices);
    /*
     * Klausur bei passendem Termin buchen
     */
    bool bookKlausur(Klausur& klausur, int day, int start, vector<int>& roomIndices);

    /*
     * Teilnehmer Bedingungen
     */
    bool areAllMemberAvailable(Klausur &klausur, int startTime, int duration, int day);
    bool areAllProfsOfKlausurAvailable(Klausur &klausur, int startTime, int duration, int day);
    bool areAllStudentsOfKlausurAvailable(Klausur &klausur, int startTime, int duration, int day);
    bool isProfAvailable(Professor& prof, int askedStartTime, int askedDuration, int day);
    bool isStudentAvailable(Student& student, int askedStartTime, int askedDuration, int day);
    bool isTimeOverlapping(int askedStartTime, int askedEndTime, int busyStartTime, int busyEndTime, int personalBreak);
};


#endif //KL_PLANNER_ALGORITHMUS_H
