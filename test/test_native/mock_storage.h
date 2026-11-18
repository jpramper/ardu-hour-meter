// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file mock_storage.h
 * @brief In-memory Storage double for native unit tests.
 */

#pragma once

#include <stdint.h>

#include "storage.h"


/**
 * @class MockStorage
 * @brief Implements Storage with runtime memory instead of hardware.
 *
 * saveTime() writes to an in-memory state, loadTime() reads it back, and
 * init() zeroes it (a simplification of the real implementation's
 * first-boot-only behaviour). Also records call counts and the last saved
 * values so tests can assert on what was persisted.
 */
class MockStorage : public Storage {
public:
  void init () override {
    init_count_++;
    stored_hh_ = 0;
    stored_mm_ = 0;
    stored_ss_ = 0;
  }

  void saveTime (
    const uint16_t hours,
    const uint8_t minutes,
    const uint8_t seconds
  ) override {
    save_count_++;
    stored_hh_ = hours;
    stored_mm_ = minutes;
    stored_ss_ = seconds;
    last_saved_hh_ = hours;
    last_saved_mm_ = minutes;
    last_saved_ss_ = seconds;
  }

  void loadTime (
    volatile uint16_t& hours,
    volatile uint8_t& minutes,
    volatile uint8_t& seconds
  ) override {
    load_count_++;
    hours = stored_hh_;
    minutes = stored_mm_;
    seconds = stored_ss_;
  }

  /// Pre-seeds the stored state, as if a previous session had saved it.
  void setStored (uint16_t hours, uint8_t minutes, uint8_t seconds) {
    stored_hh_ = hours;
    stored_mm_ = minutes;
    stored_ss_ = seconds;
  }

  /// Zeroes all mock state and call counters.
  void reset () {
    stored_hh_ = 0;
    stored_mm_ = 0;
    stored_ss_ = 0;
    last_saved_hh_ = 0;
    last_saved_mm_ = 0;
    last_saved_ss_ = 0;
    init_count_ = 0;
    save_count_ = 0;
    load_count_ = 0;
  }

  uint16_t storedHours () const { return stored_hh_; }
  uint8_t storedMinutes () const { return stored_mm_; }
  uint8_t storedSeconds () const { return stored_ss_; }

  uint16_t lastSavedHours () const { return last_saved_hh_; }
  uint8_t lastSavedMinutes () const { return last_saved_mm_; }
  uint8_t lastSavedSeconds () const { return last_saved_ss_; }

  int initCount () const { return init_count_; }
  int saveCount () const { return save_count_; }
  int loadCount () const { return load_count_; }

private:
  /// In-memory state acting as the non-volatile medium.
  uint16_t stored_hh_ = 0;
  uint8_t stored_mm_ = 0;
  uint8_t stored_ss_ = 0;

  /// Values passed to the last saveTime() call.
  uint16_t last_saved_hh_ = 0;
  uint8_t last_saved_mm_ = 0;
  uint8_t last_saved_ss_ = 0;

  /// Call counters for assertions.
  int init_count_ = 0;
  int save_count_ = 0;
  int load_count_ = 0;
};