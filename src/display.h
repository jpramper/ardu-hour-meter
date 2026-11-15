// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file display.h
 * @brief MAX7219 display control functionality.
 */

#pragma once

#include <stdint.h>
#include <LedControl.h>


// Single MAX7219 display, wired per the pins defined in constants.h.
extern LedControl lc;


/**
 * Clears all digits in MAX7219 display.
 */
void clearDisplay ();

/**
 * Powerups MAX7219 display and tests all digits.
 * Also preps onboard led for blinking.
 */
void initDisplay ();

/** Even seconds turn onboard led on, odd seconds off.
 * 
 * @param [in] seconds Seconds (0-60)
 */
void blinkOnboardLed (uint8_t seconds);

/**
 * @brief Displays received time on MAX7219 display as HHHHH-MM where HHHHH 
 * are hours and MM minutes of current hour. Turns on '-' segment on even 
 * seconds, off in odd seconds.
 * 
 * @param [in] hours Hours (0-65535)
 * @param [in] minutes Minutes (0-60)
 * @param [in] seconds Seconds (0-60)
 */
void displayTime (uint16_t hours, uint8_t minutes, uint8_t seconds);