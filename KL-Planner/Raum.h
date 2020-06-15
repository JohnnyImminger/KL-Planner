//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_RAUM_H
#define KL_PLANNER_RAUM_H

#include "Utility.h"

using namespace std;

class Raum {
public:

    /*
     * Konstruktoren und toString();
     */

    Raum();
    Raum(string &art, int adrBau, int adrRaum, int cap);
    friend std::ostream& operator<<(std::ostream &out, const Raum &raum);

    void printTimeSlots(ostream &out);
    void printFreeTimeslots(ostream& out);

    /*
     * Getter
     */

    const string &getRaumArt() const;
    int getAdrBau() const;
    int getAdrRaum() const;
    int getCapacity() const;
    const int *getTimeSlots() const;

    /*_____________________________________
     * Methoden:
     */

    static vector<Raum> parse(const string& pathToFile);


    /*
     * Ressourcen-System
     */

    //prüft ob die Timeslots verfügbar sind, berücksichtigt direkt die Pause für den Raum
    int getFreeSpaceAt(int startTime, int duration);

    bool isEmpty(int start, int dauer);

    //belegt die Timeslots, berücksichtigt direkt die Pause für den Raum
    bool bookTimeSlots(int startTime, int duration, int capacity);


private:
    /*
     * Attribute
     */

    string raumArt;
    int adrBau;
    int adrRaum;
    int capacity;
    int timeSlots[Utility::timeSlotsProTag + Utility::timeSlotsPauseRaum]; //[40] je 15min slots + die Pause als imaginärer Puffer, 0 = raum ist voll



};

#endif //KL_PLANNER_RAUM_H
