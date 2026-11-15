// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file logic.h
 * @brief Time logic functionality and runtime time variables.
 */

#pragma once

#include <stdint.h>


/// 0 - 65535 hours
extern volatile uint16_t HOURS;

/// 0 - 60 minutes
extern volatile uint8_t MINUTES;

/// 0 - 60 seconds
extern volatile uint8_t SECONDS;


/// Zeroes EEPROM adresses defined in constants.h.
void initEprom ();

/**
 * @brief Loads elapsed time from EEPROM to runtime memory.
 * 
 * @param [out] hours Variable to save hours into.
 * @param [out] minutes Variable to save minutes into.
 * @param [out] seconds Variable to save seconds into.
 */
void loadTime (
  volatile uint16_t& hours, 
  volatile uint8_t& minutes, 
  volatile uint8_t& seconds
);

/**
 * @brief Saves elapsed time from EEPROM to runtime memory.
 * 
 * @param [in] hours Hours (0-65535)
 * @param [in] minutes Minutes (0-60)
 * @param [in] seconds Seconds (0-60)
 */
void saveTime (uint16_t hh, uint8_t mm, uint8_t ss);

/**
 * @brief Adds a second to the received time, saving it to the received 
 * variables. Also triggers a save to EEPROM if the new second matches the 
 * SAVE_INTERVAL defined in constants.h.
 * 
 * @param [out] hours Variable to save hours into.
 * @param [out] minutes Variable to save minutes into.
 * @param [out] seconds Variable to save seconds into.
 */
void tick (
  volatile uint16_t& hours, 
  volatile uint8_t& minutes, 
  volatile uint8_t& seconds
);
