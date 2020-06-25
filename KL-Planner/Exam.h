//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_EXAM_H
#define KL_PLANNER_EXAM_H

#include "Utility.h"
#include "Registration.h"
#include "Student.h"


using namespace std;

class Exam {

public:
    /*
     * Konstruktoren und toString();
     */

    Exam();
    Exam(string& course, string& vertiefung, int examVersion, int examId, string& examName,
         int prof1Id, string& prof1Name, int prof2Id, string& prof2Name,
         float duration, string& kindOfExam, int examSemester, bool projectable);
    friend std::ostream& operator<<(std::ostream &out, const Exam &exam);

    /*
     * Getter und Setter
     */

    int getIndex();
    const string &getCourse() const;
    const string &getVertiefung() const;
    int getVersion() const;
    int getId() const;
    const string &getName() const;
    int getProf1Id() const;
    const string &getProf1Name() const;
    int getProf2Id() const;
    const string &getProf2Name() const;
    float getDurationFloat() const;
    int getDurationTimeSlots() const;
    const string &getKindOfExam() const;
    int getSemester() const;
    bool isProjectable() const;
    bool isReadyForScheduling() const;
    bool isScheduled() const;

    vector<int> getProfs();
    const vector<int> &getStudents() const;
    int getMemberCount() const;

    vector<int> getRoomIndices();
    int getDay() const;
    int getStartTimeSlot() const;


    void setIndex(int index);
    void setProjectable(bool projectable);
    void setScheduled(bool scheduled);
    void setDay(int day);
    void setStartTimeSlot(int startTimeSlot);

    /*_____________________________________
     * Methoden:
     */

    //holt sich die Daten aus der csv
    static vector<Exam> parse(const string& pathToFile);

    //added den Index des Studenten
    void addStudent(int index);
    void addProf(int index);
    void addRoom(int index);
    void removeRoom(int index);

private:
    int index;
    string course;
    string vertiefung;
    int version;
    int id;
    string name;
    int prof1Id;
    string prof1Name;
    int prof2Id;
    string prof2Name;
    float duration;
    int durationTimeSlots;
    string kindOfExam;
    int semester;
    bool offered;
    bool projectable;
    bool scheduled;

    vector<int> roomIndices;
    vector<int> profIndices;
    vector<int> studentIndices;
    int memberCount;
    int day;
    int startTimeSlot;
};

#endif //KL_PLANNER_EXAM_H
