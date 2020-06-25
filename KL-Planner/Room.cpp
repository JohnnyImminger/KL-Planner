//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Room.h"

/*
 * Konstruktoren
 */

Room::Room() {
    this->kindOfRoom = "DummyRoom";
    this->building = 404;
    this->adrRoom = 404;
    this->capacity = 0;
    fill_n(this->timeSlots, Utility::timeSlotsPerDay + Utility::timeSlotsRoomBreak, this->capacity);
}

Room::Room(string &kindOfRoom, int building, int adrRoom, int capacity) {
    this->kindOfRoom = kindOfRoom;
    this->building = building;
    this->adrRoom = adrRoom;
    this->capacity = capacity / Utility::roomDivider;
    fill_n(this->timeSlots, Utility::timeSlotsPerDay + Utility::timeSlotsRoomBreak, this->capacity);
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Room &room) {
    out << room.kindOfRoom << ';' << room.building << '/' << room.adrRoom << ';' << room.capacity;
    return out;
}

//A = 100% free, B = 99% - 50% , C = 49% - 20%, D = 19% - 1% E = 0% free
void Room::printTimeSlots(ostream& out){
    int counter = 1;
    for (int freeCapacity : timeSlots) {
        if (freeCapacity == this->capacity){
            out << counter <<";A;";
        } else if (freeCapacity >= this->capacity * 0.5){
            out << counter<<";B;";
        } else if (freeCapacity == this->capacity * 0.2){
            out << counter<<";C;";
        } else if (freeCapacity == 0){
            out <<counter <<";E;";
        } else {
            out << counter<<";D;";
        }
        counter++;
    }
}

void Room::printFreeTimeslots(ostream& out) {
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

int Room::getAdrBau() const {
    return building;
}

int Room::getAdrRaum() const {
    return adrRoom;
}

int Room::getCapacity() const {
    return capacity;
}

/*______________________________________________________________
 * Methoden:
 */

vector<Room> Room::parse(const string& pathToFile) {
    ifstream input(pathToFile);
    if(!input) {
        cerr << "Error: could not open file " << pathToFile << endl;
    }
    size_t lines = 0;
    vector<Room> list;
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
        Room a (splitRaum[0], adrBau, adrRaum, kap);
        list.push_back(a);
        ++lines;
    }
    input.close();
    cout << lines << "\tparsed rooms" << endl;
    return list;
}



/*
 * Ressourcen-System
 */

int Room::getFreeSpaceAt(int start, int duration) {
    //nicht valide startZeit - Vermeidung von ArrayOutOfBounds
    if (start < 0){
        cout << "Error: Room::getFreeSpaceAt() - Startzeit < 0!" << endl;
        return 0;
    }
    //nicht valide startZeit - Vermeidung von ArrayOutOfBounds
    if (start + duration >= Utility::timeSlotsPerDay){
        return 0;
    }
    int maxFreeCapacity = this->capacity;
    for (int time = start; time < start + duration; ++time) {
        int freeCapacity = timeSlots[time];
        if (freeCapacity < maxFreeCapacity){
            maxFreeCapacity = freeCapacity;
        }
    }
    return maxFreeCapacity;
}

bool Room::bookTimeSlots(int start, int duration, int bookedCapacity) {
    int noFail = true;
    int index;
    for (index = start; index < start + duration; ++index) {
        this->timeSlots[index] -= bookedCapacity;

    }
    //Ausgleich der Imaginären Slots durch die Pause in den Räumen
    for (; index < start + duration + Utility::timeSlotsRoomBreak; ++index) {
        if (index >= Utility::timeSlotsPerDay + Utility::timeSlotsRoomBreak){
            cout << "Error: bookTimeSlots() - Zu großer slotIndex bei Room: " << this->building << "/" << this->adrRoom << " bei " << start << " bis " << start + duration << "!" << endl;
            return false;
        }
        this->timeSlots[index] = 0;
    }
    return noFail;
}

bool Room::isEmpty(int start, int duration) {
    for (int i = start; i< start + duration + Utility::timeSlotsRoomBreak; i++) {
        if (capacity > timeSlots[i]) return false;
    }
    return true;
}
