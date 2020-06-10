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

        file << cKlausur << ';';

        vector<int> klausurRaeume = cKlausur.getRaumRefs();
        for (int j: klausurRaeume) {
            Raum cRaum = data.raeume.at(j);
            file << cRaum.getAdrBau() << '/';
            file << cRaum.getAdrRaum() << ';';
        }

        file << cKlausur.getTag() << ';';
        file << (float)cKlausur.getStartZeitTimeSlot()/Utility::timeSlotsProStunde + Utility::startZeitProTag << endl;
    }
}

bool Algorithmus::isTimeSlotValidForProf(Professor& prof, int startTimeSlot, int dauerTimeSlot, int tag) {
    //iteriere über alle Klausuren die ein Prof hat
    for (int index : prof.getKlausurAufsichtIndices()) {
        //Hol die Klausur aus der Referenz
        Klausur beaufsichtigteKlausur = data.klausuren[index];
        //ist die Klausur vergeben?
        if (beaufsichtigteKlausur.getRaumRefs().empty()) {
            continue;
        }
        //findet die Klausur am selben Tag statt?
        if (beaufsichtigteKlausur.getTag() == tag) {
            //Ende der vorhandene Klausur + Prof Pause <= neue Startzeit
            bool c1 = beaufsichtigteKlausur.getStartZeitTimeSlot() + beaufsichtigteKlausur.getDauerTimeSlots() + Utility::timeSlotsPauseProf <= startTimeSlot;
            //Start der vorhandenen Klausur >= Ende der neuen Klausur + Prof Pause
            bool c2 = beaufsichtigteKlausur.getStartZeitTimeSlot() >= startTimeSlot + dauerTimeSlot + Utility::timeSlotsPauseProf;
            if(!(c1&&c2)) {
                return false;
            }
        }
    }
    return true;
}

bool Algorithmus::isTimeSlotValidForStudent(Student& student, int startTimeSlot, int dauerTimeSlot, int tag) {
    //iteriere über alle Klausuren die ein Prof hat
    for (int index : student.getKlausurIndices()) {
        //Hol die Klausur aus der Referenz
        Klausur angemeldeteKlausur = data.klausuren[index];
        //ist die Klausur vergeben?
        if (angemeldeteKlausur.getRaumRefs().empty()) {
            continue;
        }
        //findet die Klausur am selben Tag statt?
        if (angemeldeteKlausur.getTag() == tag) {
            //Ende der vorhandene Klausur + Prof Pause <= neue Startzeit
            bool c1 = angemeldeteKlausur.getStartZeitTimeSlot() + angemeldeteKlausur.getDauerTimeSlots() + Utility::timeSlotsPauseStudent <= startTimeSlot;
            //Start der vorhandenen Klausur >= Ende der neuen Klausur + Prof Pause
            bool c2 = angemeldeteKlausur.getStartZeitTimeSlot() >= startTimeSlot + dauerTimeSlot + Utility::timeSlotsPauseStudent;
            if(!(c1&&c2)) {
                return false;
            }
        }
    }
    return true;
}

bool Algorithmus::isTimeSlotValidForRoom(Raum& raum, int startTimeSlot, int dauerTimeSlot, int tag) { //TODO überprüfen von Konsrukten
    return raum.areTimeSlotsFree(startTimeSlot,dauerTimeSlot);
}

bool Algorithmus::isTimeSlotTooLong(int startTimeSlot, int dauerTimeSlot) {
    return startTimeSlot + dauerTimeSlot <= Utility::timeSlotsProTag;
}


