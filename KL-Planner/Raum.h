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
    Raum(string &art, int adrBau, int adrRaum, int kap);
    friend std::ostream& operator<<(std::ostream &out, const Raum &raum);

    void printFreeTimeslots(ostream& out);

    /*
     * Getter
     */

    const string &getRaumArt() const;
    int getAdrBau() const;
    int getAdrRaum() const;
    int getKapazitaet() const;

    /*_____________________________________
     * Methoden:
     */

    //holt sich die Daten aus der csv
    static vector<Raum> parse(const string& pathToFile);

    //prüft ob die Timeslots verfügbar sind, berücksichtigt direkt die Pause für den Raum
    bool areTimeSlotsFree(int startTimeSlot, int dauerTimeSlot);

    //belegt die Timeslots, berücksichtigt direkt die Pause für den Raum
    void useTimeSlots(int startTimeSlot, int dauerTimeSlot);

private:
    /*
     * Attribute
     */

    string raumArt;
    int adrBau;
    int adrRaum;
    int kapazitaet;

    //[40] je 15min slots + die Pause als imaginärer Puffer, false = nicht belegt
    bool timeSlots[Utility::timeSlotsProTag + Utility::timeSlotsPauseRaum] = {false};

    /*_____________________________________
     * Methoden:
     */
};

#endif //KL_PLANNER_RAUM_H
