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

void Algorithmus::initTage() {
    for (auto & tag : tage) {
        tag = data.raeume;
    }
}

void Algorithmus::run() {
    map<string, vector<int>> klausuren = klausurenGroupByStudiengang();
    sortMap(klausuren);
    cout << "Klausuren nach Anzahl der Teilnehmer sortiert" << endl;
    string nextStg = "AB";
    int nextKlausurIndex = selectNextKlausur(klausuren, nextStg);
    while (nextKlausurIndex != -1) {
        if (findDateAndBookKlausur(data.klausuren.at(nextKlausurIndex))) {
        } else {
            cout << "Klausur konnte nicht eingeplant werden: " << data.klausuren.at(nextKlausurIndex) << endl;
        }
        nextKlausurIndex = selectNextKlausur(klausuren, nextStg);
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
    file.close();
}

void Algorithmus::printRaumplanliste(const string &filename) {
    ofstream file;
    file.open(filename);
    for (int i = 0; i < Utility::klausurTage; i++) {
        file << "day " << i+1 << endl;
        vector cRaume = tage[i];
        for(Raum cRaum : cRaume){
            file << cRaum.getAdrBau() << '/' << cRaum.getAdrRaum() << ';';
            cRaum.printFreeTimeslots(file);
            file << endl;
        }
    }
    file.close();
}

void Algorithmus::printProfpalnliste(const string &filename) {
    ofstream file;
    file.open(filename);
    for(Professor cProf : data.professoren){
        file << "Prof_" << cProf.getIdentNr() << endl;
        for(int i = 0; i < cProf.getKlausurDataIndizes().size(); i++){
            file << "beaufsichtigt;" << data.klausuren[cProf.getKlausurDataIndizes()[i]].getName() << ";am;" << data.klausuren[cProf.getKlausurDataIndizes()[i]].getTag() << ";um;" << data.klausuren[cProf.getKlausurDataIndizes()[i]].getStartZeitTimeSlot() << endl;
        }
    }
    file.close();
}

void Algorithmus::printStudentplanliste(const string &filename) {
    ofstream file;
    file.open(filename);
    for(Student cStudent : data.studenten){
        file << "Student_" << cStudent.getMatrikelNr() << endl;
        for(int i = 0;i < cStudent.getKlausurDataIndizes().size(); i++){
            file << "schreibt;" << data.klausuren[cStudent.getKlausurDataIndizes()[i]].getName() << ";am;" << data.klausuren[cStudent.getKlausurDataIndizes()[i]].getTag() << ";um;" << data.klausuren[cStudent.getKlausurDataIndizes()[i]].getStartZeitTimeSlot() << endl;
        }
    }
    file.close();
}

/*_____________________________________
* Methoden:
*/

/*
 * gruppieren der Klausuren nach studStudiengang
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


int Algorithmus::selectNextKlausur(map<string, vector<int>> &map, string &nextStg) {
    // wenn die Map leer ist, soll -1 zurückgegeben werden
    while (!map.empty()) {
        // zwischenspeichern des Index der nächsten klausur und entfernen dieser aus dem vektor der map
        int nextKlausurIndex = map.at(nextStg).at(0);
        map.at(nextStg).erase(map.at(nextStg).cbegin());
        //zwischenspeichern des jetzt "verbrauchten studiengangs" um zugriffsfehler zu vermeiden, löschen falls leer erst später
        string last = nextStg;
        /*
         * durchsucht die map nach dem studiengangname und schreibt dann den nächsten in nextStg für den nächsten Funktionsaufruf
         * ist das ende der map erreicht wird der erste eintrag der Map verwendet
         */
        bool next = false;
        for (const auto &studiengang: map) {
            if (next) {
                nextStg = studiengang.first;
                next = false;
                break;
            }
            if (studiengang.first == nextStg) next = true;
        }
        if (next) nextStg = map.begin()->first;
        //entfernen des studiengangs falls er keine einzuplanende klausuren mehr enthält
        if (map.at(last).empty())map.erase(last);
        //sortiert klausuren ohne teilnehmer aus
        if(data.klausuren.at(nextKlausurIndex).getAnzTeilnehmer() == 0) {
            data.klausuren.at(nextKlausurIndex).setPlanbar(false);
            continue;
        }
        data.klausuren.at(nextKlausurIndex).setPlanbar(true);
        return nextKlausurIndex;
    }
    return -1;
}

