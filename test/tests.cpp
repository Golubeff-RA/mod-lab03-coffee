// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>

#include "Automata.h"

TEST(automata_test, starting) {
  Automata a{std::cout};
  ASSERT_EQ(STATES::OFF, a.getState());
}

TEST(automata_test, coin_when_off) {
  Automata a{std::cout};
  a.coin(10);
  ASSERT_EQ(STATES::OFF, a.getState());
  ASSERT_EQ(0, a.getCash());
}

TEST(automata_test, choise_when_off) {
  Automata a{std::cout};
  a.choice("Cappucino");
  ASSERT_EQ(STATES::OFF, a.getState());
}

TEST(automata_test, cancel_when_off) {
  Automata a{std::cout};
  a.cancel();
  ASSERT_EQ(STATES::OFF, a.getState());
  ASSERT_EQ(0, a.getCash());
}

TEST(automata_test, turn_on) {
  Automata a{std::cout};
  a.on();
  ASSERT_EQ(STATES::WAIT, a.getState());
}

TEST(automata_test, first_coin) {
  Automata a{std::cout};
  a.on();
  a.coin(50);
  ASSERT_EQ(STATES::ACCEPT, a.getState());
  ASSERT_EQ(50, a.getCash());
}

TEST(automata_test, multiple_coin) {
  Automata a{std::cout};
  a.on();
  a.coin(20);
  a.coin(30);
  ASSERT_EQ(STATES::ACCEPT, a.getState());
  ASSERT_EQ(50, a.getCash());
}

TEST(automata_test, cancel_from_start) {
  Automata a{std::cout};
  a.on();
  a.cancel();
  ASSERT_EQ(STATES::WAIT, a.getState());
  ASSERT_EQ(0, a.getCash());
}

TEST(automata_test, cancel_with_coin) {
  Automata a{std::cout};
  a.on();
  a.coin(50);
  a.cancel();
  ASSERT_EQ(STATES::WAIT, a.getState());
  ASSERT_EQ(50, a.getCash());
}

TEST(automata_test, choose_with_no_coins) {
  Automata a{std::cout};
  a.on();
  a.choice("Cappucino");
  ASSERT_EQ(STATES::WAIT, a.getState());
}

TEST(automata_test, check_coin) {
  Automata a{std::cout};
  a.on();
  a.coin(70);
  ASSERT_EQ(STATES::ACCEPT, a.getState());
  ASSERT_EQ(70, a.getCash());
}

TEST(automata_test, add_coin) {
  Automata a{std::cout};
  a.on();
  a.coin(60);
  a.coin(40);
  ASSERT_EQ(STATES::ACCEPT, a.getState());
  ASSERT_EQ(100, a.getCash());
}

TEST(automata_test, cancel_in_accept) {
  Automata a{std::cout};
  a.on();
  a.coin(80);
  a.cancel();
  ASSERT_EQ(STATES::WAIT, a.getState());
  ASSERT_EQ(80, a.getCash());
}

TEST(automata_test, choose_valid_drink) {
  Automata a{std::cout};
  a.on();
  a.coin(150);
  a.choice("Latte");
  a.change();
  ASSERT_EQ(STATES::WAIT, a.getState());
  ASSERT_EQ(0, a.getCash());
}

TEST(automata_test, turn_off_from_wait) {
  Automata a{std::cout};
  a.on();
  a.off();
  ASSERT_EQ(STATES::OFF, a.getState());
  ASSERT_EQ(0, a.getCash());
}

TEST(automata_test, off_from_accept) {
  Automata a{std::cout};
  a.on();
  a.coin(100);
  a.off();
  ASSERT_EQ(STATES::ACCEPT, a.getState());
  ASSERT_EQ(100, a.getCash());
}

TEST(automata_test, off_from_off) {
  Automata a{std::cout};
  a.off();
  ASSERT_EQ(STATES::OFF, a.getState());
}
TEST(automata_test, full_scenary) {
  Automata a{std::cout};
  a.on();
  a.coin(90);
  a.choice("Espresso");
  a.off();
  ASSERT_EQ(STATES::OFF, a.getState());
}