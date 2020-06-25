//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "ReadInput.h"
#include "Algorithm.h"
#include <chrono>

int main() {
    using namespace chrono;
    milliseconds start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    ReadInput data;
    data.init();
    Algorithm alg = Algorithm(data);
    alg.initTage();
    alg.run();
    cout << ">>printing results" << endl;
    alg.printResultByExams("../../output/result.csv");
    alg.printResultByRooms("../../output/raumPlanListe.csv");
    alg.printResultByProfs("../../output/profPlanListe.csv");
    alg.printResultByStudent("../../output/studentPlanListe.csv");

    milliseconds end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    cout << "executed in " << (end-start).count()/1000 << 's' << endl;

    return 0;
}