void Algorithmus::sortMap(const map<string, vector<int>>& map) {
    for (const auto& studiengang: map) {
        auto* current = (vector<int>*) &studiengang.second;
        int x = 1;
        bool swapped;
        do {
            swapped = false;
            for (int i = 0; i < current->size()-1; ++i) {
                if (data.klausuren.at(current->at(i)).getAnzTeilnehmer() < data.klausuren.at(current->at(i+1)).getAnzTeilnehmer()) {
                    int temp = (int) current->at(i);
                    current->at(i) = (int) current->at(i+1);
                    current->at(i+1) = temp;
                    swapped = true;
                }
            }
        } while (swapped);
    }
}

map<string, vector<int>> Algorithmus::klausurenGroupByStudiengang() {
    map<string,vector<int>> result;
    for(Klausur klausur : data.klausuren){
        if(result.find(klausur.getStudiengang()) == result.end()) { // if-Bedingung für standards vor c++20, da contains erst seit version 20 enthalten ist
        //if(!result.contains(klausur.getStudiengang())) {
            vector<int> neuerStudiengang;
            neuerStudiengang.push_back(klausur.getDataIndex());
            result.insert(pair<string, vector<int>>(klausur.getStudiengang(), neuerStudiengang));
        } else {
            result.find(klausur.getStudiengang())->second.push_back(klausur.getDataIndex());
        }
    }
    return result;
}


/*______________________________________________________________________________________________________________________
 * Klausur einsortieren und buchen
 */


bool Algorithmus::findDateAndBookKlausur(Klausur &klausur) {
    int raumIndex = 0;
    int startTime = 0;
    int startDay = lastSortedDay;
    int klausurDuration = klausur.getDauerTimeSlots();
    int notBookedMember = klausur.getAnzTeilnehmer();

    /*__________________________________________________________________________________________________________________
     * Vorgeschaltete Methode um so wenig capacity wie möchglich zu verschwenden
     */

    //TODO neugestaltung der ganzen Methode mit den neuen Funktionen

    return findDateAndBookKlausurIntoSingleRoom(klausur);
}




bool Algorithmus::findDateAndBookKlausurIntoSingleRoom(Klausur &klausur) {
    int abweichung = 0;
    vector <int> possibleRaumIndizes;
    while (abweichung < klausur.getAnzTeilnehmer()){
        //Suche einen schon genutzen Raum, in den alle Studenten passen
        for (int day = 0; day < Utility::klausurTage; ++day) {
            possibleRaumIndizes = findAvailableUsedRaumAtDay(klausur.getAnzTeilnehmer(), abweichung, abweichung, klausur.getDauerTimeSlots(), day);
            for (int raumIndex : possibleRaumIndizes) {
                for (int startTime : getFillableStartTimesFromUsedRoom(raumIndex, day)) {
                    if (tage[day].at(raumIndex).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()) >= klausur.getAnzTeilnehmer() && areAllMemberAvailable(klausur, startTime, klausur.getDauerTimeSlots(), day)){
                        return bookKlausurDate(klausur, startTime, day, raumIndex, klausur.getAnzTeilnehmer());
                    }
                }
            }
        }
        //Suche irgendwann irgendeinen Raum in den alle Studenten aufeinmal passen
        for (int day = 0; day < Utility::klausurTage; ++day) {
            possibleRaumIndizes = findAvailableRaumAtDay(klausur.getAnzTeilnehmer(), abweichung, abweichung, klausur.getDauerTimeSlots(), day);
            for (int raumIndex : possibleRaumIndizes) {
                for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
                    if (tage[day].at(raumIndex).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()) >= klausur.getAnzTeilnehmer() && areAllMemberAvailable(klausur, startTime, klausur.getDauerTimeSlots(), day)){
                        return bookKlausurDate(klausur, startTime, day, raumIndex, klausur.getAnzTeilnehmer());
                    }
                }
            }
        }
        abweichung++;
    }
    return false;
}

/*
 * Suche passende Räume nach verschiedenen Prioritäten
 */

vector<int> Algorithmus::getFillableStartTimesFromUsedRoom(int raumIndex, int day) {
    vector<int> startTimeSlotsToFill;
    Raum& raum = tage [day].at(raumIndex);
    for (int time = 0; time < Utility::timeSlotsProTag; ++time) {
        int spaceInRoom = tage[day].at(raumIndex).getFreeSpaceAt(time,1);
        if ( 0 < spaceInRoom && spaceInRoom < tage[day].at(raumIndex).getCapacity()){
            if (time == 0){
                startTimeSlotsToFill.push_back(time);
                continue;
            }
            if (tage[day].at(raumIndex).getFreeSpaceAt(time-1,1) == 0){
                startTimeSlotsToFill.push_back(time);
            }
        }
    }
    return startTimeSlotsToFill;
}

