// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file main.cpp
 * @brief Main entrypoint.
 */

#include "constants.h"
#include "display.h"

/**
 * @brief One-time hardware and display initialization.
 */
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  lc.shutdown(DISPLAY_ADDRESS, false);
  lc.clearDisplay(DISPLAY_ADDRESS);

  // Self-test: light each of the 8 rows one at a time.
  for (int i = 0; i < 8; i++) {
    lc.setRow(DISPLAY_ADDRESS, i, B11111111);
    delay(DELAY_TIME_MS);
  }
  lc.clearDisplay(DISPLAY_ADDRESS);
  delay(DELAY_TIME_MS);
}

/**
 * @brief Main loop 
 */
void loop() {
  lc.setDigit(DISPLAY_ADDRESS, 0, 1, false);
  lc.setChar(DISPLAY_ADDRESS, 1, '-', false);

  delay(500);
  lc.clearDisplay(DISPLAY_ADDRESS);
  
}
