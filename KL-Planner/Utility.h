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

using namespace std;

class Utility {
public:
    static vector<string> splitString(string &s, char delimiter);
    static string removeChars(string &s, string &charsToRemove);

    static bool isTimeSlotTooLong(int startTimeSlot, int dauerTimeSlot);
    /*
     * Varialbe Vorgaben durch Aufgabenstellung
     */
    //TODO comments der Aufgabenstellung zur Erklärung
    constexpr const static float pauseProf = 0.5; //30min
    constexpr const static float pauseStudent = 4;
    constexpr const static float pauseRaum = 1;
    const static int maxKlausurenProTagStudent = 2;
    constexpr const static float startZeitProTag = 8;
    constexpr const static float endZeitProTag = 18;
    const static int klausurTage = 9;

    constexpr const static float gesamtZeitProTag = endZeitProTag - startZeitProTag;

    /*
     * Umrechnung der Zeiten in Timeslots
     */

    const static int timeSlotsProStunde = 4; //15min pro Slot
    const static int timeSlotsPauseProf = (int) pauseProf * timeSlotsProStunde;
    const static int timeSlotsPauseStudent = (int) pauseStudent * timeSlotsProStunde;
    const static int timeSlotsPauseRaum = (int) pauseRaum * timeSlotsProStunde;
    const static int timeSlotsProTag = (int) gesamtZeitProTag * timeSlotsProStunde;



};

#endif //KL_PLANNER_UTILITY_H
