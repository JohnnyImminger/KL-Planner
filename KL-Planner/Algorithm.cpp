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
    vector<int> exams = sortExamsBySize();
    cout << ">>sorted exams by size" << endl;
    int nextExamIndex = selectNextExam(exams);
    while (nextExamIndex != -1) {
        if (scheduleExam(data.exams.at(nextExamIndex))) {
        } else {
            cout << "Exception: exam could not be scheduled: " << data.exams.at(nextExamIndex) << endl;
        }
        nextExamIndex = selectNextExam(exams);
    }
}

void Algorithm::printResultByExams(const string &filename) {
    ofstream file;
    file.open(filename);
    for (auto& cExam : data.exams) {
        if(cExam.getMemberCount() == 0) continue;

        file << cExam << ';';

        vector<int> examRooms = cExam.getRoomIndices();
        for (int j: examRooms) {
            Room cRaum = data.rooms.at(j);
            file << cRaum.getAdrBau() << '/';
            file << cRaum.getAdrRaum() << ';';
        }

        file << cExam.getDay() << ';';
        file << (float) cExam.getStartTimeSlot() / Utility::timeSlotsPerHour + Utility::startTimePerDay << endl;
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
        for(int i : cStudent.getExamDataIndizes()){
            file << "schreibt;" << data.exams[i].getName() << ";am;" << data.exams[i].getDay() << ";um;" << data.exams[i].getStartTimeSlot() << endl;
        }
    }
    file.close();
}

/*_____________________________________
* Methoden:
*/


