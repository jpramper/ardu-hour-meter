// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <stdint.h>

#include "eeprom.h"
#include <EEPROM.h>


namespace {
  /**
   * @brief Eeprom address calculation util for minutes.
   * 
   * @param [in] base_address Base address of hours according to EepromStorage.
   * @param [in] hours Hours to base address of.
   * 
   * Minutes is written & fetched from an address defined by the hours:
   * base_address is added to the current modulo 60 of hours to determine 
   * target address.
   */
  uint8_t getMinutesAddress (uint8_t minutes_base_address, uint16_t hours) {
    return minutes_base_address + (hours % 60);
  }

  /**
   * @brief Eeprom address calculation util for seconds.
   * 
   * @param [in] base_address Base address of minutes according to 
   * EepromStorage.
   * @param [in] minutes Minutes to calculate address with.
   * 
   * Seconds is written & fetched from an address defined by the minutes.
   */
  uint8_t getSecondsAddress (uint8_t seconds_base_address, uint8_t minutes) {
    return seconds_base_address + minutes;
  }
}

EepromStorage::EepromStorage (
    uint8_t address_hours, 
    uint8_t address_minutes,
    uint8_t address_seconds)
    : address_hours_(address_hours), 
    address_minutes_(address_minutes), 
    address_seconds_(address_seconds) {}

/**
 * If eeprom_eady_ address is not written, it zeroes all hour/minute/second 
 * addresses as well as EEPR_RDY.
 */
void EepromStorage::init () {
  uint8_t init = EEPROM.read(eeprom_eady_);

  if (init != 0) {
    EEPROM.write(eeprom_eady_, 0); // signal EEPROM initialized

    uint16_t two_byte_zero = 0; // init hour addresses
    EEPROM.put(address_hours_, two_byte_zero);

    for (int i = 0; i <= 60; i++) { // init minute addresses
      EEPROM.put(address_minutes_ + i, 0);
    }
    
    for (int i = 0; i <= 60; i++) { // init second addresses
      EEPROM.put(address_seconds_ + i, 0);
    }
  }
}

void EepromStorage::loadTime (
  volatile uint16_t& hours, 
  volatile uint8_t& minutes, 
  volatile uint8_t& seconds
) {
  uint16_t hh = 0; // get cannot directly save to a volatile, must use temp
  EEPROM.get(address_hours_, hh); 
  hours = hh;

  minutes = EEPROM.read(getMinutesAddress(address_minutes_, hours));
  seconds = EEPROM.read(getSecondsAddress(address_seconds_, minutes));
}

void EepromStorage::saveTime (uint16_t hours, uint8_t minutes, uint8_t seconds) {
  EEPROM.put(address_hours_, hours);
  EEPROM.update(getMinutesAddress(address_minutes_, hours), minutes);
  EEPROM.update(getSecondsAddress(address_seconds_, minutes), seconds);
}
