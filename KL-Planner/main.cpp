//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "ReadInput.h"
#include "Algorithmus.h"

int main() {
    ReadInput data;
    data.init();
    Algorithmus alg = Algorithmus(data);
    alg.initTage();
    alg.run();
    return 0;
}
