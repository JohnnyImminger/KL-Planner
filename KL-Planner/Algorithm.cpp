//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Algorithm.h"
#include <map>

/*
* Konstruktoren
*/

Algorithm::Algorithm(ReadInput& data) {
    this->data = data;
}

void Algorithm::initTage() {
    for (auto & tag : days) {
        tag = data.rooms;
    }
}

void Algorithm::run() {
    vector<int> klausuren =  sortKlausurenBySize();
    cout << ">>sorted exams by size" << endl;
    int nextKlausurIndex = selectNextKlausur(klausuren);
    while (nextKlausurIndex != -1) {
        if (scheduleKlausur(data.exams.at(nextKlausurIndex))) {
        } else {
            cout << "Exception: exam could not be scheduled: " << data.exams.at(nextKlausurIndex) << endl;
        }
        nextKlausurIndex = selectNextKlausur(klausuren);
    }
}

void Algorithm::printResultByExams(const string &filename) {
    ofstream file;
    file.open(filename);
    for (auto& cKlausur : data.exams) {
        if(cKlausur.getMemberCount() == 0) continue;

        file << cKlausur << ';';

        vector<int> klausurRaeume = cKlausur.getRoomIndices();
        for (int j: klausurRaeume) {
            Room cRaum = data.rooms.at(j);
            file << cRaum.getAdrBau() << '/';
            file << cRaum.getAdrRaum() << ';';
        }

        file << cKlausur.getDay() << ';';
        file << (float) cKlausur.getStartTimeSlot() / Utility::timeSlotsPerHour + Utility::startTimePerDay << endl;
    }
    file.close();
}

void Algorithm::printResultByRooms(const string &filename) {
    ofstream file;
    file.open(filename);
    for (int i = 0; i < Utility::examinationPeriod; i++) {
        file << "day " << i+1 << endl;
        vector<Room> currRooms = days[i];
        for(Room& currRoom : currRooms){
            file << currRoom.getAdrBau() << '/' << currRoom.getAdrRaum() << ';';
            currRoom.printTimeSlots(file);
            file << endl;
        }
    }
    file.close();
}

void Algorithm::printResultByProfs(const string &filename) {
    ofstream file;
    file.open(filename);
    for(const Professor& cProf : data.profs){
        file << "Prof_" << cProf.getIdentNr() << endl;
        for(int i : cProf.getExamIndices()){
            file << "beaufsichtigt;" << data.exams[i].getName() << ";am;" << data.exams[i].getDay() << ";um;" << data.exams[i].getStartTimeSlot() << endl;
        }
    }
    file.close();
}

void Algorithm::printResultByStudent(const string &filename) {
    ofstream file;
    file.open(filename);
    for(const Student& cStudent : data.students){
        file << "Student_" << cStudent.getMatrikelNr() << endl;
        for(int i : cStudent.getKlausurDataIndizes()){
            file << "schreibt;" << data.exams[i].getName() << ";am;" << data.exams[i].getDay() << ";um;" << data.exams[i].getStartTimeSlot() << endl;
        }
    }
    file.close();
}

/*_____________________________________
* Methoden:
*/


int Algorithm::selectNextKlausur(vector<int> &indices) {
    // wenn der vector leer ist, soll -1 zurückgegeben werden
    while (!indices.empty()) {
        int nextIndex = indices.front();
        //wenn die Exam keine Teilnehmer hat, wird sie ignoriert
        if(data.exams.at(nextIndex).getMemberCount() == 0) {
            indices.erase(indices.begin());
            continue;
        }
        indices.erase(indices.begin());
        return nextIndex;
    }
    return -1;
}

vector<int> Algorithm::sortKlausurenBySize() {
    vector<int> result;
    for (Exam& klausur: data.exams) {
        result.push_back(klausur.getIndex());
    }
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < result.size()-1; ++i) {
            Exam k1 = data.exams.at(result.at(i));
            Exam k2 = data.exams.at(result.at(i + 1));
            if (k1.getMemberCount() < k2.getMemberCount()) {
                int temp = (int) k1.getIndex();
                result.at(i) = (int) k2.getIndex();
                result.at(i+1) = temp;
                swapped = true;
            } else if (k1.getMemberCount() == k2.getMemberCount() && k1.getDurationTimeSlots() <
                                                                     k2.getDurationTimeSlots()) {
                int temp = (int) k1.getIndex();
                result.at(i) = (int) k2.getIndex();
                result.at(i+1) = temp;
                swapped = true;
            }
        }
    } while (swapped);
    return result;
}

/*______________________________________________________________________________________________________________________
 * Exam einsortieren und buchen
 */

bool Algorithm::scheduleKlausur(Exam& klausur) {
    for (int start = 0; start < Utility::timeSlotsPerDay - klausur.getDurationTimeSlots(); start++) {
        for (int day = 0; day<Utility::examinationPeriod; day++) {
            if(!areAllMemberAvailable(klausur, day, start)) continue;
            vector<int> roomIndices = getRoomIndicesForKlausur(klausur, day, start);
            if(roomIndices.empty()) continue;
            return bookKlausur(klausur, day, start, roomIndices);
        }
    }
    return false;
}

