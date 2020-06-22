//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "ReadInput.h"

#include <utility>

void ReadInput::init() {
    parseInput();
    createProfs();
    createStudents();
    attachStudentsToKlausur();
}

void ReadInput::parseInput() {
    this->rooms = Room::parse("../../input/Raumliste.csv");
    this->registrations = Registration::parse("../../input/Anmeldungen_WS2019_KL.csv");
    this->exams = Exam::parse("../../input/Angebotene_Pruefungen_KL.csv");
}

void ReadInput::createProfs() {
    for (Exam& klausur: exams) {
        if (klausur.getProf1Id() != 0) {
            processProf(klausur.getIndex(), klausur.getProf1Id(), klausur.getProf1Name());
        }
        if (klausur.getProf2Id() != 0) {
            processProf(klausur.getIndex(), klausur.getProf2Id(), klausur.getProf2Name());
        }
    }
    indexProfs();
    cout << profs.size() << "\tprofs created" << endl;
}

void ReadInput::indexProfs() {
    int index = 0;
    for (Professor &prof: profs) {
        prof.setIndex(index);
        index++;
    }
}

void ReadInput::processProf(int examIndex, int id, const string &name) {
    int index = isProfInVector(id);
    if (index >= 0) {
        profs.at(index).addKlausur(examIndex);
        exams.at(examIndex).addProf(index);
    } else {
        Professor p(id, name);
        p.addKlausur(examIndex);
        profs.push_back(p);
        exams.at(examIndex).addProf(profs.size() - 1);
    }
}
int ReadInput::isProfInVector(int identNr) {
    int index = -1;
    for (int i = 0; i < profs.size(); ++i) {
        if(profs.at(i).getIdentNr() == identNr) {
            index = i;
            break;
        }
    }
    return index;
}

void ReadInput::createStudents() {
    int countMissingSignings = 0;
    int studentCount = 0;
    for (Registration& registration: registrations) {
        int index = isStudentInVector(registration.getMatrikelNr());
        int examIndex = findExamIndex(registration.getCourse(), registration.getExamVersionNr(),
                                      registration.getExamNr());
        if (examIndex < 0){
            countMissingSignings++;
            continue;
        }
        if (index >= 0) {
            students.at(index).addKlausur(examIndex);
        } else {
            Student s = Student(registration.getMatrikelNr(), registration.getCourse());
            s.addKlausur(examIndex);
            s.setIndex(studentCount);
            students.push_back(s);
            studentCount++;
        }
    }
    cout << countMissingSignings << "\tregistrations matched no exam" << endl;
    cout << students.size() << "\tstudents created" << endl;
}

int ReadInput::isStudentInVector(int matrikelNr) {
    int index = -1;
    for (int i = 0; i < students.size(); ++i) {
        if(students.at(i).getMatrikelNr() == matrikelNr) {
            index = i;
            break;
        }
    }
    return index;
}

int ReadInput::findExamIndex(const string& course, int examVersion, int examNr) {
    for (Exam& klausur: exams) {
        if (course != klausur.getCourse()) continue;
        if (examVersion != klausur.getVersion()) continue;
        if (examNr != klausur.getId()) continue;
        return klausur.getIndex();
    }
    return -1;
}

void ReadInput::attachStudentsToKlausur() {
    for (const Student& student: students) {
        for (int klausurIndex: student.getKlausurDataIndizes()) {
            exams.at(klausurIndex).addStudent(student.getDataIndex());
        }
    }
    cout << ">>attached students to exams" << endl;
}