int Algorithm::selectNextExam(vector<int> &indices) {
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

vector<int> Algorithm::sortExamsBySize() {
    vector<int> result;
    for (Exam& exam: data.exams) {
        result.push_back(exam.getIndex());
    }
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < result.size()-1; ++i) {
            Exam e1 = data.exams.at(result.at(i));
            Exam e2 = data.exams.at(result.at(i + 1));
            if (e1.getMemberCount() < e2.getMemberCount()) {
                int temp = (int) e1.getIndex();
                result.at(i) = (int) e2.getIndex();
                result.at(i+1) = temp;
                swapped = true;
            } else if (e1.getMemberCount() == e2.getMemberCount()
                && e1.getDurationTimeSlots() < e2.getDurationTimeSlots()) {
                int temp = (int) e1.getIndex();
                result.at(i) = (int) e2.getIndex();
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

bool Algorithm::scheduleExam(Exam& exam) {
    if (scheduleExamIntoSingleUsedRoom(exam)){
        return true;
    }
    //erst die frühen uhrzeiten
    for (int start = 0; start < Utility::timeSlotsPerDay - exam.getDurationTimeSlots(); start++) {
        //für jeden tag versuchen
        for (int day = 0; day<Utility::examinationPeriod; day++) {
            //wenn nicht alle teilnehmer zu dem Zeitpunkt können, weiterversuchen
            if(!areAllMemberAvailable(exam, day, start)) continue;
            vector<int> roomIndices = getRoomIndicesForExam(exam, day, start);
            //wenn keine räume verfügbar, weiterversuchen
            if(roomIndices.empty()) continue;
            return bookExam(exam, day, start, roomIndices);
        }
    }
    return false;
}

bool Algorithm::scheduleExamIntoSingleUsedRoom(Exam &exam) {
    int dispersion = 0;
    vector <int> possibleRaumIndizes;

    while (dispersion < exam.getMemberCount()){
        for (int day = 0; day < Utility::examinationPeriod; ++day) {
            possibleRaumIndizes = findAvailableUsedRoomAtDay(exam.getMemberCount(), dispersion, exam.getDurationTimeSlots(), day);
            for (int raumIndex : possibleRaumIndizes) {
                for (int startTime : getFillableStartTimesFromUsedRoom(raumIndex, day)) {
                    if (days[day].at(raumIndex).getFreeSpaceAt(startTime, exam.getDurationTimeSlots()) >= exam.getMemberCount() && areAllMemberAvailable(exam, day, startTime)){
                        vector<int> roomIndices;
                        roomIndices.push_back(raumIndex);
                        return bookExam(exam, day, startTime, roomIndices);
                    }
                }
            }
        }
        dispersion++;
    }
    return false;
}

vector<int> Algorithm::findAvailableUsedRoomAtDay(int examSize, int dispersion, int duration, int day) {
    vector <int> possibleRoomIndices;
    for (int roomIndex = 0; roomIndex < days[day].size(); ++roomIndex) {
     Room &room = days[day].at(roomIndex);
        for (int startTime = 0; startTime < Utility::timeSlotsPerDay; ++startTime) {
            if (isRoomUsedAndAvailable(days[day].at(roomIndex),examSize, dispersion, startTime, duration)){
                possibleRoomIndices.push_back(roomIndex);
                break;
            }
        }
    }
    return possibleRoomIndices;
}

bool Algorithm::isRoomUsedAndAvailable(Room &room, int examSize, int dispersion, int startTime, int duration) {
    int space = room.getFreeSpaceAt(startTime,duration);
    if (examSize > space){
        return false;
    }
    if (examSize + dispersion == space){
        //condition for room to be used
        return 0 < space && space < room.getCapacity();
    }
    return false;
}

vector<int> Algorithm::getFillableStartTimesFromUsedRoom(int raumIndex, int day) {
    vector<int> startTimeSlotsToFill;
    Room& room = days[day].at(raumIndex);
    for (int time = 0; time < Utility::timeSlotsPerDay; ++time) {
        int spaceInRoom = days[day].at(raumIndex).getFreeSpaceAt(time,1);
        if ( 0 < spaceInRoom && spaceInRoom < days[day].at(raumIndex).getCapacity()){
            if (time == 0){
                startTimeSlotsToFill.push_back(time);
                continue;
            }
            if (days[day].at(raumIndex).getFreeSpaceAt(time-1,1) == 0){
                startTimeSlotsToFill.push_back(time);
            }
        }
    }
    return startTimeSlotsToFill;
}


vector<int> Algorithm::getRoomIndicesForExam(Exam &exam, int day, int start) {
    vector<int> indicesForExam;
    vector<int> selectableRoomIndices = getSelectableRoomIndices(exam, day, start);
    if(selectableRoomIndices.empty()) return indicesForExam;

    //if all selectable rooms together are smaller than the exam return no rooms
    int sumOfCapacity = 0;
    for (int roomIndex: selectableRoomIndices) {
        sumOfCapacity+=data.rooms.at(roomIndex).getCapacity();
    }
    if(sumOfCapacity < exam.getMemberCount()) return vector<int>();

    sortRoomIndicesBySize(selectableRoomIndices);

    //optimization of slecting rooms is possible here
    //always the biggest room is selected
    int examSize = exam.getMemberCount();
    for (int& selectableRoomIndex : selectableRoomIndices) {
        int roomCapacity = data.rooms.at(selectableRoomIndex).getCapacity();
        indicesForExam.push_back(selectableRoomIndex);
        examSize-=roomCapacity;
        if(examSize <= 0) break;
    }

    return indicesForExam;
}

vector<int> Algorithm::getSelectableRoomIndices(Exam& exam, int day, int start) {
    vector<int> roomIndices;
    for (int rIndex = 0; rIndex < days[day].size(); rIndex++) {
        Room& room = days[day].at(rIndex);
        if(room.isEmpty(start, exam.getDurationTimeSlots())) {
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

bool Algorithm::bookExam(Exam &exam, int day, int start, vector<int>& roomIndices) {
    exam.setDay(day);
    exam.setStartTimeSlot(start);
    int sumOfRoomSize = 0;
    for(int index: roomIndices) {
        exam.addRoom(index);
        int capacity = index != roomIndices.back() ? data.rooms.at(index).getCapacity() : exam.getMemberCount() - sumOfRoomSize;
        if(! days[day].at(index).bookTimeSlots(start, exam.getDurationTimeSlots(), capacity)) return false;
        sumOfRoomSize+=data.rooms.at(index).getCapacity();
    }
    return true;
}

/*
* Teilnehmer Bedingungen
*/

bool Algorithm::areAllMemberAvailable(Exam &exam, int day, int start) {
    return areAllProfsOfExamAvailable(exam, day, start) && areAllStudentsOfExamAvailable(exam, day, start);
}

bool Algorithm::areAllProfsOfExamAvailable(Exam &exam, int day, int start) {
    for (int profIndex : exam.getProfs()) {
        if (!isProfAvailable(data.profs.at(profIndex), day, start, exam.getDurationTimeSlots())){
            return false;
        }
    }
    return true;
}

bool Algorithm::areAllStudentsOfExamAvailable(Exam &exam, int day, int start) {
    for (int studentIndex : exam.getStudents()) {
        if (!isStudentAvailable(data.students.at(studentIndex), day, start, exam.getDurationTimeSlots())){
            return false;
        }
    }
    return true;
}

bool Algorithm::isProfAvailable(Professor& prof, int day, int start, int duration) {
    for (int examIndex : prof.getExamIndices()) {
        Exam exam = data.exams[examIndex];
        if (!exam.isScheduled()){
            continue;
        }
        if (exam.getDay() == day) {
            if (isTimeOverlapping(start, start + duration, exam.getStartTimeSlot(),
                    exam.getStartTimeSlot() + exam.getDurationTimeSlots(), Utility::timeSlotsProfBreak)){
                return false;
            }
        }
    }
    return true;
}

bool Algorithm::isStudentAvailable(Student& student, int day, int start, int duration) {
    int examPerDay = 0;
    for (int examIndex : student.getExamDataIndizes()) {
        Exam exam = data.exams[examIndex];
        if (!exam.isScheduled()){
            continue;
        }
        if (exam.getDay() == day) {
            examPerDay++;
            if (examPerDay >= Utility::maxExamsPerDayStudent){
                return false;
            }
            if (isTimeOverlapping(start, start + duration, exam.getStartTimeSlot(),
                    exam.getStartTimeSlot() + exam.getDurationTimeSlots(), Utility::timeSlotsStudentBreak)){
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
