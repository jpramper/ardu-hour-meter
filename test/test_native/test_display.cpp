// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file test_display.cpp
 * @brief Contract tests for the Display interface, exercised through
 * MockDisplay. The real Max7219Display is AVR-bound and cannot run natively;
 * these tests pin down the behaviour every Display implementation (and the
 * mock itself) must uphold.
 */

#include <unity.h>

#include "mock_display.h"


void test_display_init_marks_initialized (void) {
  MockDisplay display;

  TEST_ASSERT_FALSE(display.initialized());

  display.init();

  TEST_ASSERT_TRUE(display.initialized());
  TEST_ASSERT_EQUAL_INT(1, display.initCount());
}


void test_display_clear_is_recorded (void) {
  MockDisplay display;

  display.clear();
  display.clear();

  TEST_ASSERT_EQUAL_INT(2, display.clearCount());
}


void test_display_displayTime_records_last_time (void) {
  MockDisplay display;

  display.displayTime(123, 45, 59);

  TEST_ASSERT_EQUAL_INT(1, display.displayCount());
  TEST_ASSERT_EQUAL_UINT16(123, display.lastHours());
  TEST_ASSERT_EQUAL_UINT8(45, display.lastMinutes());
  TEST_ASSERT_EQUAL_UINT8(59, display.lastSeconds());
}