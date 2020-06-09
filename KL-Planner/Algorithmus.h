//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#ifndef KL_PLANNER_ALGORITHMUS_H
#define KL_PLANNER_ALGORITHMUS_H

#include "ReadInput.h"

using namespace std;

class Algorithmus {

public:
    /*
     * Konstruktoren
     */

    explicit Algorithmus(ReadInput& data);


    /*_____________________________________
     * Methoden:
     */

    void run();

private:
    /*
     * Attribute
     */

    ReadInput data;

    /*_____________________________________
     * Methoden:
     */


};


#endif //KL_PLANNER_ALGORITHMUS_H
