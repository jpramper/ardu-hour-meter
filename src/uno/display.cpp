// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <vector>
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
  lc.setIntensity(DISPLAY_ADDRESS, 1);

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

void displayTime (std::vector<Segment> segments) {
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_A, 
    segments[0].digit, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_B,
    segments[1].digit, 
    false);

  lc.setChar(DISPLAY_ADDRESS, SEGMENT_C, 
    segments[2].character, 
    false);
  
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_D, 
    segments[3].digit, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_E, 
    segments[4].digit, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_F, 
    segments[5].digit, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_G, 
    segments[6].digit, 
    false);
  lc.setDigit(DISPLAY_ADDRESS, SEGMENT_H, 
    segments[7].digit, 
    false);
}
