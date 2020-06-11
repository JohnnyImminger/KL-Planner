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
    bool isTimeSlotTooLong(int startTimeSlot, int dauerTimeSlot);

private:
    /*
     * Attribute
     */

    ReadInput data;
    //9 Tage
    vector<Raum> tage [Utility::klausurTage];
    int lastSortedDay;

    /*_____________________________________
     * Methoden:
     */

    //string ist der studiengangname, vector<int> eine liste mit Indices der dazugehörigen klausuren
    map<string, vector<int>> klausurenGroupByStudiengang();
    void sortMap(const map<string, vector<int>>& map);

    //Utility::isTimeSlotTooLong(startTimeSlot, dauerTimeSlot)
    bool isTimeSlotValidForProf(Professor& prof, int startTimeSlot, int dauerTimeSlot, int tag);
    bool isTimeSlotValidForStudent(Student& student, int startTimeSlot, int dauerTimeSlot, int tag);
    bool isTimeSlotValidForRoom(int raum,int startTimeSlot, int dauerTimeSlot, int tag);

    int selectNextKlausur(string &lastStg, map<string, vector<int>> &map);

    //versucht die Klausur in das System einzubuchen und das Ergebnis in Prüfung zu hinterlegen --> bei Erfolg return true
    bool einsortierenKlausur(Klausur& klausur);
    bool einsortierenKlausurInGleichGroßenRaum(Klausur &klausur, int maxAbweichung);
    bool checkProfForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag);
    bool checkStudentForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag);
    bool checkRaeumeByKapazitaetForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag,int raumStartIndex);
    bool checkRaeumeByVectorSizeForEinsortieren(Klausur &klausur, int startTag,int raumStartIndex);

    vector<int> findePassendeRaumIndices(int klausurKapazitaet, int maxAbweichung);
};


#endif //KL_PLANNER_ALGORITHMUS_H
