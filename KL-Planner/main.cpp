#include <iostream>
#include "Raum.h"

int main() {
    Raum input;
    input.parseRaumliste("C:\\Users\\stein\\CLionProjects\\KL-Planner-Github\\input\\Raumliste.csv");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
