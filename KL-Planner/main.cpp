#include "Raum.h"
#include "Anmeldung.h"
#include "Pruefung.h"
#include "Professor.h"

int main() {
    Raum::parseRaumliste("../../input/Raumliste.csv");
    Anmeldung::parse("../../input/Anmeldungen_WS2019_KL.csv");
    Pruefung::parse("../../input/Angebotene_Pruefungen_KL.csv");
    cout << "create profs" << endl;
    Professor::createProfs();
    cout << "done creating profs" << endl;
    return 0;
}
