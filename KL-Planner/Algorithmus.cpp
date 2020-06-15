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
    return result;
}

/*______________________________________________________________________________________________________________________
 * Klausur einsortieren und buchen
 */

bool Algorithmus::klausurEinsortieren(int index) {
    Klausur klausur = data.klausuren.at(index);
    bool booked = false;
    int day = 0;
    while (!booked) {
        vector<int> rooms = roomsAtDay(klausur, day);
        if(rooms.empty()) break;
        for (int room: rooms) {

        }
    }
    return booked;
}

vector<int> Algorithmus::roomsAtDay(Klausur& klausur, int day) {


    return vector<int>();
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