// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <vector>

#include "format_time.h"


namespace {
  /// Segment creator for digits.
  Segment digit (uint8_t d) {
    return Segment{d, ' '};
  }

  /// Segment creator for characters. 
  Segment character (char c) {
    return Segment{0, c};
  }
}


std::vector<Segment> formatTime (
  uint16_t hours, 
  uint8_t minutes, 
  uint8_t seconds
) {
  std::vector<Segment> out(8);

  out[0] = digit(minutes > 0 ? ( minutes % 10 ) : 0);
  out[1] = digit(minutes >= 10 ? ( (minutes / 10) % 10 ) : 0);
  out[2] = character(seconds % 2 == 0 ? '-' : ' ');
  out[3] = digit(hours > 0 ? (hours % 10) : 0);
  out[4] = digit(hours > 10 ? ((hours / 10) % 10) : 0);
  out[5] = digit(hours > 100 ? ((hours / 100) % 10) : 0);
  out[6] = digit(hours >= 1000 ? ((hours / 1000) % 10) : 0);
  out[7] = digit(hours >= 10000 ? ((hours / 10000) % 10) : 0);

  return out;
}