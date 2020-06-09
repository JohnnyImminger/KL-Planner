//
// Created by Johnny on 08.06.2020.
//

#include "Student.h"

Student::Student() {
    this->matrikelNr = 404;
    this->studiengang = "DummyStudent";
}



Student::Student(int matikelNr, string studiengang) {
    this->matrikelNr = matikelNr;
    this->studiengang = studiengang;
}



std::ostream &operator<<(ostream &out, const Student &student) {
    out << student.matrikelNr << ';' << student.studiengang;
    return out;
}

int Student::getMatrikelNr() const {
    return matrikelNr;
}

const string &Student::getStudiengang() const {
    return studiengang;
}

vector<Student> Student::initStudenten(vector<Anmeldung> &anmeldungenListe, vector<Pruefung> &pruefungenListe) {
    int counter = 0;
    vector<Student> liste;
    for (auto& anmeldung : anmeldungenListe){
        for (auto& studenten : liste){
            if (studenten.getMatrikelNr() == anmeldung.getMatrikelNr()){
                studenten.addPruefung(anmeldung, pruefungenListe);
                break;
            }
            Student st = Student(anmeldung.getMatrikelNr(),anmeldung.getStudiengang());
            st.addPruefung(anmeldung, pruefungenListe);
            liste.push_back(Student(anmeldung.getMatrikelNr(),anmeldung.getStudiengang()));
            counter++;
        }
    }
    cout << counter << " Studenten wurden erzeugt."  << endl;
    return liste;
}

void Student::addPruefung(Anmeldung &anmeldung, vector<Pruefung> &pruefungenListe) {
    for (int i=0; i<pruefungenListe.size(); i++){
        Pruefung pruefung = pruefungenListe [i];
        //TODO muss pNummer und pVersion identisch sein?
        if (pruefung.getPNummer() == anmeldung.getPNummer() && pruefung.getPVersion() == anmeldung.getPVersion()){
            this->pruefungsIndex.push_back(i);
            break;
        }
    }
}
