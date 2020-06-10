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

    /*
     * Variable Vorgaben durch Aufgabenstellung - Zeitangaben in Stunden --> float
     */

    //Bei Lehrenden muss zwischen zwei Einsaetzen eine Pause von mindestens 30 Minuten liegen.
    constexpr const static float pauseProf = 0.5; //30min
    //Fur die Studierenden muss eine Pause von mindestens 4 Stunden zwischen zwei Klausuren liegen.
    constexpr const static float pauseStudent = 4;
    //In demselben Raum muss zwischen zwei Klausuren eine Pause von mindestens einer Stunde liegen.
    constexpr const static float pauseRaum = 1;
    //Dabei durfen Studierende hoechstens 2 Klausuren an einem Tag schreiben.
    const static int maxKlausurenProTagStudent = 2;
    //Tag - (zwischen 8 und 18 Uhr)
    constexpr const static float startZeitProTag = 8;
    constexpr const static float endZeitProTag = 18;
    //SS2020: 20.07.2020 - 29.07.2020
    const static int klausurTage = 9;

    constexpr const static float gesamtZeitProTag = endZeitProTag - startZeitProTag;

    /*
     * Umrechnung der Zeiten in Timeslots - Zeitangaben werden von Stunden in Timeslots umgerechnet
     */

    const static int timeSlotsProStunde = 4; //15min pro Slot
    const static int roomDivider = 4; // der wievielte Sitzplaz kann belegt werden
    const static int timeSlotsPauseProf = (int) pauseProf * timeSlotsProStunde;
    const static int timeSlotsPauseStudent = (int) pauseStudent * timeSlotsProStunde;
    const static int timeSlotsPauseRaum = (int) pauseRaum * timeSlotsProStunde;
    const static int timeSlotsProTag = (int) gesamtZeitProTag * timeSlotsProStunde;



};

#endif //KL_PLANNER_UTILITY_H
