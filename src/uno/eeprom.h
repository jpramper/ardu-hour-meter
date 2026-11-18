// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file eeprom.h
 * @brief Defines Storage implementation EepromStorage.
 */

#pragma once

#include <stdint.h>

#include "storage.h"


/**
 * @class EepromStorage
 * @brief Implements storage to provide access to Arduino Uno's EEPROM storage.
 */
class EepromStorage : public Storage {
public:
  EepromStorage (
    uint8_t address_hours = 10, 
    uint8_t address_minutes = 20,
    uint8_t address_seconds = 100);

  void init () override;

  void saveTime (
    const uint16_t hours, 
    const uint8_t minutes, 
    const uint8_t seconds) override;

  void loadTime (
    volatile uint16_t& hours, 
    volatile uint8_t& minutes, 
    volatile uint8_t& seconds) override;

private:
  /** 
   * @brief EEPROM initialization flag address
   * 
   * This will be set to 0 after first boot to signal EEPROM has been written
   * for the first time and can be used to retrieve elapsed time. 
   */
  uint8_t eeprom_eady_ = 0;

  /// EEPROM address for hours
  uint8_t address_hours_; // NOTE: 2 bytes needed for hours

  /**
   * @brief EEPROM address start (lower end) for minutes
   * 
   * The current (hour mod 60) will be added to this to calculate seconds address.
   * This grants 60 addresses for minutes, lowering write cycles to addresses.
   */ 
  uint8_t address_minutes_;

  /**
   * @brief EEPROM address start (lower end) for seconds
   * 
   * The current minute will be added to this to calculate seconds address.
   * This grants 60 addresses for seconds, lowering write cycles to addresses.
   */ 
  uint8_t address_seconds_;
};
