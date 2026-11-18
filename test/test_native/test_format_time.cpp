// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "format_time.h"


void test_formatTime_blinks_seconds (void) {
  std::vector<Segment> out(8);

  out = formatTime(0, 0, 0);
  TEST_ASSERT_EQUAL_CHAR('-', out[2].character);
  
  out = formatTime(0, 0, 1);
  TEST_ASSERT_EQUAL_CHAR(' ', out[2].character);

  out = formatTime(0, 0, 58);
  TEST_ASSERT_EQUAL_CHAR('-', out[2].character);
}

void test_formatTime_splits_digits (void) {
  std::vector<Segment> out(8);

  out = formatTime(1234, 56, 0);
  
  TEST_ASSERT_EQUAL_INT(6, out[0].digit);
  TEST_ASSERT_EQUAL_INT(5, out[1].digit);
  
  TEST_ASSERT_EQUAL_INT(4, out[3].digit);
  TEST_ASSERT_EQUAL_INT(3, out[4].digit);
  TEST_ASSERT_EQUAL_INT(2, out[5].digit);
  TEST_ASSERT_EQUAL_INT(1, out[6].digit);
  TEST_ASSERT_EQUAL_INT(0, out[7].digit);
}