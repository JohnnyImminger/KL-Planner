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
        Klausur cKlausur = data.klausuren.at(i);
        Raum cRaum = data.raeume.at(cKlausur.getRaumRef());
        file << cKlausur << ';';
        file << cRaum.getAdrBau() << '/';
        file << cRaum.getAdrRaum() << ';';
        file << cKlausur.getTag() << ';';
        file << (float)cKlausur.getStartZeitTimeSlot()/Utility::timeSlotsProStunde + Utility::startZeitProTag << endl;
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


