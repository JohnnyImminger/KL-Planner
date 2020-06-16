//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Registration.h"

/*
 * Konstruktoren
 */

Registration::Registration() {
    this->martrikelNummer = 404;
    this->course = "dummyAnmeldung";
    this->examVersionNr = 404;
    this->examNr = 404;
    this->kindOfExamShort = "dummyAnmeldung";
    this->KindOfExamLong = "dummyAnmeldung";
    this->examSemester = 404;
}

Registration::Registration(int matrikelNr, string &course, int examVersion, int examNr, string &kindOfExam, string &description,
                           int examSemester) {
    this->martrikelNummer = matrikelNr;
    this->course = course;
    this->examVersionNr = examVersion;
    this->examNr = examNr;
    this->kindOfExamShort = kindOfExam;
    this->KindOfExamLong = description;
    this->examSemester = examSemester;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Registration &registration) {
    out << registration.getMatrikelNr() << ';' << registration.getCourse() << ';' << registration.getExamVersionNr() << ';' << registration.getExamNr() << ';' << registration.getKindOfExamShort() << ';' << registration.getKindOfExamLong() << ';' << registration.getExamSemester();
    return out;
}

/*
 * Getter
 */

int Registration::getMatrikelNr() const {
    return martrikelNummer;
}

const string &Registration::getCourse() const {
    return course;
}

int Registration::getExamVersionNr() const {
    return examVersionNr;
}

int Registration::getExamNr() const {
    return examNr;
}

const string &Registration::getKindOfExamShort() const {
    return kindOfExamShort;
}

const string &Registration::getKindOfExamLong() const {
    return KindOfExamLong;
}

int Registration::getExamSemester() const {
    return examSemester;
}

/*______________________________________________________________
 * Methoden:
 */

vector<Registration> Registration::parse(const string& filename) {
    ifstream input(filename);
    if(!input) {
        cerr << "Error: could not open file " << filename << endl;
    }

    size_t lines = 0;
    vector<Registration> list;
    string line;
    getline(input, line);
    while (!input.eof()) {
        getline(input, line);
        if(line.empty()) break;
        vector<string> split = Utility::splitString(line, ';');
        int matNr;
        int pVer;
        int pNr;
        int pSem;
        istringstream(split[0]) >> matNr;
        istringstream(split[2]) >> pVer;
        istringstream(split[3]) >> pNr;
        istringstream(split[6]) >> pSem;
        Registration a(matNr, split[1], pVer, pNr, split[4], split[5], pSem);
        list.push_back(a);
        ++lines;
    }
    input.close();
    cout << lines << "\tparsed registrations" << endl;
    return list;
}