/*
 * Find
 */

vector <int> Algorithmus::findAvailableRaumForCapacity(int klausurSize, int minAbweichung, int maxAbweichung, int duration){
    vector<int> raumIndizes;
    for (int raumIndex = 0; raumIndex < data.raeume.size(); ++raumIndex) {
        bool bookable = false;
        for (int day = 0; day < Utility::klausurTage; ++day) {
            for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
                if (isCapacityInRange(tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration), klausurSize, minAbweichung,maxAbweichung)){
                    bookable = true;
                    raumIndizes.push_back(raumIndex);
                    break;
                }
            }
            if (bookable){
                break;
            }
        }
    }
    return raumIndizes;
}

vector<int> Algorithmus::findAvailableRaumAtDay(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day) {
    vector<int> raumIndizes;
    for (int raumIndex = 0; raumIndex < tage[day].size(); ++raumIndex) {
        for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
            if (isCapacityInRange(tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration), klausurSize, minAbweichung, maxAbweichung)){
                raumIndizes.push_back(raumIndex);
                break;
            }
        }

    }
    return raumIndizes;
}

vector<int> Algorithmus::findAvailableRaumAtDayAndTime(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day, int startTime) {
    vector<int> raumIndizes;
    for (int raumIndex = 0; raumIndex < tage[day].size(); ++raumIndex) {
        if (isCapacityInRange(tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration), klausurSize, minAbweichung, maxAbweichung)){
            raumIndizes.push_back(raumIndex);
        }
    }
    return raumIndizes;
}
/*
 * Used
 */

vector<int> Algorithmus::findAvailableUsedRaumForCapacity(int klausurSize, int minAbweichung, int maxAbweichung, int duration) {
    vector <int> possibleRaumIndizes = findAvailableRaumForCapacity(klausurSize,minAbweichung,maxAbweichung,duration);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        bool bookable = false;
        for (int day = 0; day < Utility::klausurTage; ++day) {
            for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
                if (tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration) < tage[day].at(raumIndex).getCapacity()){
                    bookable = true;
                    raumIndizes.push_back(raumIndex);
                    break;
                }
            }
            if (bookable){
                break;
            }
        }
    }
    return raumIndizes;

}

vector<int> Algorithmus::findAvailableUsedRaumAtDay(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day) {
    vector <int> possibleRaumIndizes = findAvailableRaumForCapacity(klausurSize,minAbweichung,maxAbweichung,duration);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
            if (tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration) < tage[day].at(raumIndex).getCapacity()){
                raumIndizes.push_back(raumIndex);
                break;
            }
        }
    }
    return raumIndizes;
}

vector<int> Algorithmus::findAvailableUsedRaumAtDayAndTime(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day, int startTime) {
    vector <int> possibleRaumIndizes = findAvailableRaumForCapacity(klausurSize,minAbweichung,maxAbweichung,duration);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        if (tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration) < tage[day].at(raumIndex).getCapacity()){
            raumIndizes.push_back(raumIndex);
        }
    }
    return raumIndizes;
}

/*
 * Utility
 */

bool Algorithmus::isCapacityInRange(int freeRoomCapacity, int klausurSize, int minAbweichung, int maxAbweichung) {
    if (freeRoomCapacity < klausurSize) {
        return false;
    }
    //klausurSize - maxAbweichung <= freeRoomCapacity <= klausurSize - minAbweichung
    bool condition1 = klausurSize - maxAbweichung <= freeRoomCapacity && freeRoomCapacity <= klausurSize - minAbweichung;
    //klausurSize + minAbweichung <= freeRoomCapacity <= klausurSize + maxAbweichung
    bool condition2 = klausurSize + minAbweichung <= freeRoomCapacity && freeRoomCapacity <= klausurSize + maxAbweichung;

    return condition1 || condition2;
}

/*
 * Klausur bei passendem Termin buchen
 */

