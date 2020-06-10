//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_ALGORITHMUS_H
#define KL_PLANNER_ALGORITHMUS_H

#include "ReadInput.h"

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

    /*_____________________________________
     * Methoden:
     */

    //Utility::isTimeSlotTooLong(startTimeSlot, dauerTimeSlot)
    bool isTimeSlotValidForProf(Professor& prof, int startTimeSlot, int dauerTimeSlot, int tag);
    bool isTimeSlotValidForStudent(Student& student, int startTimeSlot, int dauerTimeSlot, int tag);
    bool isTimeSlotValidForRoom(Raum& raum,int startTimeSlot, int dauerTimeSlot, int tag);

};


#endif //KL_PLANNER_ALGORITHMUS_H
