//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Raum.h"

/*
 * Konstruktoren
 */

Raum::Raum() {
    this->raumArt = "DummyRaum";
    this->adrBau = 404;
    this->adrRaum = 404;
    this->capacity = 0;
}

Raum::Raum(string &art, int adrBau, int adrRaum, int cap) {
    this->raumArt = art;
    this->adrBau = adrBau;
    this->adrRaum = adrRaum;
    this->capacity = cap / Utility::roomDivider;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Raum &raum) {
    out << raum.getRaumArt() << ';' << raum.getAdrBau() << '/' << raum.getAdrRaum() << ';' << raum.getCapacity();
    return out;
}

//A = 100% free, B = 99% - 50% , C = 49% - 20%, D = 19% - 1% E = 0% free
void Raum::printTimeSlots(ostream& out){
    for (int freeCapacity : timeSlots) {
        if (freeCapacity == this->capacity){
            out << "A;";
        } else if (freeCapacity >= this->capacity * 0.5){
            out << "B;";
        } else if (freeCapacity == this->capacity * 0.2){
            out << "C;";
        } else if (freeCapacity == 0){
            out << "E;";
        } else {
            out << "D;";
        }
    }
}

void Raum::printFreeTimeslots(ostream& out) {
    int counter = 1;
    for(int slot : timeSlots){
        if(slot == this->capacity){
            out << counter << ";F;";
        }else{
            out << counter << ";B;";
        }
        counter ++;
    }
}
/*
 * Getter
 */

const string &Raum::getRaumArt() const {
    return raumArt;
}

int Raum::getAdrBau() const {
    return adrBau;
}

int Raum::getAdrRaum() const {
    return adrRaum;
}

int Raum::getCapacity() const {
    return capacity;
}

const int *Raum::getTimeSlots() const {
    return timeSlots;
}

/*______________________________________________________________
 * Methoden:
 */

vector<Raum> Raum::parse(const string& pathToFile) {
    ifstream input(pathToFile);
    if(!input) {
        cerr << "Fehler beim Oeffnen der Datei " << pathToFile << endl;
    }
    size_t lines = 0;
    vector<Raum> list;
    string line;
    while (!input.eof()){
        getline(input, line);
        if(line.empty()) break;
        string remove("\"");
        line = Utility::removeChars(line, remove);
        vector<string> splitRaum = Utility::splitString(line, ',');
        vector<string> splitAdr = Utility::splitString(splitRaum[1],'/');
        int adrBau;
        int adrRaum;
        int kap;
        istringstream(splitAdr[0]) >> adrBau;
        istringstream(splitAdr[1]) >> adrRaum;
        istringstream(splitRaum[2]) >> kap;
        Raum a (splitRaum[0], adrBau, adrRaum,kap);
        list.push_back(a);
        ++lines;
    }
    input.close();
    cout << lines << " Raeume eingelesen" << endl;
    return list;
}



/*
 * Ressourcen-System
 */

int Raum::getFreeSpaceAt(int startTime, int duration) {
    //nicht valide startZeit - Vermeidung von ArrayOutOfBounds
    if (startTime < 0){
        cout << "Error: Raum::getFreeSpaceAt() - Startzeit < 0!" << endl;
        return 0;
    }
    //nicht valide startZeit - Vermeidung von ArrayOutOfBounds
    if (startTime + duration >= Utility::timeSlotsProTag){
        cout << "Error: Raum::getFreeSpaceAt() - Startzeit + Dauer >= maximale Zeit pro Tag!" << endl;
        return 0;
    }
    int minCapacity = this->capacity;
    for (int slotCapacity : timeSlots) {
        if (slotCapacity < minCapacity){
            minCapacity = slotCapacity;
        }
    }
    return minCapacity;
}

bool Raum::bookTimeSlots(int startTime, int duration, int bookedCapacity) {
    int noFail = true;
    int index;
    for (index = startTime; index < startTime + duration; ++index) {
        this->timeSlots[index] -= bookedCapacity;

    }
    //Ausgleich der Immaginären Slots durch die Pause in den Räumen
    for (; index < startTime + duration + Utility::timeSlotsPauseRaum; ++index) {
        if (index >= Utility::timeSlotsProTag + Utility::timeSlotsPauseRaum){
            cout << "Error: bookTimeSlots() - Zu großer slotIndex bei Raum: " << this->adrBau << "/" << this->adrRaum << " bei " << startTime << " bis " << startTime + duration << "!" << endl;
            return false;
        }
        this->timeSlots[index] = 0;
    }
    return noFail;
}