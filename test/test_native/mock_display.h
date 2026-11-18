// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file mock_display.h
 * @brief Recording Display double for native unit tests.
 */

#pragma once

#include <stdint.h>

#include "display.h"


/**
 * @class MockDisplay
 * @brief Implements Display without hardware, recording every call so
 * tests can assert on the display choreography (init/clear/displayTime).
 */
class MockDisplay : public Display {
public:
  void init () override {
    init_count_++;
    initialized_ = true;
  }

  void clear () override {
    clear_count_++;
  }

  void displayTime (uint16_t hours, uint8_t minutes, uint8_t seconds) override {
    display_count_++;
    last_hh_ = hours;
    last_mm_ = minutes;
    last_ss_ = seconds;
  }

  /// Zeroes all mock state and call counters.
  void reset () {
    initialized_ = false;
    init_count_ = 0;
    clear_count_ = 0;
    display_count_ = 0;
    last_hh_ = 0;
    last_mm_ = 0;
    last_ss_ = 0;
  }

  bool initialized () const { return initialized_; }
  int initCount () const { return init_count_; }
  int clearCount () const { return clear_count_; }
  int displayCount () const { return display_count_; }

  uint16_t lastHours () const { return last_hh_; }
  uint8_t lastMinutes () const { return last_mm_; }
  uint8_t lastSeconds () const { return last_ss_; }

private:
  bool initialized_ = false;
  int init_count_ = 0;
  int clear_count_ = 0;
  int display_count_ = 0;
  uint16_t last_hh_ = 0;
  uint8_t last_mm_ = 0;
  uint8_t last_ss_ = 0;
};