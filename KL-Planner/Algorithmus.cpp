//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Algorithmus.h"
#include <map>

/*
* Konstruktoren
*/

Algorithmus::Algorithmus(ReadInput& data) {
    this->data = data;
    this->lastSortedDay = 0;
}

void Algorithmus::initTage() {
    for (auto & tag : tage) {
        tag = data.raeume;
    }
}

void Algorithmus::run() {
    vector<int> klausuren =  sortKlausurenBySize();
    cout << "Klausuren nach Anzahl der Teilnehmer sortiert" << endl;
    int nextKlausurIndex = selectNextKlausur(klausuren);
    while (nextKlausurIndex != -1) {
        if (findDateAndBookKlausur(data.klausuren.at(nextKlausurIndex))) {
        } else {
            cout << "Klausur konnte nicht eingeplant werden: " << data.klausuren.at(nextKlausurIndex) << endl;
        }
        nextKlausurIndex = selectNextKlausur(klausuren);
    }
}

void Algorithmus::printResult(const string &filename) {
    ofstream file;
    file.open(filename);
    for (int i = 0; i < data.klausuren.size(); ++i) {
        Klausur cKlausur = data.klausuren.at(i);

        file << cKlausur << ';';

        vector<int> klausurRaeume = cKlausur.getRaumRefs();
        for (int j: klausurRaeume) {
            Raum cRaum = data.raeume.at(j);
            file << cRaum.getAdrBau() << '/';
            file << cRaum.getAdrRaum() << ';';
        }

        file << cKlausur.getTag() << ';';
        file << (float)cKlausur.getStartZeitTimeSlot()/Utility::timeSlotsProStunde + Utility::startZeitProTag << endl;
    }
    file.close();
}

void Algorithmus::printRaumplanliste(const string &filename) {
    ofstream file;
    file.open(filename);
    for (int i = 0; i < Utility::klausurTage; i++) {
        file << "day " << i+1 << endl;
        vector cRaume = tage[i];
        for(Raum cRaum : cRaume){
            file << cRaum.getAdrBau() << '/' << cRaum.getAdrRaum() << ';';
            cRaum.printTimeSlots(file);
            file << endl;
        }
    }
    file.close();
}

void Algorithmus::printProfpalnliste(const string &filename) {
    ofstream file;
    file.open(filename);
    for(const Professor& cProf : data.professoren){
        file << "Prof_" << cProf.getIdentNr() << endl;
        for(int i : cProf.getKlausurDataIndizes()){
            file << "beaufsichtigt;" << data.klausuren[i].getName() << ";am;" << data.klausuren[i].getTag() << ";um;" << data.klausuren[i].getStartZeitTimeSlot() << endl;
        }
    }
    file.close();
}

void Algorithmus::printStudentplanliste(const string &filename) {
    ofstream file;
    file.open(filename);
    for(const Student& cStudent : data.studenten){
        file << "Student_" << cStudent.getMatrikelNr() << endl;
        for(int i : cStudent.getKlausurDataIndizes()){
            file << "schreibt;" << data.klausuren[i].getName() << ";am;" << data.klausuren[i].getTag() << ";um;" << data.klausuren[i].getStartZeitTimeSlot() << endl;
        }
    }
    file.close();
}

/*_____________________________________
* Methoden:
*/


int Algorithmus::selectNextKlausur(vector<int> &indices) {
    // wenn der vector leer ist, soll -1 zurückgegeben werden
    while (!indices.empty()) {
        int nextIndex = indices.front();
        //wenn die Klausur keine Teilnehmer hat, wird sie ignoriert
        if(data.klausuren.at(nextIndex).getAnzTeilnehmer() == 0) {
            indices.erase(indices.begin());
            continue;
        }
        indices.erase(indices.begin());
        return nextIndex;
    }
    return -1;
}

vector<int> Algorithmus::sortKlausurenBySize() {
    vector<int> result;
    for (Klausur& klausur: data.klausuren) {
        result.push_back(klausur.getDataIndex());
    }
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < result.size()-1; ++i) {
            Klausur k1 = data.klausuren.at(result.at(i));
            Klausur k2 = data.klausuren.at(result.at(i+1));
            if (k1.getAnzTeilnehmer() < k2.getAnzTeilnehmer()) {
                int temp = (int) k1.getDataIndex();
                result.at(i) = (int) k2.getDataIndex();
                result.at(i+1) = temp;
                swapped = true;
            } else if (k1.getAnzTeilnehmer() == k2.getAnzTeilnehmer() && k1.getDauerTimeSlots() < k2.getDauerTimeSlots()) {
                int temp = (int) k1.getDataIndex();
                result.at(i) = (int) k2.getDataIndex();
                result.at(i+1) = temp;
                swapped = true;
            }
        }
    } while (swapped);
    return result;
}

