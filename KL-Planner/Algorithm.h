//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_ALGORITHM_H
#define KL_PLANNER_ALGORITHM_H

#include "ReadInput.h"
#include <map>

using namespace std;

class Algorithm {

public:
    /*
     * Konstruktoren
     */

    explicit Algorithm(ReadInput& data);

    /*_____________________________________
     * Methoden:
     */

    void run();
    void initTage();
    void printResultByExams(const string &filename);
    void printResultByRooms(const string &filename);
    void printResultByProfs(const string &filename);
    void printResultByStudent(const string &filename);

private:
    /*
     * Attribute
     */

    ReadInput data;
    vector<Room> days [Utility::examinationPeriod]; //9 Tage

    /*_____________________________________
     * Methoden:
     */

    //gibt einen sortierten vektor mit Klausurindices nach Größe und Länge zurück
    vector<int> sortKlausurenBySize();
    //gibt den nächsten index aus dem Vektor zurück, Klausuren ohne Teilnehmer werden ignoriert
    int selectNextKlausur(vector<int> &indices);
    /*______________________________________________________________________________________________________________________
     * Exam einsortieren und buchen
     */
    bool scheduleKlausur(Exam& klausur);
    vector<int> getRoomIndicesForKlausur(Exam& klausur, int day, int start);
    vector<int> getSelectableRoomIndices(Exam& kl, int day, int start);
    void sortRoomIndicesBySize(vector<int>& indices);
    /*
     * Exam bei passendem Termin buchen
     */
    bool bookKlausur(Exam& klausur, int day, int start, vector<int>& roomIndices);

    /*
     * Teilnehmer Bedingungen
     */
    bool areAllMemberAvailable(Exam &klausur, int day, int start);
    bool areAllProfsOfKlausurAvailable(Exam &klausur, int day, int start);
    bool areAllStudentsOfKlausurAvailable(Exam &klausur, int startTime, int duration);
    bool isProfAvailable(Professor& prof, int askedStartTime, int askedDuration, int day);
    bool isStudentAvailable(Student& student, int day, int start, int duration);
    bool isTimeOverlapping(int start, int end, int busyStart, int busyEnd, int personalBreak);
};


#endif //KL_PLANNER_ALGORITHM_H
