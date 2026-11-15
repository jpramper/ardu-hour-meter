// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file main.cpp
 * @brief Main entrypoint.
 */

#include "logic.h"
#include "display.h"
#include "reset.h"


/// One-time hardware and display initialization.
void setup() {
  initEprom();

  loadTime(HOURS, MINUTES, SECONDS);
  
  initDisplay();

  setupButtonInterrupt();
}

/// Main loop 
void loop() {
  clearDisplay();
  
  tick(HOURS, MINUTES, SECONDS);

  blinkOnboardLed(SECONDS);

  displayTime(HOURS, MINUTES, SECONDS);

  delay(1000);
}
