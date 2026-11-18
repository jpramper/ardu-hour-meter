// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file reset.h
 * @brief Defines ResetButton class.
 */

#pragma once

#include <stdint.h>

#include "time.h"

/**
 * @class ResetButton
 * @brief Provides an Arduino interrupt for a button click to reset a Time 
 * instance's time.
 */
class ResetButton {
public:
  explicit ResetButton (
    Time& time_instance, 
    uint8_t reset_pin = 2, 
    uint8_t debounce_delay = 200);

  /**
   * Reset button initialization: Attaches the interrupt function (isr()) 
   * to the interrupt pin.
   */
  void init ();

private:

  /// Time instance to reset on an interrupt.
  Time& time_;

  // Miliseconds to wait before allowing another button interrupt.
  uint8_t button_debounce_delay_;

  /// Time of last interrupt.
  volatile unsigned long last_trigger_;

  /**
   * Resets the owned Time instance's time. Also implements a debounce by 
   * timing the last reset action through last_trigger_.
   */
  void reset();

  /**
   * @brief Trampoline between arduino interrupts and reset logic.
   * 
   * Arduino's attachInterrupt requires a void (*)(), e.g. a pointer to a 
   * function that returns nothing and receives nothing (interrupt routines 
   * are pure function addresses). Member functions translate to 
   * void (Class::*)(Class* self), e.g. an address to a function in an object 
   * that includes a reference to that object. So this provides the entrypoint
   * for the interrupt, which then calls the handle (reset()). 
   */
  static void isr();
  /// current active interrupt to be referenced by isr()
  static ResetButton* active_interrupt_;
};
