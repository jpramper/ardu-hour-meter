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
   * @brief Clear display contents.
   */
  virtual void clear () = 0;

  /**
   * @brief Presents the time values on the display.
   * 
   * @param [in] hours Hours to display.
   * @param [in] minutes Minutes to display.
   * @param [in] seconds Seconds to display.
   */
  virtual void displayTime (
    uint16_t hours, 
    uint8_t minutes, 
    uint8_t seconds) = 0;
};