vector<int> Algorithm::getRoomIndicesForKlausur(Exam &klausur, int day, int start) {
    vector<int> indicesForKlausur;
    vector<int> selectableRoomIndices = getSelectableRoomIndices(klausur, day, start);
    if(selectableRoomIndices.empty()) return indicesForKlausur;

    sortRoomIndicesBySize(selectableRoomIndices);

    //TODO: optimierung bei der raumauswahl
    int klSize = klausur.getMemberCount();
    for (int i = 0; i < selectableRoomIndices.size(); i++) {
        int roomCap = data.rooms.at(selectableRoomIndices.at(i)).getCapacity();
        indicesForKlausur.push_back(selectableRoomIndices.at(i));
        klSize-=roomCap;
        if(klSize<=0) break;
    }

    return indicesForKlausur;
}

vector<int> Algorithm::getSelectableRoomIndices(Exam& kl, int day, int start) {
    vector<int> roomIndices;
    for (int rIndex = 0; rIndex < days[day].size(); rIndex++) {
        Room* room = &days[day].at(rIndex);
        if(room->isEmpty(start, kl.getDurationTimeSlots())) {
            roomIndices.push_back(rIndex);
        }
    }
    return roomIndices;
}

void Algorithm::sortRoomIndicesBySize(vector<int>& indices) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < indices.size()-1; ++i) {
            Room r1 = data.rooms.at(indices.at(i));
            Room r2 = data.rooms.at(indices.at(i + 1));
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
 * Exam bei passendem Termin buchen
 */

bool Algorithm::bookKlausur(Exam &klausur, int day, int start, vector<int>& roomIndices) {
    klausur.setDay(day);
    klausur.setStartTimeSlot(start);
    int sumOfRoomSize = 0;
    for(int index: roomIndices) {
        klausur.addRoom(index);
        if(! days[day].at(index).bookTimeSlots(start, klausur.getDurationTimeSlots(), index != roomIndices.back() ? data.rooms.at(index).getCapacity() :
                                                                                      klausur.getMemberCount() - sumOfRoomSize)) return false;
        sumOfRoomSize+=data.rooms.at(index).getCapacity();
    }
    return true;
}

/*
* Teilnehmer Bedingungen
*/

bool Algorithm::areAllMemberAvailable(Exam &klausur, int day, int start) {
    return areAllProfsOfKlausurAvailable(klausur, day, start) && areAllStudentsOfKlausurAvailable(klausur, day, start);
}

bool Algorithm::areAllProfsOfKlausurAvailable(Exam &klausur, int day, int start) {
    for (int profIndex : klausur.getProfs()) {
        if (!isProfAvailable(data.profs.at(profIndex), day, start, klausur.getDurationTimeSlots())){
            return false;
        }
    }
    return true;
}

bool Algorithm::areAllStudentsOfKlausurAvailable(Exam &klausur, int day, int start) {
    for (int studentIndex : klausur.getStudents()) {
        if (!isStudentAvailable(data.students.at(studentIndex), day, start, klausur.getDurationTimeSlots())){
            return false;
        }
    }
    return true;
}

bool Algorithm::isProfAvailable(Professor& prof, int day, int start, int duration) {
    for (int klausurIndex : prof.getExamIndices()) {
        Exam klausur = data.exams[klausurIndex];
        if (!klausur.isScheduled()){
            continue;
        }
        if (klausur.getDay() == day) {
            if (isTimeOverlapping(start, start + duration, klausur.getStartTimeSlot(), klausur.getStartTimeSlot() +
                                                                                       klausur.getDurationTimeSlots(), Utility::timeSlotsProfBreak)){
                return false;
            }
        }
    }
    return true;
}

bool Algorithm::isStudentAvailable(Student& student, int day, int start, int duration) {
    int klausurPerDay = 0;
    for (int klausurIndex : student.getKlausurDataIndizes()) {
        Exam klausur = data.exams[klausurIndex];
        if (!klausur.isScheduled()){
            continue;
        }
        if (klausur.getDay() == day) {
            klausurPerDay++;
            if (klausurPerDay >= Utility::maxExamsPerDayStudent){
                return false;
            }
            if (isTimeOverlapping(start, start + duration, klausur.getStartTimeSlot(), klausur.getStartTimeSlot() +
                                                                                       klausur.getDurationTimeSlots(), Utility::timeSlotsStudentBreak)){
                return false;
            }
        }
    }
    return true;
}

bool Algorithm::isTimeOverlapping(int start, int end, int busyStart, int busyEnd, int personalBreak) {
    //busyStart <= askedStarttime < busyEnd + Break --> neue Exam würde in der alten Starten
    bool condition1 = busyStart <= start && start < busyEnd + personalBreak;
    //busyStart <= end < busyEnd+Pause --> Endzeit schneidet vorhandene Exam
    bool condition2 = busyStart <= end && end < busyEnd + personalBreak;
    //start <= busyStart <= busyEnd <= askedEndTim --> neue Exam würde vorhandene Exam überdecken
    bool condition3 = start <= busyStart && busyEnd <= end;
    return condition1 || condition2 || condition3;
}
