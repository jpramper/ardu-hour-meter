// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <Arduino.h>
#include <LedControl.h>

#include "display.h"
#include "constants.h"


LedControl lc(DATA_PIN, CLK_PIN, CS_PIN, NUM_DEVICES);


void clearDisplay () {
  lc.clearDisplay(DISPLAY_ADDRESS);
}

void initDisplay () {
  pinMode(LED_BUILTIN, OUTPUT);

  lc.shutdown(DISPLAY_ADDRESS, false); // powerup display
  lc.clearDisplay(DISPLAY_ADDRESS);

  // test all 8 digits one by one, all segments each.
  for (int i = 0; i < 8; i++) { 
    lc.setRow(DISPLAY_ADDRESS, i, B11111111);
    delay(125);
  }
  for (int i = 0; i < 8; i++) { 
    lc.setRow(DISPLAY_ADDRESS, i, B00000000);
    delay(125);
  }
}

void blinkOnboardLed (uint8_t seconds) {
  if (seconds % 2 == 0) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);
}

void displayTime (uint16_t hours, uint8_t minutes, uint8_t seconds) {
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_A, 
    minutes > 0 ? ( minutes % 10 ) : 0, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_B,
    minutes > 0 ? ( minutes % 100 ) : 0, 
    false);

  if (seconds % 2 == 0) lc.setChar(DISPLAY_ADDRESS, SEGMENT_C, '-', false);
  else lc.setChar(DISPLAY_ADDRESS, SEGMENT_C, ' ', false);
  
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_D, 
    hours > 0 ? (hours % 10) : 0, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_E, 
    hours > 10 ? (hours % 100) : 0, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_F, 
    hours > 100 ? (hours % 1000) : 0, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_G, 
    hours > 1000 ? (hours % 10000) : 0, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_H, 
    hours > 10000 ? (hours % 100000) : 0, 
    false);
}