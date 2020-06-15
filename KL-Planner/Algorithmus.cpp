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
        if (scheduleKlausur(data.klausuren.at(nextKlausurIndex))) {
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
        if(cKlausur.getAnzTeilnehmer() == 0) continue;

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

bool Algorithmus::scheduleKlausur(Klausur& klausur) {
    for (int start = 0; start < Utility::timeSlotsProTag-klausur.getDauerTimeSlots(); start++) {
        for (int day = 0; day<Utility::klausurTage; day++) {
            if(!areAllMemberAvailable(klausur, start, klausur.getDauerTimeSlots(), day)) continue;
            vector<int> roomIndices = getRoomIndicesForKlausur(klausur, day, start);
            if(roomIndices.empty()) continue;
            return bookKlausur(klausur, day, start, roomIndices);
        }
    }
    return false;
}

vector<int> Algorithmus::getRoomIndicesForKlausur(Klausur &klausur, int day, int start) {
    vector<int> indicesForKlausur;
    vector<int> selectableRoomIndices = getSelectableRoomIndices(klausur, day, start);
    if(selectableRoomIndices.empty()) return indicesForKlausur;

    sortRoomIndicesBySize(selectableRoomIndices);

    //TODO: optimierung bei der raumauswahl
    int klSize = klausur.getAnzTeilnehmer();
    for (int i = 0; i < selectableRoomIndices.size(); i++) {
        int roomCap = data.raeume.at(selectableRoomIndices.at(i)).getCapacity();
        indicesForKlausur.push_back(selectableRoomIndices.at(i));
        klSize-=roomCap;
        if(klSize<=0) break;
    }

    return indicesForKlausur;
}

vector<int> Algorithmus::getSelectableRoomIndices(Klausur& kl, int day, int start) {
    vector<int> roomIndices;
    for (int rIndex = 0; rIndex<tage[day].size(); rIndex++) {
        Raum* room = &tage[day].at(rIndex);
        if(room->isEmpty(start, kl.getDauerTimeSlots())) {
            roomIndices.push_back(rIndex);
        }
    }
    return roomIndices;
}

void Algorithmus::sortRoomIndicesBySize(vector<int>& indices) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < indices.size()-1; ++i) {
            Raum r1 = data.raeume.at(indices.at(i));
            Raum r2 = data.raeume.at(indices.at(i+1));
            if (r1.getCapacity() < r2.getCapacity()) {
                int temp = (int) indices.at(i);
                indices.at(i) = (int) indices.at(i+1);
                indices.at(i+1) = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

/*
 * Klausur bei passendem Termin buchen
 */

bool Algorithmus::bookKlausur(Klausur &klausur, int day, int start, vector<int>& roomIndices) {
    klausur.setDay(day);
    klausur.setStartZeitTimeSlot(start);
    int sumOfRoomSize = 0;
    for(int index: roomIndices) {
        klausur.addRaumRef(index);
        if(! tage[day].at(index).bookTimeSlots(start, klausur.getDauerTimeSlots(), index != roomIndices.back() ? data.raeume.at(index).getCapacity() : klausur.getAnzTeilnehmer()-sumOfRoomSize)) return false;
        sumOfRoomSize+=data.raeume.at(index).getCapacity();
    }
    return true;
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