/*__________________________________________________________________________________________________________________
 * Klausur einsortieren und buchen
 */


bool Algorithmus::findDateAndBookKlausur(Klausur &klausur) {
    /*__________________________________________________________________________________________________________________
     * Versuche die Klausur in einen einzelnen Raum zu bekommen --> Priorität: wenig Abweichung und einen genutzen Raum füllen
     */
    if (findDateAndBookKlausurIntoSingleRoom(klausur)){
        return true; //--> Einsortiert und Gebucht
    } //--> Raum ist ZU GROSS für einen einzelnen Raum

    /*__________________________________________________________________________________________________________________
     * Suche den größten Raum und suche einen anderen großen Raum in den alles passt --> Priorität: nutze so wenig Räume wie möglich
     */
    return findDateAndBookKlausurIntoMultibleRooms(klausur);
}

bool Algorithmus::findDateAndBookKlausurIntoSingleRoom(Klausur &klausur) {
    int abweichung = 0;
    vector <int> possibleRaumIndizes;
    while (abweichung < klausur.getAnzTeilnehmer()){
        //Suche einen schon genutzen Raum, in den alle Studenten passen
        for (int day = 0; day < Utility::klausurTage; ++day) {
            possibleRaumIndizes = findAvailableUsedRaumAtDay(klausur.getAnzTeilnehmer(), abweichung, abweichung, klausur.getDauerTimeSlots(), day);
            for (int raumIndex : possibleRaumIndizes) {
                for (int startTime : getFillableStartTimesFromUsedRoom(raumIndex, day)) {
                    if (tage[day].at(raumIndex).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()) >= klausur.getAnzTeilnehmer() && areAllMemberAvailable(klausur, startTime, klausur.getDauerTimeSlots(), day)){
                        return bookKlausurDate(klausur, startTime, day, raumIndex, klausur.getAnzTeilnehmer());
                    }
                }
            }
        }
        //Suche irgendwann irgendeinen Raum in den alle Studenten aufeinmal passen
        for (int day = 0; day < Utility::klausurTage; ++day) {
            possibleRaumIndizes = findAvailableRaumAtDay(klausur.getAnzTeilnehmer(), abweichung, abweichung, klausur.getDauerTimeSlots(), day);
            for (int raumIndex : possibleRaumIndizes) {
                for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
                    if (tage[day].at(raumIndex).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()) >= klausur.getAnzTeilnehmer() && areAllMemberAvailable(klausur, startTime, klausur.getDauerTimeSlots(), day)){
                        return bookKlausurDate(klausur, startTime, day, raumIndex, klausur.getAnzTeilnehmer());
                    }
                }
            }
        }
        abweichung++;
    }
    return false;
}

bool Algorithmus::findDateAndBookKlausurIntoMultibleRooms(Klausur &klausur) {
    cout << "called find multiple rooms" << endl;
    vector <vector<int>> possibleRaumKombinationen;
    vector<int> savedStartTime;
    vector<int> savedDay;
    for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
        for (int day = 0; day < Utility::klausurTage; ++day) {
            if (!areAllMemberAvailable(klausur, startTime, klausur.getDauerTimeSlots(),day)){
                continue;
            }
            vector <int> possibleRaumKombination = findBiggestAvailableRaumIndizes(klausur,day,startTime);
            if (possibleRaumKombination.size() == 2){
                tage[day].at(0).bookTimeSlots(startTime, klausur.getDauerTimeSlots(), tage[day].at(0).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()));
                return tage[day].at(1).bookTimeSlots(startTime, klausur.getDauerTimeSlots(), klausur.getAnzTeilnehmer() - tage[day].at(0).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()));
            }
            possibleRaumKombinationen.push_back(possibleRaumKombination);
            savedStartTime.push_back(startTime);
            savedDay.push_back(day);
        }
    }
    if (possibleRaumKombinationen.empty()){
        return false;
    }
    int resultIndex = Utility::findShortestArrayIndex(possibleRaumKombinationen);
    int resultDay = savedDay.at(resultIndex);
    int resultTime = savedStartTime.at(resultIndex);
    int restAnzTeilnehmer = klausur.getAnzTeilnehmer();
    for (int i = 0; i < possibleRaumKombinationen.at(resultIndex).size() - 1; ++i) {
        Raum& raum = tage[resultDay].at(possibleRaumKombinationen.at(resultIndex).at(i));
        raum.bookTimeSlots(resultTime, klausur.getDauerTimeSlots(), raum.getFreeSpaceAt(resultTime, klausur.getDauerTimeSlots()));
        restAnzTeilnehmer -= raum.getFreeSpaceAt(resultTime, klausur.getDauerTimeSlots());
    }
    return tage[resultDay].at(possibleRaumKombinationen.at(resultIndex).at(possibleRaumKombinationen.at(resultIndex).size() -1)).bookTimeSlots(resultTime, klausur.getDauerTimeSlots(), restAnzTeilnehmer);
}

