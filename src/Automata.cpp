// Copyright 2022 UNN-IASR
#include "Automata.h"

#include <chrono>
#include <thread>

void Automata::on() {
    if (state_ == STATES::OFF) {
        state_ = STATES::WAIT;
    } else {
        out_stream_ << "Machine is already working\n";
    }
}

void Automata::off() {
    if (state_ == STATES::WAIT) {
        change();
        state_ = STATES::OFF;
    } else {
        if (state_ != STATES::OFF) {
            out_stream_ << "Machine is working, pls wait\n";
        }
    }
}

void Automata::coin(int money) {
    if (state_ == STATES::WAIT || state_ == STATES::ACCEPT) {
        cash_ += money;
        state_ = STATES::ACCEPT;
    } else {
        out_stream_ << "Unable to do this action now\n";
    }
}

void Automata::choice(std::string drink) {
    if (state_ == STATES::ACCEPT) {
        if (menu_.find(drink) == menu_.end()) {
            out_stream_ << "Unable to make this drink";
            cancel();
        } else {
            state_ = STATES::CHECK;
            check(drink);
        }
    }
}
void Automata::cancel() {
    if (state_ != STATES::OFF) {
        state_ = STATES::WAIT;
    }
}

STATES Automata::getState() {
    return state_;
}

void Automata::printMenu() {
    for (auto pos : menu_) {
        out_stream_ << pos.first << ' ' << pos.second << '\n';
    }
}
void Automata::check(std::string drink) {
    if (state_ == STATES::CHECK) {
        if (cash_ < menu_[drink]) {
            out_stream_ << "No money, top up your balance\n";
            cancel();
        } else {
            cash_ -= menu_[drink];
            cook();
        }
    } else {
        out_stream_ << "Ivalid state_";
    }
}
void Automata::cook() {
    out_stream_ << "Started preparing. Pls, wait\n";
    state_ = STATES::COOK;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    out_stream_ << "Drink prepapred!\n";
    finish();
}

void Automata::finish() {
    state_ = STATES::WAIT;
}

void Automata::change() {
    if (state_ == STATES::WAIT) {
        if (cash_ > 0) {
            out_stream_ << "Here is your change" << cash_;
            cash_ = 0;
        }
    }
}
int Automata::getCash() {
    return cash_;
}