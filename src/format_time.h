// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file format_time.h
 * @brief Time formatting support functionality.
 */

#pragma once

#include <stdint.h>
#include <vector>


/// Represents a segment position in a display. 
struct Segment {
  int digit;
  char character;
};


/**
 * @brief For a given time, returns an array of 8 segments as HHHHH-MM where 
 * HHHHH are hours and MM minutes of current hour. Turns on '-' segment in 
 * even seconds, ' ' in odd seconds.
 * 
 * @param [in] hours Hours (0-65535)
 * @param [in] minutes Minutes (0-60)
 * @param [in] seconds Seconds (0-60)
 */
std::vector<Segment> formatTime (
  uint16_t hours, 
  uint8_t minutes, 
  uint8_t seconds
);