/*
 * Suche passende Räume nach verschiedenen Prioritäten
 */


vector<int> Algorithmus::findBiggestAvailableRaumIndizes(Klausur &klausur, int day, int startTime) {
    vector<int> neededRaumIndizesForKlausur;
    vector<int> possibleRaumIndizes = findPossibleRoomIndices(klausur.getDauerTimeSlots(), day, startTime);
    int restAnzTeilnehmer = klausur.getAnzTeilnehmer();
    while (restAnzTeilnehmer > 0){

        int biggestRaumIndex = findBiggestAvailableRaumIndex(possibleRaumIndizes, neededRaumIndizesForKlausur, day, startTime, klausur.getDauerTimeSlots());

        if (restAnzTeilnehmer - tage[day].at(biggestRaumIndex).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()) < 0){
            int abweichung = 0;
            while (abweichung < restAnzTeilnehmer){
                possibleRaumIndizes = findAvailableUsedRaumAtDayAndTime(restAnzTeilnehmer, abweichung, abweichung, klausur.getDauerTimeSlots(), day, startTime);
                for (int raumIndex : possibleRaumIndizes) {
                    if (restAnzTeilnehmer - tage[day].at(raumIndex).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()) < 0){
                        neededRaumIndizesForKlausur.push_back(raumIndex);
                        return neededRaumIndizesForKlausur;
                    }
                }
                possibleRaumIndizes = findAvailableRaumAtDayAndTime(restAnzTeilnehmer, abweichung, abweichung, klausur.getDauerTimeSlots(), day, startTime);
                for (int raumIndex : possibleRaumIndizes) {
                    if (restAnzTeilnehmer - tage[day].at(raumIndex).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots()) < 0){
                        neededRaumIndizesForKlausur.push_back(raumIndex);
                        return neededRaumIndizesForKlausur;
                    }
                }
                abweichung++;
            }
        }
        restAnzTeilnehmer -= tage[day].at(biggestRaumIndex).getFreeSpaceAt(startTime, klausur.getDauerTimeSlots());
        neededRaumIndizesForKlausur.push_back(biggestRaumIndex);
    }
    return neededRaumIndizesForKlausur;
}

vector <int> Algorithmus::findPossibleRoomIndices(int timeSlotDuration, int day, int startTime) {
    vector<int> raumIndizes;
    for (int raumIndex = 0; raumIndex < tage[day].size(); ++raumIndex) {
        Raum &raum = tage[day].at(raumIndex);
        int space = raum.getFreeSpaceAt(startTime,timeSlotDuration);
        if(space < raum.getCapacity()) {
            vector<int> startTimes = getFillableStartTimesFromUsedRoom(raumIndex, day);
            bool startTimeMatch = false;
            for (int otherStartTime: startTimes) {
                if (startTime == otherStartTime) {
                    startTimeMatch = true;
                    break;
                }
            }
            if(!startTimeMatch) continue;
            else raumIndizes.push_back(raumIndex);
        } else if (space == 0) continue;
        raumIndizes.push_back(raumIndex);
    }
    return raumIndizes;
}