bool Algorithmus::bookKlausurDate(Klausur &klausur, int startTime, int day, int raumDataIndex, int bookedCapacity) {
    klausur.setTag(day);
    klausur.setStartZeitTimeSlot(startTime);
    klausur.addRaumRef(raumDataIndex);
    return tage[day].at(raumDataIndex).bookTimeSlots(startTime, klausur.getDauerTimeSlots(),bookedCapacity);

}

/*
* Teilnehmer Bedingungen
*/

bool Algorithmus::areAllMemberAvailable(Klausur &klausur, int startTime, int duration, int day) {
    return areAllProfsOfKlausurAvailable(klausur, startTime,duration,day) && areAllStudentsOfKlausurAvailable(klausur,startTime,duration,day);
}

bool Algorithmus::areAllProfsOfKlausurAvailable(Klausur &klausur, int startTime, int duration, int day) {
    for (int profIndex : klausur.getProfs()) {
        if (!isProfAvailable(data.professoren.at(profIndex), startTime, duration, day)){
            return false;
        }
    }
    return true;
}

bool Algorithmus::areAllStudentsOfKlausurAvailable(Klausur &klausur, int startTime, int duration, int day) {
    for (int studentIndex : klausur.getStudenten()) {
        if (!isStudentAvailable(data.studenten.at(studentIndex), startTime, duration, day)){
            return false;
        }
    }
    return true;
}

bool Algorithmus::isProfAvailable(Professor& prof, int askedStartTime, int askedDuration, int day) {
    for (int klausurIndex : prof.getKlausurDataIndizes()) {
        Klausur klausur = data.klausuren[klausurIndex];
        if (!klausur.isEingeplant()){
            continue;
        }
        if (klausur.getTag() == day) {
            if (isTimeOverlapping(askedStartTime, askedStartTime + askedDuration, klausur.getStartZeitTimeSlot(), klausur.getStartZeitTimeSlot() + klausur.getDauerTimeSlots(), Utility::timeSlotsPauseProf)){
                return false;
            }
        }
    }
    return true;
}

bool Algorithmus::isStudentAvailable(Student& student, int askedStartTime, int askedDuration, int day) {
    int klausurPerDay = 0;
    for (int klausurIndex : student.getKlausurDataIndizes()) {
        Klausur klausur = data.klausuren[klausurIndex];
        if (!klausur.isEingeplant()){
            continue;
        }
        if (klausur.getTag() == day) {
            klausurPerDay++;
            if (klausurPerDay >= Utility::maxKlausurenProTagStudent){
                return false;
            }
            if (isTimeOverlapping(askedStartTime, askedStartTime + askedDuration, klausur.getStartZeitTimeSlot(), klausur.getStartZeitTimeSlot() + klausur.getDauerTimeSlots(), Utility::timeSlotsPauseStudent)){
                return false;
            }
        }
    }
    return true;
}

bool Algorithmus::isTimeOverlapping(int askedStartTime, int askedEndTime, int busyStartTime, int busyEndTime, int personalBreak) {
    //busyStartTime <= askedStarttime < busyEndTime + Break --> neue Klausur würde in der alten Starten
    bool condition1 = busyStartTime <= askedStartTime && askedStartTime < busyEndTime + personalBreak;
    //busyStartTime <= askedEndTime < busyEndTime+Pause --> Endzeit schneidet vorhandene Klausur
    bool condition2 = busyStartTime <= askedEndTime && askedEndTime < busyEndTime + personalBreak;
    //askedStartTime <= busyStartTime <= busyEndTime <= askedEndTim --> neue Klausur würde vorhandene Klausur überdecken
    bool condition3 = askedStartTime <= busyStartTime && busyEndTime <= askedEndTime;
    return condition1 || condition2 || condition3;
}

/*
 * Array Bedingungen
 */

bool Algorithmus::isTimeArrayLongEnough(int startTime, int duration) {
    if (0 < startTime){
        cout << "Error: Algorithmus::isTimeArrayLongEnough() - Startzeit < 0 !"<< endl;
        return false;
    }
    return startTime + duration <= Utility::timeSlotsProTag;
}

bool Algorithmus::isRaumArrayLongEnough( int raumIndex) {
    if (0 < raumIndex){
        cout << "Error: Algorithmus::isRaumArrayLongEnough() - RaumIndex < 0 !"<< endl;
        return false;
    }
    return raumIndex <= data.raeume.size();
}

int Algorithmus::increaseStartTag(int startTag) {
    startTag++;
    if (startTag == Utility::klausurTage){
        startTag = 0;
    }
    return startTag;
}


