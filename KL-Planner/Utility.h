//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_UTILITY_H
#define KL_PLANNER_UTILITY_H

/*
 * Klasse bringt alle wichtigen Librarys and bietet nützliche Methoden
 *
 * Veränderbare Vorgaben der Aufgabenstellung
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;

class Utility {
public:
    static vector<string> splitString(string &s, char delimiter);
    static string removeChars(string &s, string &charsToRemove);
    static int getRandomInt(int max);
    static void printIgnoredExam(const string& line);

    /*
     * Variable Vorgaben durch Aufgabenstellung - Zeitangaben in Stunden --> float
     */

    //Bei Lehrenden muss zwischen zwei Einsaetzen eine Pause von mindestens 30 Minuten liegen.
    constexpr const static float profBreak = 0.5; //30min
    //Fur die Studierenden muss eine Pause von mindestens 4 Stunden zwischen zwei Klausuren liegen.
    constexpr const static float studentBreak = 4;
    //In demselben Room muss zwischen zwei Klausuren eine Pause von mindestens einer Stunde liegen.
    constexpr const static float roomBreak = 1;
    //Dabei durfen Studierende hoechstens 2 Klausuren an einem Tag schreiben.
    const static int maxExamsPerDayStudent = 2;
    //Tag - (zwischen 8 und 18 Uhr)
    constexpr const static float startTimePerDay = 8;
    constexpr const static float endTimePerDay = 18;
    //SS2020: 20.07.2020 - 29.07.2020
    const static int examinationPeriod = 9;

    constexpr const static float availableTimePerDay = endTimePerDay - startTimePerDay;

    /*
     * Umrechnung der Zeiten in Timeslots - Zeitangaben werden von Stunden in Timeslots umgerechnet
     */

    const static int timeSlotsPerHour = 12; //5min
    const static int roomDivider = 4; // der wievielte Sitzplaz kann belegt werden

    const static int timeSlotsProfBreak = (int) profBreak * timeSlotsPerHour;
    const static int timeSlotsStudentBreak = (int) studentBreak * timeSlotsPerHour;
    const static int timeSlotsRoomBreak = (int) roomBreak * timeSlotsPerHour;
    const static int timeSlotsPerDay = (int) availableTimePerDay * timeSlotsPerHour;



};

#endif //KL_PLANNER_UTILITY_H
