// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <vector>
#include <LedControl.h>

#include "max7219.h"
#include "format_time.h"


Max7219Display::Max7219Display (
    uint8_t data_pin,
    uint8_t cs_pin, 
    uint8_t clk_pin,
    uint8_t num_devices,
    uint8_t display_address)
    : display_address_(display_address), 
    led_control_(data_pin, clk_pin, cs_pin, num_devices) {}

void Max7219Display::clear () {
  led_control_.clearDisplay(display_address_);
}

void Max7219Display::init () {
  // init onboard led as part of the display
  pinMode(LED_BUILTIN, OUTPUT);

  led_control_.shutdown(display_address_, false); // powerup display
  led_control_.clearDisplay(display_address_);
  led_control_.setIntensity(display_address_, 1);

  // test all 8 digits one by one, all segments each.
  for (int i = 0; i < 8; i++) { 
    led_control_.setRow(display_address_, i, B11111111);
    delay(125);
  }
  for (int i = 0; i < 8; i++) { 
    led_control_.setRow(display_address_, i, B00000000);
    delay(125);
  }
}

void Max7219Display::displayTime (
  uint16_t hours, 
  uint8_t minutes, 
  uint8_t seconds) {
  // blink onboard led 
  if (seconds % 2 == 0) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);

  std::vector<Segment> segments = formatTime(hours, minutes, seconds);

  led_control_.setDigit(display_address_, SEGMENT_A, 
    segments[0].digit, 
    false);
  led_control_.setDigit(display_address_, SEGMENT_B,
    segments[1].digit, 
    false);

  led_control_.setChar(display_address_, SEGMENT_C, 
    segments[2].character, 
    false);
  
  led_control_.setDigit(display_address_, SEGMENT_D, 
    segments[3].digit, 
    false);
  led_control_.setDigit(display_address_, SEGMENT_E, 
    segments[4].digit, 
    false);
  led_control_.setDigit(display_address_, SEGMENT_F, 
    segments[5].digit, 
    false);
  led_control_.setDigit(display_address_, SEGMENT_G, 
    segments[6].digit, 
    false);
  led_control_.setDigit(display_address_, SEGMENT_H, 
    segments[7].digit, 
    false);
}
