// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file display.h
 * @brief Defines abstract class Display.
 */

#pragma once

#include <stdint.h>

/**
 * @class Display
 * @brief Abstract class representing any display device.
 */
class Display {
public:
  /**
   * @brief Standard virtual destructor.
   */
  virtual ~Display () = default;

  /**
   * @brief Display initialization routine.
   */
  virtual void init () = 0;

  /**
   * @brief Method to clear display contents.
   */
  virtual void clear () = 0;

  /**
   * @brief Presents the time values on the display.
   * 
   * @param [out] hours Variable to save hours into.
   * @param [out] minutes Variable to save minutes into.
   * @param [out] seconds Variable to save seconds into.
   */
  virtual void displayTime (uint16_t hh, uint8_t mm, uint8_t ss) = 0;
};
