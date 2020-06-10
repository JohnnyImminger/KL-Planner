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
    this->lastSortedDay = 0;
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
    string lastStudiengang = "AB";
    int nextKlausur = selectNextKlausur(lastStudiengang, klausuren);

}

int Algorithmus::selectNextKlausur(string &lastStg, map <string, vector<int>> &map) {



    return 0;
}

void Algorithmus::sortMap(const map<string, vector<int>>& map) { //TODO sort funktioniert nicht
    for (const auto & studiengang: map) {
        vector<int> klausuren = studiengang.second;
        bool swapped;
        do {
            swapped = false;
            for (int i = 0; i < klausuren.size()-1; ++i) {
                if(data.klausuren.at(klausuren.at(i)).getAnzTeilnehmer() > data.klausuren.at(klausuren.at(i+1)).getAnzTeilnehmer()) {
                    int tmp = klausuren.at(i);
                    klausuren.at(i) = klausuren.at(i+1);
                    klausuren.at(i+1) = tmp;
                    swapped = true;
                }
            }
        } while (swapped);
    }
}

map<string, vector<int>> Algorithmus::klausurenGroupByStudiengang() {
    //TODO ergebnis der methode ist so nicht verwendbar-> im debugger zu sehen
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

bool Algorithmus::einsortierenKlausur(Klausur &klausur) {
    int failCount = 0;
    int startZeitTimeSlot = 0;
    int startTag = lastSortedDay;
    int dauerTimeSlot = klausur.getDauerTimeSlots();
    int anzTeilnehmer = klausur.getAnzTeilnehmer();
    int raumIndex = 0;

    while(true){
        /*______________________________________________________________________________________________________________
         * Das Ende eines Tages wird erst sehr spät erreicht und resettet den Prozess
         */
        if (isTimeSlotTooLong(startZeitTimeSlot,dauerTimeSlot)){
            if (failCount >= 18){
                return false;
            }
            startZeitTimeSlot = 0;
            startTag = Utility::getRandomInt(Utility::klausurTage);

            failCount++;
            continue;
        }
        /*______________________________________________________________________________________________________________
         * Suche einen Raum - niedirige Uhrzeiten werden zuerst aufgefüllt
         */
        //Überprüft ob genug räume an diesem Tag zur verfügung stehen um die kapazitaet unterzubringen
        if (checkRaeumeByVectorSizeForEinsortieren(klausur, startTag, raumIndex)){
            startTag++;
            //wenn in allen Tagen nichts zu dieser Zeit gefunden wurde, erhöhe die Zeit
            if (startTag == lastSortedDay){
                startZeitTimeSlot++;
            }
            continue;
        }
        //überprüft ob genug die Räume zu dieser Zeit verfügbar sind um die kapazitaet unterzubringen
        if (!checkRaeumeByKapazitaetForEinsortieren(klausur, startZeitTimeSlot, dauerTimeSlot, startTag, raumIndex)){
            raumIndex++;
            continue;
        }
        /*______________________________________________________________________________________________________________
         * Raum gefunden! Überprüfe Termin für die Teilnehmer der Prüfung
         */
        //Prüfe ob der Termin den Profs der Klausur passt --> Nein --> buche späteren Zeitpunkt
        if (!checkProfForEinsortieren(klausur, startZeitTimeSlot, dauerTimeSlot, startTag)){
            startZeitTimeSlot++;
            continue;
        }
        //Prüfe ob der Termin den Studenten der Klausur passt --> Nein --> nehme späteren Zeitpunkt
        if (!checkStudentForEinsortieren(klausur, startZeitTimeSlot, dauerTimeSlot, startTag)){
            startZeitTimeSlot++;
            continue;
        }
        /*______________________________________________________________________________________________________________
         * BUCHUNGSPOZESS
         */
        //TODO für die Zukunft müsste beim buchen eines Raumes der die Kapazitaet der Timeslots der Räume abgezogen werden
        klausur.setTag(startTag);
        klausur.setStartZeitTimeSlot(startZeitTimeSlot);
        while (anzTeilnehmer > 0){
            klausur.addRaumRef(raumIndex);
            tage[startTag].at(raumIndex).useTimeSlots(startZeitTimeSlot,dauerTimeSlot);
            anzTeilnehmer -= tage[startTag].at(raumIndex).getKapazitaet();
            raumIndex++;
        }
        lastSortedDay = startTag;
        return true;
    } //while (true)
}

bool Algorithmus::checkRaeumeByVectorSizeForEinsortieren(Klausur &klausur, int startTag, int raumStartIndex) {
    int tempRaumIndex = raumStartIndex;
    int anzTeilnehmer = klausur.getAnzTeilnehmer();
    while (anzTeilnehmer > 0){
        //Falls das es keine Räume mehr zu dieser Uhrzeit gibt, gehe zum nächsten Tag zur selben Uhrzeit
        if (tempRaumIndex >= data.raeume.size()){
            return false;
        }
        anzTeilnehmer -= tage[startTag].at(tempRaumIndex).getKapazitaet();
        tempRaumIndex++;
    }
    return true;
}


bool Algorithmus::checkRaeumeByKapazitaetForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag, int raumStartIndex) {
    //TODO diese variable ist unnötig, aber es MUSS kopiert werden!
    int tempRaumIndex = raumStartIndex;
    int anzTeilnehmer = klausur.getAnzTeilnehmer();
    while (anzTeilnehmer > 0){
        Raum raum = tage[startTag].at(tempRaumIndex);
        if (!raum.areTimeSlotsFree(startZeitTimeSlot,dauerTimeSlot)){
            return false;
        }
        anzTeilnehmer -= raum.getKapazitaet();
        tempRaumIndex++;
    }
    return true;
}

bool Algorithmus::checkProfForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag) {
    for (int profIndex : klausur.getProfs()) {
        if (!isTimeSlotValidForProf(data.professoren.at(profIndex),startZeitTimeSlot,dauerTimeSlot,startTag)){
            return false;
        }
    }
    return true;
}

bool Algorithmus::checkStudentForEinsortieren(Klausur &klausur, int startZeitTimeSlot, int dauerTimeSlot, int startTag) {
    for (int studentIndex : klausur.getStudenten()) {
        if (!isTimeSlotValidForProf(data.professoren.at(studentIndex),startZeitTimeSlot,dauerTimeSlot,startTag)){
            return false;
        }
    }
    return true;
}



