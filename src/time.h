// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file time.h
 * @brief Time class.
 */

 #include <stdint.h>
 #include "storage.h"

class Time {
public:
  explicit Time (Storage& storage, uint8_t save_interval = 15);

  /**
   * @brief Obtains time from storage and updates instance time with it.
   */
  void load();

  /**
   * @brief Persists instance time on storage.
   */
  void save();

  /**
   * @brief Zeroes instance time and resets storage as well.
   */
  void reset();

  /**
   * @brief Adds a second to the instance time. Also triggers a save to 
   * storage EEPROM if the new second matches the save_interval_.
   */
  void tick ();

private:
  /// Storage implementation for this time instance.
  Storage& storage_;

  /// 0 - 65535 hours
  volatile uint16_t hours_;

  /// 0 - 60 minutes
  volatile uint8_t minutes_;

  /// 0 - 60 seconds
  volatile uint8_t seconds_;

  /// Interval of time to persist time to storage, in seconds.
  uint8_t save_interval_;
};
