// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <Arduino.h>

#include "reset.h"
#include "constants.h"
#include "logic.h"


volatile unsigned long LAST_TRIGGER = 0;


void setupButtonInterrupt () {
  attachInterrupt(digitalPinToInterrupt(RESET_BUTTON_PIN), buttonInterruptReset, FALLING);
}

void buttonInterruptReset () {
  unsigned long currentTime = millis();

  if (currentTime - LAST_TRIGGER > BUTTON_DEBOUNCE_DELAY) {
    HOURS = 0;
    MINUTES = 0;
    SECONDS = 0;
    saveTime(HOURS, MINUTES, SECONDS);
    LAST_TRIGGER = currentTime;
  }
}