vector <int> Algorithmus::findRaumListeForMember(int anzTeilnehmer, int day, int startTime, int duration){

    vector <int> raumListe;
    int currentRaumIndex;
    int raumKapazitaet;

    while (anzTeilnehmer > 0){

        currentRaumIndex = findBiggestAvailableRaum(raumListe, day, startTime, duration);
        if (currentRaumIndex == -1) return raumListe; //Das sollte nicht passieren!
        raumKapazitaet = tage[day].at(currentRaumIndex).getFreeSpaceAt(startTime,duration);
        anzTeilnehmer -= raumKapazitaet;
        raumListe.push_back(currentRaumIndex);

        if (anzTeilnehmer <= 0) return raumListe;

        currentRaumIndex = findFittingAvailableRaum(anzTeilnehmer, raumListe, day, startTime, duration);
        if (currentRaumIndex != -1){
            raumListe.push_back(currentRaumIndex);
            return raumListe;
        }
    }
}

int Algorithmus::findBiggestAvailableRaum(vector<int> &excludedRaumIndizes, int day, int startTime, int duration) {
    int maxRaumIndex = -1;
    int maxRaumKapazitaet = 0;
    for (int raumIndex = 0; raumIndex < tage[day].size(); ++raumIndex) {

        if (!Utility::vectorContains(excludedRaumIndizes, raumIndex)){
            Raum &raum = tage[day].at(raumIndex);
            int freeSpace = raum.getFreeSpaceAt(startTime, duration);
            int raumKapazitaet = raum.getCapacity();
            if (isRaumUsedAndAvailable(raum, startTime, duration) || freeSpace == raumKapazitaet){
                if (freeSpace > maxRaumKapazitaet){
                    maxRaumKapazitaet = freeSpace;
                    maxRaumIndex = raumIndex;
                }
            }
        }

    }
    if (maxRaumIndex < 0) {
        cout << "Error: Algorithmus::findBiggestAvailableRaum() - returns -1 ! with Parameter: [day: " << day << " , startTime: " << startTime << " , duration: " << duration << "]" << endl;
    }
    return maxRaumIndex;
}

int Algorithmus::findFittingAvailableRaum(int anzTeilnehmer, vector<int> &excludedRaumIndizes, int day, int startTime, int duration) {
    int abweichungOfAnzTeilnehmer = 0;
    vector <int> possibleRoomIndizes;
    while (abweichungOfAnzTeilnehmer < anzTeilnehmer){
        possibleRoomIndizes = findAvailableRaumAtDayAndTime(anzTeilnehmer, abweichungOfAnzTeilnehmer, abweichungOfAnzTeilnehmer,duration, day, startTime);
        for (int raumIndex: possibleRoomIndizes) {
            if (!Utility::vectorContains(excludedRaumIndizes, raumIndex)){
                Raum &raum = tage[day].at(raumIndex);
                int freeSpace = raum.getFreeSpaceAt(startTime, duration);
                int raumKapazitaet = raum.getCapacity();
                if (isRaumUsedAndAvailable(raum, startTime, duration) || freeSpace == raumKapazitaet){
                    return raumIndex;
                }
            }
        }
        abweichungOfAnzTeilnehmer++;
    }
    return -1;
}



vector<int> Algorithmus::getFillableStartTimesFromUsedRoom(int raumIndex, int day) {
    vector<int> startTimeSlotsToFill;
    Raum& raum = tage [day].at(raumIndex);
    for (int time = 0; time < Utility::timeSlotsProTag; ++time) {
        int spaceInRoom = tage[day].at(raumIndex).getFreeSpaceAt(time,1);
        if ( 0 < spaceInRoom && spaceInRoom < tage[day].at(raumIndex).getCapacity()){
            if (time == 0){
                startTimeSlotsToFill.push_back(time);
                continue;
            }
            if (tage[day].at(raumIndex).getFreeSpaceAt(time-1,1) == 0){
                startTimeSlotsToFill.push_back(time);
            }
        }
    }
    return startTimeSlotsToFill;
}

/*
 * Find
 */

vector <int> Algorithmus::findAvailableRaumForCapacity(int klausurSize, int minAbweichung, int maxAbweichung, int duration){
    vector<int> raumIndizes;
    for (int raumIndex = 0; raumIndex < data.raeume.size(); ++raumIndex) {
        bool bookable = false;
        for (int day = 0; day < Utility::klausurTage; ++day) {
            for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
                if (isCapacityInRange(tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration), klausurSize, minAbweichung,maxAbweichung)){
                    bookable = true;
                    raumIndizes.push_back(raumIndex);
                    break;
                }
            }
            if (bookable){
                break;
            }
        }
    }
    return raumIndizes;
}

