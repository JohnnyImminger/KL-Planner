//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "ReadInput.h"
#include "Algorithmus.h"

int main() {
    ReadInput data;
    data.init();
    Algorithmus basic = Algorithmus(data);
    basic.run();
    return 0;
}
