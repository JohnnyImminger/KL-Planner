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

void Algorithmus::printResult(const string &filename) {
    ofstream file;
    file.open(filename);
    for (int i = 0; i < data.klausuren.size(); ++i) {
        file << data.klausuren.at(i) << ';';
        file << ' ' << ';';
        file << ' ' << ';';
        file << ' ' << ';';
        file << ' ' << ';';
        file << endl;
    }

}

bool Algorithmus::isTimeSlotValidForProf(Professor prof, int startTimeSlot, int dauerTimeSlot) {

}

bool Algorithmus::isTimeSlotValidForStudent(Student student, int startTimeSlot, int dauerTimeSlot) {
    return false;
}

bool Algorithmus::isTimeSlotValidForRoom(Raum raum, int startTimeSlot, int dauerTimeSlot) {
    return false;
}