vector<int> Algorithmus::findAvailableRaumAtDay(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day) {
    vector<int> raumIndizes;
    for (int raumIndex = 0; raumIndex < tage[day].size(); ++raumIndex) {
        for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
            if (isCapacityInRange(tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration), klausurSize, minAbweichung, maxAbweichung)){
                raumIndizes.push_back(raumIndex);
                break;
            }
        }

    }
    return raumIndizes;
}

vector<int> Algorithmus::findAvailableRaumAtDayAndTime(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day, int startTime) {
    vector<int> raumIndizes;
    for (int raumIndex = 0; raumIndex < tage[day].size(); ++raumIndex) {
        if (isCapacityInRange(tage[day].at(raumIndex).getFreeSpaceAt(startTime,duration), klausurSize, minAbweichung, maxAbweichung)){
            raumIndizes.push_back(raumIndex);
        }
    }
    return raumIndizes;
}
/*
 * Used
 */

vector<int> Algorithmus::findAvailableUsedRaum(int klausurSize, int minAbweichung, int maxAbweichung, int duration) {
    vector <int> possibleRaumIndizes = findAvailableRaumForCapacity(klausurSize,minAbweichung,maxAbweichung,duration);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        bool bookable = false;
        for (int day = 0; day < Utility::klausurTage; ++day) {
            for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
                if (isRaumUsedAndAvailable(tage[day].at(raumIndex), startTime, duration)){
                    bookable = true;
                    raumIndizes.push_back(raumIndex);
                    break;
                }
            }
            if (bookable){
                break;
            }
        }
    }
    return raumIndizes;
}

vector<int> Algorithmus::findAvailableUsedRaumAtDay(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day) {
    vector <int> possibleRaumIndizes = findAvailableUsedRaum(klausurSize, minAbweichung, maxAbweichung, duration);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        for (int startTime = 0; startTime < Utility::timeSlotsProTag; ++startTime) {
            if (isRaumUsedAndAvailable(tage[day].at(raumIndex), startTime, duration)){
                raumIndizes.push_back(raumIndex);
                break;
            }
        }
    }
    return raumIndizes;
}

vector<int> Algorithmus::findAvailableUsedRaumAtDayAndTime(int klausurSize, int minAbweichung, int maxAbweichung, int duration, int day, int startTime) {
    vector <int> possibleRaumIndizes = findAvailableUsedRaumAtDay(klausurSize,minAbweichung,maxAbweichung,duration,day);
    vector<int> raumIndizes;
    for (int raumIndex : possibleRaumIndizes) {
        if (isRaumUsedAndAvailable(tage[day].at(raumIndex), startTime, duration)){
            raumIndizes.push_back(raumIndex);
        }
    }
    return raumIndizes;
}

bool Algorithmus::isRaumUsedAndAvailable(Raum &raum, int startTime, int duration) {
    int space = raum.getFreeSpaceAt(startTime,duration);
    return 0 < space && space < raum.getCapacity();
}

/*
 * Utility
 */

bool Algorithmus::isCapacityInRange(int freeRoomCapacity, int klausurSize, int minAbweichung, int maxAbweichung) {
    if (freeRoomCapacity < klausurSize) {
        return false;
    }
    //klausurSize - maxAbweichung <= freeRoomCapacity <= klausurSize - minAbweichung
    bool condition1 = klausurSize - maxAbweichung <= freeRoomCapacity && freeRoomCapacity <= klausurSize - minAbweichung;
    //klausurSize + minAbweichung <= freeRoomCapacity <= klausurSize + maxAbweichung
    bool condition2 = klausurSize + minAbweichung <= freeRoomCapacity && freeRoomCapacity <= klausurSize + maxAbweichung;

    return condition1 || condition2;
}

/*
 * Klausur bei passendem Termin buchen
 */

bool Algorithmus::bookKlausurDate(Klausur &klausur, int startTime, int day, int raumDataIndex, int bookedCapacity) {
    klausur.setTag(day);
    klausur.setStartZeitTimeSlot(startTime);
    klausur.addRaumRef(raumDataIndex);
    return tage[day].at(raumDataIndex).bookTimeSlots(startTime, klausur.getDauerTimeSlots(),bookedCapacity);

}

