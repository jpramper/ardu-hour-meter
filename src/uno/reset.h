// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file reset.h
 * @brief Reset button functionality.
 */

#pragma once

/// Time 
extern volatile unsigned long LAST_TRIGGER;


/**
 * Reset button initialization: Attaches the interrupt function to the 
 * interrupt pin.
 */
void setupButtonInterrupt ();

/**
 * Resets current time and saves zeroed time to EEPROM. Also implements a 
 * debounce through timing last reset through LAST_TRIGGER.
 */
void buttonInterruptReset ();
