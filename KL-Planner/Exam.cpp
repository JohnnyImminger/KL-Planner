//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Exam.h"
#include "Utility.h"

/*
 * Konstruktoren
 */

Exam::Exam() {
    this->index = -1;
    this->course = "DummyExam";
    this->vertiefung = "DummyExam";
    this->version = 404;
    this->id = 404;
    this->name = "DummyExam";
    this->prof1Id = 404;
    this->prof1Name = "DummyExam";
    this->prof2Id = 404;
    this->prof2Name = "DummyExam";
    this->duration = 0;
    this->durationTimeSlots = 0;
    this->kindOfExam = "DummyExam";
    this->semester = 404;
    this->offered = false;
    this->projectable = false;
    this->scheduled = false;
    this->memberCount = 0;
    this->day = -1;
    this->startTimeSlot = -1;

}

Exam::Exam(string& course, string& vertiefung, int examVersion, int examId, string& examName, int prof1Id,
           string& prof1Name, int prof2Id, string& prof2Name, float duration, string& kindOfExam, int examSemester,
           bool projectable) {
    this->index = -1;
    this->course = course;
    this->vertiefung = vertiefung;
    this->version = examVersion;
    this->id = examId;
    this->name = examName;
    this->prof1Id = prof1Id;
    this->prof1Name = prof1Name;
    this->prof2Id = prof2Id;
    this->prof2Name = prof2Name;
    this->duration = duration;
    this->durationTimeSlots = (int) ((duration / 60) * Utility::timeSlotsPerHour);
    this->kindOfExam = kindOfExam;
    this->semester = examSemester;
    this->offered = projectable;
    this->projectable = false;
    this->scheduled = false;
    this->memberCount = 0;
    this->day = -1;
    this->startTimeSlot = -1;
}
/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Exam &exam) {
    out << exam.getCourse() << ';' << exam.getVertiefung() << ';' << exam.getVersion() << ';' << exam.getId() << ';'
        << exam.getName() << ';' << exam.getProf1Id() << ';' << exam.getProf1Name() << ';' << exam.getProf2Id() << ';'
        << exam.getProf2Name() << ';' << exam.getDurationFloat() << ';' << exam.getKindOfExam() << ';' << exam.getSemester() << ';'
        << exam.isProjectable();
    return out;
}

/*
 * Getter
 */

int Exam::getIndex() {
    return this->index;
}

const string &Exam::getCourse() const {
    return course;
}

const string &Exam::getVertiefung() const {
    return vertiefung;
}

int Exam::getVersion() const {
    return version;
}

int Exam::getId() const {
    return id;
}

const string &Exam::getName() const {
    return name;
}

int Exam::getProf1Id() const {
    return prof1Id;
}

const string &Exam::getProf1Name() const {
    return prof1Name;
}

int Exam::getProf2Id() const {
    return prof2Id;
}

const string &Exam::getProf2Name() const {
    return prof2Name;
}

float Exam::getDurationFloat() const {
    return duration;
}

int Exam::getDurationTimeSlots() const {
    return durationTimeSlots;
}

const string &Exam::getKindOfExam() const {
    return kindOfExam;
}

int Exam::getSemester() const {
    return semester;
}

bool Exam::isProjectable() const {
    return offered;
}

bool Exam::isReadyForScheduling() const {
    return projectable;
}

bool Exam::isScheduled() const {
    return scheduled;
}

vector<int> Exam::getProfs() {
    return profIndices;
}

const vector<int> &Exam::getStudents() const {
    return studentIndices;
}

int Exam::getMemberCount() const {
    return memberCount;
}

vector<int> Exam::getRoomIndices() {
    return roomIndices;
}

int Exam::getDay() const {
    return day;
}

int Exam::getStartTimeSlot() const {
    return startTimeSlot;
}

/*
 * Setter
 */

void Exam::setIndex(int index) {
    Exam::index = index;
}

void Exam::setProjectable(bool projectable) {
    Exam::projectable = projectable;
}

void Exam::setScheduled(bool scheduled) {
    Exam::scheduled = scheduled;
}

void Exam::setDay(int day) {
    Exam::day = day;
}

void Exam::setStartTimeSlot(int startTimeSlot) {
    Exam::startTimeSlot = startTimeSlot;
}

/*______________________________________________________________
 * Methoden:
 */

vector<Exam> Exam::parse(const string& pathToFile) {
    remove("../../output/ignoredExams.csv");
    ifstream input(pathToFile);
    if(!input) {
        cerr << "Error: could not open file " << pathToFile << endl;
    }
    int index = 0;
    size_t lines = 0;
    vector<Exam> list;
    string line;
    getline(input, line);
    while (!input.eof()){
        getline(input, line);
        if(line.empty()) break;
        vector<string> split = Utility::splitString(line, ';');
        if(split[9] == "0" || split[9].empty()) {
            Utility::printIgnoredExam(line);
            continue;
        }
        int pVersion;
        int pNummer;
        int prof1;
        int prof2;
        float pDauer;
        int pSemeser;
        bool angeboten;
        istringstream(split[2]) >> pVersion;
        istringstream(split[3]) >> pNummer;
        istringstream(split[5]) >> prof1;
        istringstream(split[7]) >> prof2;
        istringstream(split[9]) >> pDauer;
        istringstream(split[11]) >> pSemeser;
        angeboten = split[12] == "J";
        Exam a(split[0], split[1], pVersion, pNummer, split[4], prof1, split[6], prof2,
               split[8], pDauer, split[10], pSemeser, angeboten);
        a.setIndex(index);
        list.push_back(a);
        ++lines;
        index++;
    }
    input.close();
    cout << lines << "\tparsed exams" << endl;
    return list;
}

void Exam::addProf(int index) {
    profIndices.push_back(index);
}

void Exam::addStudent(int index) {
    memberCount++;
    studentIndices.push_back(index);
}

void Exam::addRoom(int index) {
    roomIndices.push_back(index);
}

void Exam::removeRoom(int elementToRemove) {
    roomIndices.erase(roomIndices.begin() + index);
}