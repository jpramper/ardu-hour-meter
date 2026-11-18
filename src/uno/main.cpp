// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file main.cpp
 * @brief Main entrypoint for uno platform.
 */

#include "time.h"
#include "eeprom.h"
#include "max7219.h"
#include "reset.h"

EepromStorage eeprom;
Max7219Display display;
Time time(eeprom);
ResetButton resetButton(time);

/// One-time hardware and display initialization.
void setup() {
  eeprom.init();

  time.load();
  
  display.init();

  resetButton.init();
}

/// Main loop 
void loop() {
  display.clear();
  
  time.tick();

  display.displayTime(time.hours(), time.minutes(), time.seconds());

  delay(1000);
}
