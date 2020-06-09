//
// Created by Johnny on 08.06.2020.
//

#include "ReadInput.h"

vector<Pruefung> *ReadInput::getPruefungen() {
    return nullptr;
}

vector<Professor> ReadInput::createProfs() {
    vector<Professor> profs;
    vector<Pruefung> klausuren = *ReadInput::getPruefungen();
    for (Pruefung klausur: klausuren) {
        if (klausur.getPPruefer1() != 0) {
            int index = isProfInVector(profs, klausur.getPPruefer1());
            if (index >= 0) {
                profs.at(index).addPruefung(klausur.getIndex());
            } else {

            }
        }
        if (klausur.getPPruefer2() != 0) {

        }
    }

    return profs;
}

int ReadInput::isProfInVector(vector<Professor> &profs, int nr) {
    int index = -1;
    for (int i = 0; i < profs.size(); ++i) {
        if(profs.at(i).getIdentNr() == nr) {
            index = i;
            break;
        }
    }
    return index;
}

void ReadInput::parseInput() {
    this->raeume = Raum::parseRaumliste("../../input/Raumliste.csv");
    this->anmeldungen = Anmeldung::parse("../../input/Anmeldungen_WS2019_KL.csv");
    this->klausuren = Pruefung::parse("../../input/Angebotene_Pruefungen_KL.csv");
}

vector<Student> ReadInput::initStudenten(vector<Anmeldung> &anmeldungenListe, vector<Pruefung> &pruefungenListe) {
    int counter = 0;
    vector<Student> liste;
    //TODO
    /*
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
     */
    cout << counter << " Studenten wurden erzeugt."  << endl;
    return liste;
}
