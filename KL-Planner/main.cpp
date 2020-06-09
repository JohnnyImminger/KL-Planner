#include "Raum.h"
#include "Anmeldung.h"
#include "Pruefung.h"

int main() {
    Raum::parseRaumliste("../../input/Raumliste.csv");
    //Anmeldung::parse("../../input/Anmeldungen_WS2019_KL.csv");
    //Pruefung::parse("../../input/Angebotene_Pruefungen_KL.csv");
    return 0;
}
