//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_ROOM_H
#define KL_PLANNER_ROOM_H

#include "Utility.h"

using namespace std;

class Room {
public:

    /*
     * Konstruktoren und toString();
     */

    Room();
    Room(string &kindOfRoom, int building, int adrRoom, int capacity);
    friend std::ostream& operator<<(std::ostream &out, const Room &room);

    /*
     * Getter
     */

    int getAdrBau() const;
    int getAdrRaum() const;
    int getCapacity() const;

    /*_____________________________________
     * Methoden:
     */

    static vector<Room> parse(const string& pathToFile);

    void printTimeSlots(ostream &out);
    void printFreeTimeslots(ostream& out);

    /*
     * Ressourcen-System
     */

    //prüft ob die Timeslots verfügbar sind, berücksichtigt direkt die Pause für den Room
    int getFreeSpaceAt(int start, int duration);

    bool isEmpty(int start, int duration);

    //belegt die Timeslots, berücksichtigt direkt die Pause für den Room
    bool bookTimeSlots(int start, int duration, int capacity);


private:
    /*
     * Attribute
     */

    string kindOfRoom;
    int building;
    int adrRoom;
    int capacity;
    int timeSlots[Utility::timeSlotsProTag + Utility::timeSlotsPauseRaum]{}; //[40] je 15min slots + die Pause als imaginärer Puffer, 0 = raum ist voll



};

#endif //KL_PLANNER_ROOM_H
