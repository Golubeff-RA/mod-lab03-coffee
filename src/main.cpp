// Copyright 2022 UNN-IASR
#include <iostream>

#include "Automata.h"

int main() {
    Automata machine{std::cout};
    machine.on();
    machine.printMenu();
    machine.coin(50);
    machine.coin(50);
    machine.choice("Espresso");
}