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

bool Algorithmus::isTimeSlotValidForProf(Professor& prof, int startTimeSlot, int dauerTimeSlot, int tag) {
    //iteriere über alle Klausuren die ein Prof hat
    for (int index : prof.getKlausurAufsichtIndex()) {
        //Hol die Klausur aus der Referenz
        Klausur beaufsichtigteKlausur = data.klausuren[index];
        //ist die Klausur vergeben?
        if (beaufsichtigteKlausur.getRaumRef() == -1) {
            continue;
        }
        //findet die Klausur am selben Tag statt?
        if (beaufsichtigteKlausur.getTag() == tag) {
            //TODO die conditions überprüfen
            //Ende der vorhandene Klausur + Prof Pause <= neue Startzeit
            bool c1 = beaufsichtigteKlausur.getStartZeitTimeSlot() + beaufsichtigteKlausur.getDauerTimeSlots() + Utility::timeSlotsPauseProf <= startTimeSlot;
            //Start der vorhandenen Klausur > Ende der neuen Klausur + Prof Pause
            bool c2 = beaufsichtigteKlausur.getStartZeitTimeSlot() > startTimeSlot + dauerTimeSlot + Utility::timeSlotsPauseProf;
            if(!c1 && !c2) {
                return false;
            }
        }
    }
    return true;
}

bool Algorithmus::isTimeSlotValidForStudent(Student& student, int startTimeSlot, int dauerTimeSlot, int tag) {
    return false;
}

bool Algorithmus::isTimeSlotValidForRoom(Raum& raum, int startTimeSlot, int dauerTimeSlot, int tag) {
    return false;
}


