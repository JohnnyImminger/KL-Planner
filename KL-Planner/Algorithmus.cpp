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
    vector<int> klausuren =  sortKlausurenBySize();
    cout << "Klausuren nach Anzahl der Teilnehmer sortiert" << endl;
    int nextKlausurIndex = selectNextKlausur(klausuren);
    while (nextKlausurIndex != -1) {
        if (findDateAndBookKlausur(data.klausuren.at(nextKlausurIndex))) {
        } else {
            cout << "Klausur konnte nicht eingeplant werden: " << data.klausuren.at(nextKlausurIndex) << endl;
        }
        nextKlausurIndex = selectNextKlausur(klausuren);
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
            cRaum.printTimeSlots(file);
            file << endl;
        }
    }
    file.close();
}

void Algorithmus::printProfpalnliste(const string &filename) {
    ofstream file;
    file.open(filename);
    for(const Professor& cProf : data.professoren){
        file << "Prof_" << cProf.getIdentNr() << endl;
        for(int i : cProf.getKlausurDataIndizes()){
            file << "beaufsichtigt;" << data.klausuren[i].getName() << ";am;" << data.klausuren[i].getTag() << ";um;" << data.klausuren[i].getStartZeitTimeSlot() << endl;
        }
    }
    file.close();
}

void Algorithmus::printStudentplanliste(const string &filename) {
    ofstream file;
    file.open(filename);
    for(const Student& cStudent : data.studenten){
        file << "Student_" << cStudent.getMatrikelNr() << endl;
        for(int i : cStudent.getKlausurDataIndizes()){
            file << "schreibt;" << data.klausuren[i].getName() << ";am;" << data.klausuren[i].getTag() << ";um;" << data.klausuren[i].getStartZeitTimeSlot() << endl;
        }
    }
    file.close();
}

/*_____________________________________
* Methoden:
*/


int Algorithmus::selectNextKlausur(vector<int> &indices) {
    // wenn der vector leer ist, soll -1 zurückgegeben werden
    while (!indices.empty()) {
        int nextIndex = indices.front();
        //wenn die Klausur keine Teilnehmer hat, wird sie ignoriert
        if(data.klausuren.at(nextIndex).getAnzTeilnehmer() == 0) {
            indices.erase(indices.begin());
            continue;
        }
        indices.erase(indices.begin());
        return nextIndex;
    }
    return -1;
}

vector<int> Algorithmus::sortKlausurenBySize() {
    vector<int> result;
    for (Klausur& klausur: data.klausuren) {
        result.push_back(klausur.getDataIndex());
    }
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < result.size()-1; ++i) {
            Klausur k1 = data.klausuren.at(result.at(i));
            Klausur k2 = data.klausuren.at(result.at(i+1));
            if (k1.getAnzTeilnehmer() < k2.getAnzTeilnehmer()) {
                int temp = (int) k1.getDataIndex();
                result.at(i) = (int) k2.getDataIndex();
                result.at(i+1) = temp;
                swapped = true;
            } else if (k1.getAnzTeilnehmer() == k2.getAnzTeilnehmer() && k1.getDauerTimeSlots() < k2.getDauerTimeSlots()) {
                int temp = (int) k1.getDataIndex();
                result.at(i) = (int) k2.getDataIndex();
                result.at(i+1) = temp;
                swapped = true;
            }
        }
    } while (swapped);
    for (int index: result) {
        cout << data.klausuren.at(index).getAnzTeilnehmer() << ' ' << data.klausuren.at(index).getDauerTimeSlots() << endl;
    }
    return result;
}

/*______________________________________________________________________________________________________________________
 * Klausur einsortieren und buchen
 */


bool Algorithmus::findDateAndBookKlausur(Klausur &klausur) {
    if (findDateAndBookKlausurIntoSingleRoom(klausur)){
        return true;
    }
    //TODO finde größten freien Raum, buche restTeilnehmer in möglichst wenig räume rekursiv

    /*__________________________________________________________________________________________________________________
     * Vorgeschaltete Methode um so wenig capacity wie möchglich zu verschwenden
     */

    //TODO neugestaltung der ganzen Methode mit den neuen Funktionen

    return false;
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



bool Algorithmus::findAndBookKlausurIntoDayAndTime(Klausur &klausur, int restAnzTeilnehmer, int day, int startTime) {
    int abweichung = 0;
    vector <int> possibleRaumIndizes;
    while (abweichung < restAnzTeilnehmer){
        //Versuchen aufzufüllen
        possibleRaumIndizes = findAvailableUsedRaumAtDayAndTime(restAnzTeilnehmer,abweichung, abweichung, klausur.getDauerTimeSlots(), day, startTime);
        for (int raumIndex : possibleRaumIndizes) {

        }



        abweichung++;
    }

}

/*
 * Suche passende Räume nach verschiedenen Prioritäten
 */
vector<int> Algorithmus::findShortestAvailableRaumIndezesVector(Klausur &klausur, int day, int startTime) {
    return vector<int>();
}


vector<int> Algorithmus::findAvailableRaumIndizes(Klausur &klausur, int day, int startTime) {


}

int Algorithmus::findBiggestAvailableRaumIndex(int day, int startTime, int duration) {
    int maxRaumSize = 0;
    int maxRaumIndex = -1;
    for (int raumIndex : findAvailableRaumAtDayAndTime(200, 0, 200, duration, day, startTime)) {
        int raumSize = tage[day].at(raumIndex).getFreeSpaceAt(startTime, duration);
        if (raumIndex > maxRaumSize){
            maxRaumIndex = raumIndex;
            maxRaumSize = raumSize;
        }
    }
    return maxRaumIndex;
}

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

vector<int> Algorithmus::findAvailableUsedRaum(int klausurSize, int minAbweichung, int maxAbweichung, int duration) {
    vector <int> possibleRaumIndizes = findAvailableRaumForCapacity(klausurSize,minAbweichung,maxAbweichung,duration);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        bool bookable = false;
        for (int day = 0; day < Utility::klausurTage; ++day) {
            for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
                if (isRaumUsedAndAvailable(tage[day].at(raumIndex), startTime, duration)){
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
    vector <int> possibleRaumIndizes = findAvailableUsedRaum(klausurSize, minAbweichung, maxAbweichung, duration);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
            if (isRaumUsedAndAvailable(tage[day].at(raumIndex), startTime, duration)){
                raumIndizes.push_back(raumIndex);
                break;
            }
        }
    }
    return raumIndizes;
}

vector<int> Algorithmus::findAvailableUsedRaumAtDayAndTime(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day, int startTime) {
    vector <int> possibleRaumIndizes = findAvailableUsedRaumAtDay(klausurSize,minAbweichung,maxAbweichung,duration,day);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        if (isRaumUsedAndAvailable(tage[day].at(raumIndex), startTime, duration)){
            raumIndizes.push_back(raumIndex);
        }
    }
    return raumIndizes;
}

bool Algorithmus::isRaumUsedAndAvailable(Raum &raum, int startTime, int duration) {
    return raum.getFreeSpaceAt(startTime,duration) < raum.getCapacity();
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
