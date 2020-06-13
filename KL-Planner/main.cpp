//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "ReadInput.h"
#include "Algorithmus.h"
#include <chrono>

int main() {
    using namespace chrono;
    milliseconds start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    ReadInput data;
    data.init();
    Algorithmus alg = Algorithmus(data);
    alg.initTage();
    alg.run();
    alg.printResult("../../output/result.csv");
    alg.printRaumplanliste("../../output/raumPlanListe.csv");
    alg.printProfpalnliste("../../output/profPlanListe.csv");
    alg.printStudentplanliste("../../output/studentPlanListe.csv");

    milliseconds end = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    cout << "Executed in " << (end-start).count()/1000 << 's' << endl;
    return 0;
}