// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file constants.h
 * @brief Program-wide constants
 */

#pragma once

#include <stdint.h>


// ===== EEPROM =================================

/// @brief Interval for saving elapsed time to EEPROM, in seconds.
constexpr uint8_t SAVE_INTERVAL = 15;

/** 
 * @brief EEPROM initialization flag address
 * 
 * This will be set to 0 after first boot to signal EEPROM has been written
 * for the first time and can be used to retrieve elapsed time. 
 */
constexpr uint8_t EEPR_RDY = 0;

/// EEPROM address for hours
constexpr uint8_t HH_ADDR = 10; // NOTE: 2 bytes needed for hours

/**
 * @brief EEPROM address start (lower end) for minutes
 * 
 * The current (hour mod 60) will be added to this to calculate seconds address.
 * This grants 60 addresses for minutes, lowering write cycles to addresses.
 */ 
constexpr uint8_t MM_ADDR_STRT = 20;

/**
 * @brief EEPROM address start (lower end) for seconds
 * 
 * The current minute will be added to this to calculate seconds address.
 * This grants 60 addresses for seconds, lowering write cycles to addresses.
 */ 
constexpr uint8_t SS_ADDR_STRT = 100;


// ===== DISPLAY =================================

/// Arduino pin driving the data (DIN) input.
constexpr int DATA_PIN = 12;

/// Arduino pin driving the clock (CLK) input.
constexpr int CLK_PIN = 10;

/// Arduino pin driving the chip select (CS) input.
constexpr int CS_PIN = 11;

/// Number of MAX7219 devices cascaded.
constexpr int NUM_DEVICES = 1;

/// Address of the main MAX7219 device on the cascade.
constexpr int DISPLAY_ADDRESS = 0;

/// Segment A where MAX7219 digits are HGFEDCBA
constexpr uint8_t SEGMENT_A = 0;
/// Segment B where MAX7219 digits are HGFEDCBA
constexpr uint8_t SEGMENT_B = 1;
/// Segment C where MAX7219 digits are HGFEDCBA
constexpr uint8_t SEGMENT_C = 2;
/// Segment D where MAX7219 digits are HGFEDCBA
constexpr uint8_t SEGMENT_D = 3;
/// Segment E where MAX7219 digits are HGFEDCBA
constexpr uint8_t SEGMENT_E = 4;
/// Segment F where MAX7219 digits are HGFEDCBA
constexpr uint8_t SEGMENT_F = 5;
/// Segment G where MAX7219 digits are HGFEDCBA
constexpr uint8_t SEGMENT_G = 6;
/// Segment H where MAX7219 digits are HGFEDCBA
constexpr uint8_t SEGMENT_H = 7;


// ===== BUTTON =================================

/// Arduino pin receiving the button input.
constexpr int RESET_BUTTON_PIN = 2;

/// Miliseconds to wait before allowing another button interrupt.
constexpr int BUTTON_DEBOUNCE_DELAY = 200;
