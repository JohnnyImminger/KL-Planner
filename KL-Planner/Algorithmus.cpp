//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Algorithmus.h"

/*
* Konstruktoren
*/

Algorithmus::Algorithmus(ReadInput& data) {
    this->data = data;
}



/*_____________________________________
* Methoden:
*/

void Algorithmus::run() {

}

void Algorithmus::initTage() {
    for (int i = 0; i < Utility::klausurTage; i++) {
        tage[i] = data.raeume;
    }
}

void Algorithmus::printResult() {

}

bool Algorithmus::isTimeSlotValidForProf(Professor prof, int startTimeSlot, int dauerTimeSlot) {

}

bool Algorithmus::isTimeSlotValidForStudent(Student student, int startTimeSlot, int dauerTimeSlot) {
    return false;
}

bool Algorithmus::isTimeSlotValidForRoom(Raum raum, int startTimeSlot, int dauerTimeSlot) {
    return false;
}


