// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <EEPROM.h>

#include "logic.h"
#include "constants.h"


/// 0-65535 hours
volatile uint16_t HOURS = 0;

/// 0-60 minutes
volatile uint8_t MINUTES = 0;

/// 0-60 seconds
volatile uint8_t SECONDS = 0;


namespace {
  /**
   * @param [in] hours Hours to base address of.
   * 
   * Minutes is written & fetched from an address defined by the hours:
   * constants.h/MM_ADDR_STRT is added to the current (hour mod 60) to 
   * determine target address.
   */
  uint8_t getMinutesAddress (uint16_t hours) {
    return MM_ADDR_STRT + (hours % 60);
  }

  /**
   * @param [in] minutes Minutes to base address of.
   * 
   * Seconds is written & fetched from an address defined by the minutes:
   * constants.h/SS_ADDR_STRT is added to the current minute to determine 
   * target address.
   */
  uint8_t getSecondsAddress (uint8_t minutes) {
    return SS_ADDR_STRT + minutes;
  }
}


/**
 * If constants.h/EEPR_RDY EEPROM address is not written, 
 * it zeroes all hour/minute/second addresses as well as EEPR_RDY.
 */
void initEprom () {
  uint8_t init = EEPROM.read(EEPR_RDY);

  if (init != 0) {
    EEPROM.write(EEPR_RDY, 0); // signal EEPROM initialized

    uint16_t two_byte_zero = 0; // init hour addresses
    EEPROM.put(HH_ADDR, two_byte_zero);

    for (int i = 0; i <= 60; i++) { // init minute addresses
      EEPROM.put(MM_ADDR_STRT + i, 0);
    }
    
    for (int i = 0; i <= 60; i++) { // init second addresses
      EEPROM.put(SS_ADDR_STRT + i, 0);
    }
  }
}

void loadTime (
  volatile uint16_t& hours, 
  volatile uint8_t& minutes, 
  volatile uint8_t& seconds
) {
  uint16_t hh = 0; // get cannot save to a volatile, must use temp
  EEPROM.get(HH_ADDR, hh); 
  hours = hh;

  minutes = EEPROM.read(getMinutesAddress(hours));
  seconds = EEPROM.read(getSecondsAddress(minutes));
}

void saveTime (uint16_t hours, uint8_t minutes, uint8_t seconds) {
  EEPROM.put(HH_ADDR, hours);
  EEPROM.update(getMinutesAddress(hours), minutes);
  EEPROM.update(getSecondsAddress(minutes), seconds);
}

void tick (
  volatile uint16_t& hours, 
  volatile uint8_t& minutes, 
  volatile uint8_t& seconds
) { 
  bool tickMinutes = false;
  bool tickHours = false;

  // tick seconds
  if (++seconds >= 60) {
    seconds = 0;
    tickMinutes = true;
  }

  // if seconds overflowed, tick minutes
  if (tickMinutes) {
    if (++minutes >= 60) {
      minutes = 0;
      tickHours = true;
    }
  }

  // if minutes overflowed, tick hours
  if (tickHours) hours += 1;

  // save time every interval
  if (seconds % SAVE_INTERVAL == 0) saveTime(hours, minutes, seconds);
}
