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
    vector<int> sortExamsBySize();
    //gibt den nächsten index aus dem Vektor zurück, Klausuren ohne Teilnehmer werden ignoriert
    int selectNextExam(vector<int> &indices);
    /*______________________________________________________________________________________________________________________
     * Exam einsortieren und buchen
     */
    bool scheduleExamIntoSingleUsedRoom(Exam &exam);
    vector<int> getFillableStartTimesFromUsedRoom(int raumIndex, int day);
    vector<int> findAvailableUsedRoomAtDay(int examSize, int dispersion, int duration, int day);
    bool isRoomUsedAndAvailable(Room &room,int examSize, int dispersion, int startTime, int duration);
    bool scheduleExam(Exam& exam);
    vector<int> getRoomIndicesForExam(Exam& exam, int day, int start);
    vector<int> getSelectableRoomIndices(Exam& exam, int day, int start);
    void sortRoomIndicesBySize(vector<int>& indices);
    /*
     * Exam bei passendem Termin buchen
     */
    bool bookExam(Exam& exam, int day, int start, vector<int>& roomIndices);

    /*
     * Teilnehmer Bedingungen
     */
    bool areAllMemberAvailable(Exam &exam, int day, int start);
    bool areAllProfsOfExamAvailable(Exam &exam, int day, int start);
    bool areAllStudentsOfExamAvailable(Exam &exam, int day, int start);
    bool isProfAvailable(Professor& prof, int askedStartTime, int askedDuration, int day);
    bool isStudentAvailable(Student& student, int day, int start, int duration);
    static bool isTimeOverlapping(int start, int end, int busyStart, int busyEnd, int personalBreak);
};


#endif //KL_PLANNER_ALGORITHM_H
