// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file display.h
 * @brief MAX7219 display control functionality.
 */

#pragma once

#include <stdint.h>
#include <LedControl.h>

#include "format_time.h"


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
 * Displays received time on MAX7219 display.
 */
void displayTime (std::vector<Segment> segments);