/*
* Teilnehmer Bedingungen
*/

bool Algorithmus::areAllMemberAvailable(Klausur &klausur, int startTime, int duration, int day) {
    return areAllProfsOfKlausurAvailable(klausur, startTime,duration,day) && areAllStudentsOfKlausurAvailable(klausur,startTime,duration,day);
}

bool Algorithmus::areAllProfsOfKlausurAvailable(Klausur &klausur, int startTime, int duration, int day) {
    for (int profIndex : klausur.getProfs()) {
        if (!isProfAvailable(data.professoren.at(profIndex), startTime, duration, day)){
            return false;
        }
    }
    return true;
}

bool Algorithmus::areAllStudentsOfKlausurAvailable(Klausur &klausur, int startTime, int duration, int day) {
    for (int studentIndex : klausur.getStudenten()) {
        if (!isStudentAvailable(data.studenten.at(studentIndex), startTime, duration, day)){
            return false;
        }
    }
    return true;
}

bool Algorithmus::isProfAvailable(Professor& prof, int askedStartTime, int askedDuration, int day) {
    for (int klausurIndex : prof.getKlausurDataIndizes()) {
        Klausur klausur = data.klausuren[klausurIndex];
        if (!klausur.isEingeplant()){
            continue;
        }
        if (klausur.getTag() == day) {
            if (isTimeOverlapping(askedStartTime, askedStartTime + askedDuration, klausur.getStartZeitTimeSlot(), klausur.getStartZeitTimeSlot() + klausur.getDauerTimeSlots(), Utility::timeSlotsPauseProf)){
                return false;
            }
        }
    }
    return true;
}

bool Algorithmus::isStudentAvailable(Student& student, int askedStartTime, int askedDuration, int day) {
    int klausurPerDay = 0;
    for (int klausurIndex : student.getKlausurDataIndizes()) {
        Klausur klausur = data.klausuren[klausurIndex];
        if (!klausur.isEingeplant()){
            continue;
        }
        if (klausur.getTag() == day) {
            klausurPerDay++;
            if (klausurPerDay >= Utility::maxKlausurenProTagStudent){
                return false;
            }
            if (isTimeOverlapping(askedStartTime, askedStartTime + askedDuration, klausur.getStartZeitTimeSlot(), klausur.getStartZeitTimeSlot() + klausur.getDauerTimeSlots(), Utility::timeSlotsPauseStudent)){
                return false;
            }
        }
    }
    return true;
}

bool Algorithmus::isTimeOverlapping(int askedStartTime, int askedEndTime, int busyStartTime, int busyEndTime, int personalBreak) {
    //busyStartTime <= askedStarttime < busyEndTime + Break --> neue Klausur würde in der alten Starten
    bool condition1 = busyStartTime <= askedStartTime && askedStartTime < busyEndTime + personalBreak;
    //busyStartTime <= askedEndTime < busyEndTime+Pause --> Endzeit schneidet vorhandene Klausur
    bool condition2 = busyStartTime <= askedEndTime && askedEndTime < busyEndTime + personalBreak;
    //askedStartTime <= busyStartTime <= busyEndTime <= askedEndTim --> neue Klausur würde vorhandene Klausur überdecken
    bool condition3 = askedStartTime <= busyStartTime && busyEndTime <= askedEndTime;
    return condition1 || condition2 || condition3;
}

/*
 * Array Bedingungen
 */

bool Algorithmus::isTimeArrayLongEnough(int startTime, int duration) {
    if (0 < startTime){
        cout << "Error: Algorithmus::isTimeArrayLongEnough() - Startzeit < 0 !"<< endl;
        return false;
    }
    return startTime + duration <= Utility::timeSlotsProTag;
}

bool Algorithmus::isRaumArrayLongEnough( int raumIndex) {
    if (0 < raumIndex){
        cout << "Error: Algorithmus::isRaumArrayLongEnough() - RaumIndex < 0 !"<< endl;
        return false;
    }
    return raumIndex <= data.raeume.size();
}

int Algorithmus::increaseStartTag(int startTag) {
    startTag++;
    if (startTag == Utility::klausurTage){
        startTag = 0;
    }
    return startTag;
}
