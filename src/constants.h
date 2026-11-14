// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file constants.h
 * @brief Program-wide constants
 */

#pragma once


// ===== DISPLAY =================================

/// Arduino pin driving the data (DIN) input.
constexpr int DATA_PIN = 11;

/// Arduino pin driving the clock (CLK) input.
constexpr int CLK_PIN = 13;

/// Arduino pin driving the chip select (CS) input.
constexpr int CS_PIN = 10;

/// Number of MAX7219 devices cascaded.
constexpr int NUM_DEVICES = 1;

/// Address of the main MAX7219 device on the cascade.
constexpr int DISPLAY_ADDRESS = 0;

/// Millisecond interval .
constexpr unsigned long DELAY_TIME_MS = 250;
