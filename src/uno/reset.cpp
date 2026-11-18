// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <Arduino.h>

#include "reset.h"


ResetButton::ResetButton (
    Time& time_instance, 
    uint8_t reset_pin, 
    uint8_t debounce_delay) 
    : time_(time_instance), 
    reset_pin_(reset_pin),
    button_debounce_delay_(debounce_delay) {
  // attach this instance to the interrupt instance pointer
  active_interrupt_ = this;
}

void ResetButton::init () {
  attachInterrupt(digitalPinToInterrupt(reset_pin_), isr, FALLING);
}

void ResetButton::reset () {
  unsigned long currentTime = millis();

  if (currentTime - last_trigger_ > button_debounce_delay_) {
    time_.reset();
    last_trigger_ = currentTime;
  }
}

void ResetButton::isr () {
  active_interrupt_ -> reset();
}
