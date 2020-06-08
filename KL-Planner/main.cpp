#include <iostream>
#include "Anmeldung.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    string s("../../input/Anmeldungen_WS2019_KL.csv");
    vector<Anmeldung> list = Anmeldung::parse(s);
    return 0;
}
