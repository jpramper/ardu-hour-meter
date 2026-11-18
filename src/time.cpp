// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>

#include "time.h"


Time::Time (Storage& storage, uint8_t save_interval) 
  : storage_(storage), save_interval_(save_interval) {}


void Time::load () {
  storage_.loadTime(hours_, minutes_, seconds_);
}


void Time::save () {
  storage_.saveTime(hours_, minutes_, seconds_);
}


void Time::reset () {
  hours_ = 0;
  minutes_ = 0;
  seconds_ = 0;
  save();
}


void Time::tick () {
  bool tickMinutes = false;
  bool tickHours = false;

  // tick seconds
  if (++seconds_ >= 60) {
    seconds_ = 0;
    tickMinutes = true;
  }

  // if seconds overflowed, tick minutes
  if (tickMinutes) {
    if (++minutes_ >= 60) {
      minutes_ = 0;
      tickHours = true;
    }
  }

  // if minutes overflowed, tick hours
  if (tickHours) hours_ += 1;

  // save time every interval
  if (seconds_ % save_interval_ == 0) save();
}
