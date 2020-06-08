#include <iostream>
#include "Raum.h"
#include "Anmeldung.h"

int main() {
    //Raum::parseRaumliste("../../input/Raumliste.csv");
    Anmeldung::parse("../../input/Anmeldungen_WS2019_KL.csv");
    return 0;
}
