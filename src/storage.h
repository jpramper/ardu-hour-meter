// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file storage.h
 * @brief Defines abstract class Storage.
 */

#pragma once

#include "time.h"

/**
 * @class Storage
 * @brief Abstract class representing long-term non-volatile storage.
 */
class Storage {
public:
  /**
   * @brief Standard virtual destructor.
   */
  virtual ~Storage () = default;

  /**
   * @brief Storage initialization routine.
   */
  virtual void init () = 0;

  /**
   * @brief Stores the time values.
   * 
   * @param [in] hours Hours (0-65535)
   * @param [in] minutes Minutes (0-60)
   * @param [in] seconds Seconds (0-60)
   */
  virtual void saveTime (
    const uint16_t hours, 
    const uint8_t minutes, 
    const uint8_t seconds) = 0;

  /**
   * @brief Retrieves the time values.
   * 
   * @param [out] hours Variable to save hours into.
   * @param [out] minutes Variable to save minutes into.
   * @param [out] seconds Variable to save seconds into.
   */
  virtual void loadTime (
    volatile uint16_t& hours, 
    volatile uint8_t& minutes, 
    volatile uint8_t& seconds) = 0;
};
