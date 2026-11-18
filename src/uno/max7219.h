// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file max7219.h
 * @brief Defines Display implementation Max7219Display.
 */

#pragma once

#include <stdint.h>
#include <LedControl.h>

#include "display.h"


/**
 * @class EepromStorage
 * @brief Implements storage to provide access to Arduino Uno's EEPROM storage.
 */
class Max7219Display : public Display {
public:
  Max7219Display (
    uint8_t data_pin = 12,
    uint8_t cs_pin = 11, 
    uint8_t clk_pin = 10,
    uint8_t num_devices = 1,
    uint8_t display_address = 0);

  void init () override;

  void clear () override;

  void displayTime (uint16_t hours, uint8_t minutes, uint8_t seconds) override;
private:
  /// Ledcontrol instance for display control.
  LedControl led_control_;

  /// Address of the main MAX7219 device on the display device cascade.
  uint8_t display_address_;

  /// Segment A where MAX7219 digits are HGFEDCBA
  const uint8_t SEGMENT_A = 0;
  /// Segment B where MAX7219 digits are HGFEDCBA
  const uint8_t SEGMENT_B = 1;
  /// Segment C where MAX7219 digits are HGFEDCBA
  const uint8_t SEGMENT_C = 2;
  /// Segment D where MAX7219 digits are HGFEDCBA
  const uint8_t SEGMENT_D = 3;
  /// Segment E where MAX7219 digits are HGFEDCBA
  const uint8_t SEGMENT_E = 4;
  /// Segment F where MAX7219 digits are HGFEDCBA
  const uint8_t SEGMENT_F = 5;
  /// Segment G where MAX7219 digits are HGFEDCBA
  const uint8_t SEGMENT_G = 6;
  /// Segment H where MAX7219 digits are HGFEDCBA
  const uint8_t SEGMENT_H = 7;
};