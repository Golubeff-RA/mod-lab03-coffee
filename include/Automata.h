#pragma once

// Copyright 2022 UNN-IASR
#include <map>
#include <ostream>
#include <string>

enum class STATES { OFF, WAIT, ACCEPT, CHECK, COOK };

class Automata {
public:
    void on();
    void off();
    void coin(int money);
    void choice(std::string drink);
    void cancel();
    STATES getState();
    void printMenu();
    int getCash();
    void change();
    Automata(std::ostream &out_stream, const std::map<std::string, int> &menu = {{"Espresso", 100},
                                                                                 {"Americano", 150},
                                                                                 {"Cappucino", 200},
                                                                                 {"Latte", 250}})
        : out_stream_(out_stream), cash_(0), state_(STATES::OFF), menu_(menu) {
    }

private:
    std::ostream &out_stream_;
    int cash_;
    std::map<std::string, int> menu_;
    STATES state_;
    void check(std::string drink);
    void cook();
    void finish();
};
