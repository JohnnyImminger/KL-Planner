//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Klausur.h"

/*
 * Konstruktoren
 */

Klausur::Klausur() {
    this->dataIndex = -1;
    this->studiengang = "DummyPruefung";
    this->vertiefung = "DummyPruefung";
    this->version = 404;
    this->nummer = 404;
    this->name = "DummyPruefung";
    this->pruefer1IdentNr = 404;
    this->pruefer1Name = "DummyPruefung";
    this->pruefer2IdentNr = 404;
    this->pruefer2Name = "DummyPruefung";
    this->dauer = 0;
    this->dauerTimeSlots = 0;
    this->klausurForm = "DummyPruefung";
    this->semester = 404;
    this->angeboten = false;
    this->planbar = false;
    this->eingeplant = false;
    this->anzTeilnehmer = 0;
    this->tag = -1;
    this->startZeitTimeSlot = -1;

}

Klausur::Klausur(string& studiengang, string& vertiefung, int pVersion, int pNummer, string& pName, int pPruefer1,
                 string& pruefer1, int pPruefer2, string& pruefer2, float pDauer, string& pForm, int pSemester,
                 bool angeboten) {
    this->dataIndex = -1;
    this->studiengang = studiengang;
    this->vertiefung = vertiefung;
    this->version = pVersion;
    this->nummer = pNummer;
    this->name = pName;
    this->pruefer1IdentNr = pPruefer1;
    this->pruefer1Name = pruefer1;
    this->pruefer2IdentNr = pPruefer2;
    this->pruefer2Name = pruefer2;
    this->dauer = pDauer;
    this->dauerTimeSlots = (int) ((pDauer / 60) * Utility::timeSlotsProStunde);
    this->klausurForm = pForm;
    this->semester = pSemester;
    this->angeboten = angeboten;
    this->planbar = false;
    this->eingeplant = false;
    this->anzTeilnehmer = 0;
    this->tag = -1;
    this->startZeitTimeSlot = -1;
}
/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Klausur &klausur) {
    out << klausur.getStudiengang() << ';' << klausur.getVertiefung() << ';' << klausur.getVersion() << ';' << klausur.getNummer() << ';'
        << klausur.getName() << ';' << klausur.getPruefer1IdentNr() << ';' << klausur.getPruefer1Name() << ';' << klausur.getPruefer2IdentNr() << ';'
        << klausur.getPruefer2Name() << ';' << klausur.getDauerFloat() << ';' << klausur.getKlausurForm() << ';' << klausur.getSemester() << ';'
        << klausur.isAngeboten();
    return out;
}

/*
 * Getter
 */

int Klausur::getDataIndex() {
    return this->dataIndex;
}

const string &Klausur::getStudiengang() const {
    return studiengang;
}

const string &Klausur::getVertiefung() const {
    return vertiefung;
}

int Klausur::getVersion() const {
    return version;
}

int Klausur::getNummer() const {
    return nummer;
}

const string &Klausur::getName() const {
    return name;
}

int Klausur::getPruefer1IdentNr() const {
    return pruefer1IdentNr;
}

const string &Klausur::getPruefer1Name() const {
    return pruefer1Name;
}

int Klausur::getPruefer2IdentNr() const {
    return pruefer2IdentNr;
}

const string &Klausur::getPruefer2Name() const {
    return pruefer2Name;
}

float Klausur::getDauerFloat() const {
    return dauer;
}

int Klausur::getDauerTimeSlots() const {
    return dauerTimeSlots;
}

const string &Klausur::getKlausurForm() const {
    return klausurForm;
}

int Klausur::getSemester() const {
    return semester;
}

bool Klausur::isAngeboten() const {
    return angeboten;
}

bool Klausur::isPlanbar() const {
    return planbar;
}

bool Klausur::isEingeplant() const {
    return eingeplant;
}

vector<int> Klausur::getProfs() {
    return profRefs;
}

const vector<int> &Klausur::getStudenten() const {
    return studenten;
}

int Klausur::getAnzTeilnehmer() const {
    return anzTeilnehmer;
}

vector<int> Klausur::getRaumRefs() {
    return raumRefs;
}

int Klausur::getTag() const {
    return tag;
}

int Klausur::getStartZeitTimeSlot() const {
    return startZeitTimeSlot;
}

/*
 * Setter
 */

void Klausur::setIndex(int index) {
    this->dataIndex = index;
}

void Klausur::setPlanbar(bool planbar) {
    Klausur::planbar = planbar;
}

void Klausur::setEingeplant(bool eingeplant) {
    Klausur::eingeplant = eingeplant;
}

void Klausur::setTag(int tag) {
    Klausur::tag = tag;
}

void Klausur::setStartZeitTimeSlot(int startZeitTimeSlot) {
    Klausur::startZeitTimeSlot = startZeitTimeSlot;
}

/*______________________________________________________________
 * Methoden:
 */

vector<Klausur> Klausur::parse(const string& pathToFile) {
    remove("../../output/ignoredKlausuren.csv");
    ifstream input(pathToFile);
    if(!input) {
        cerr << "Fehler beim Oeffnen der Datei " << pathToFile << endl;
    }
    int index = 0;
    size_t lines = 0;
    vector<Klausur> list;
    string line;
    getline(input, line);
    while (!input.eof()){
        getline(input, line);
        if(line.empty()) break;
        vector<string> split = Utility::splitString(line, ';');
        if(split[9] == "0" || split[9].empty()) {
            outputIgnored(line);
            continue;
        }
        int pVersion;
        int pNummer;
        int pPruefer1;
        int pPruefer2;
        float pDauer;
        int pSemeser;
        bool angeboten;
        istringstream(split[2]) >> pVersion;
        istringstream(split[3]) >> pNummer;
        istringstream(split[5]) >> pPruefer1;
        istringstream(split[7]) >> pPruefer2;
        istringstream(split[9]) >> pDauer;
        istringstream(split[11]) >> pSemeser;
        angeboten = split[12] == "J";
        Klausur a(split[0], split[1], pVersion, pNummer, split[4], pPruefer1, split[6], pPruefer2,
                  split[8], pDauer, split[10], pSemeser, angeboten);
        a.setIndex(index);
        list.push_back(a);
        ++lines;
        index++;
    }
    input.close();
    cout << lines << " Klausuren eingelesen" << endl;
    return list;
}

void Klausur::addProf(int profDataIndex) {
    profRefs.push_back(profDataIndex);
}

void Klausur::addStudent(int studentDataIndex) {
    anzTeilnehmer++;
    studenten.push_back(studentDataIndex);
}

void Klausur::addRaumRef(int raumRef) {
    raumRefs.push_back(raumRef);
}

void Klausur::removeRaumRef(int elementToRemove) {
    raumRefs.erase(raumRefs.begin()+elementToRemove);
}

void Klausur::outputIgnored(const string& line) {
    ofstream output;
    output.open("../../output/ignoredKlausuren.csv", ios_base::app);
    output << line << endl;
    output.close();
}