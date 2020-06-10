//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Algorithmus.h"
#include <map>

/*
* Konstruktoren
*/

Algorithmus::Algorithmus(ReadInput& data) {
    this->data = data;
}



/*_____________________________________
* Methoden:
*/

/*
 * gruppieren der Klausuren nach studiengang
 * innerhalb der studiengänge nach größe der klausuren sortieren
 * rotierend alle studiengänge durchgehen und jeweils eine klausur einsortieren
 * klausur gegebenenfalls teilen und passenden raum suchen:
 *      - schauen ob der(die) raum(räume) zur gleichen zeit frei sind
 *          - wenn nein nächsten aktuelle startzeit ++ und nochmal versuchen
 *      - schauen ob der prof zeit hat
 *          - wenn nein neuen slot suchen
 *      - schauen ob alle studierenden zeit haben
 *          - wenn nein neuen slot suchen
 */
void Algorithmus::run() {
    map<string, vector<int>> klausuren = klausurenGroupByStudiengang();
    sortMap(klausuren);


}

void Algorithmus::sortMap(const map<string, vector<int>>& map) {
    for (const pair<string, vector<int>>& studiengang: map) {
        vector<int> curr = studiengang.second;
        //sort(curr.begin(), curr.end(), &Algorithmus::compareKlausurteilnehmergroesseByIndex);
    }
}

int Algorithmus::compareKlausurteilnehmergroesseByIndex(int index1, int index2) {
    int k1 = data.klausuren.at(index1).getAnzTeilnehmer();
    int k2 = data.klausuren.at(index2).getAnzTeilnehmer();
    if (k1 > k2) return 1;
    if (k1 == k2) return 0;
    return -1;
}

map<string, vector<int>> Algorithmus::klausurenGroupByStudiengang() {
    map<string,vector<int>> result;
    for(Klausur klausur : data.klausuren){
        if(result.find(klausur.getStudiengang()) == result.end()) {
            result.insert(pair<string, vector<int>>(klausur.getStudiengang(), vector<int>(klausur.getIndex())));
        } else {
            result.find(klausur.getStudiengang())->second.push_back(klausur.getIndex());
        }
    }
    return result;
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

bool Algorithmus::isTimeSlotValidForRoom(int raum, int startTimeSlot, int dauerTimeSlot, int tag) {
    return tage[tag].at(raum).areTimeSlotsFree(startTimeSlot, dauerTimeSlot);
}

bool Algorithmus::isTimeSlotTooLong(int startTimeSlot, int dauerTimeSlot) {
    return startTimeSlot + dauerTimeSlot <= Utility::timeSlotsProTag;
}