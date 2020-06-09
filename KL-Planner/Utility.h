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
     * Varialbe Vorgaben durch Aufgabenstellung
     */
    static float klausurPauseProf();
    static float klausurPauseStudent();
    static float klausurPauseRaum();
    static int maxKlausurenStudentProTag();
    static float startZeitKlausurTag();
    static float endZeitKlausurTag();
    static float klausurTimeSlot();
    static int klausurTage();

};



#endif //KL_PLANNER_UTILITY_H
