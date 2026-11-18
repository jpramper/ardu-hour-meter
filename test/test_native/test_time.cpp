// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file test_time.cpp
 * @brief Unit tests for the Time class, run against MockStorage.
 */

#include <unity.h>

#include "time.h"
#include "mock_storage.h"


void test_time_load_reads_from_storage (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(123, 45, 59);
  time.load();

  TEST_ASSERT_EQUAL_UINT16(123, time.hours());
  TEST_ASSERT_EQUAL_UINT8(45, time.minutes());
  TEST_ASSERT_EQUAL_UINT8(59, time.seconds());
  TEST_ASSERT_EQUAL_INT(1, storage.loadCount());
}


void test_time_save_writes_to_storage (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(10, 20, 30);
  time.load();
  time.save();

  TEST_ASSERT_EQUAL_UINT16(10, storage.lastSavedHours());
  TEST_ASSERT_EQUAL_UINT8(20, storage.lastSavedMinutes());
  TEST_ASSERT_EQUAL_UINT8(30, storage.lastSavedSeconds());
  TEST_ASSERT_EQUAL_INT(1, storage.saveCount());
}


void test_time_reset_zeroes_time_and_saves (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(10, 20, 30);
  time.load();
  time.reset();

  TEST_ASSERT_EQUAL_UINT16(0, time.hours());
  TEST_ASSERT_EQUAL_UINT8(0, time.minutes());
  TEST_ASSERT_EQUAL_UINT8(0, time.seconds());
  TEST_ASSERT_EQUAL_INT(1, storage.saveCount());
  TEST_ASSERT_EQUAL_UINT16(0, storage.lastSavedHours());
  TEST_ASSERT_EQUAL_UINT8(0, storage.lastSavedMinutes());
  TEST_ASSERT_EQUAL_UINT8(0, storage.lastSavedSeconds());
}


void test_time_tick_increments_seconds (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(0, 0, 0);
  time.load();
  time.tick();

  TEST_ASSERT_EQUAL_UINT8(1, time.seconds());
  TEST_ASSERT_EQUAL_INT(0, storage.saveCount());
}


void test_time_tick_rolls_over_minutes (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(0, 0, 59);
  time.load();
  time.tick();

  TEST_ASSERT_EQUAL_UINT8(0, time.seconds());
  TEST_ASSERT_EQUAL_UINT8(1, time.minutes());
  TEST_ASSERT_EQUAL_UINT16(0, time.hours());
}


void test_time_tick_rolls_over_hours (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(5, 59, 59);
  time.load();
  time.tick();

  TEST_ASSERT_EQUAL_UINT16(6, time.hours());
  TEST_ASSERT_EQUAL_UINT8(0, time.minutes());
  TEST_ASSERT_EQUAL_UINT8(0, time.seconds());
}


void test_time_tick_saves_on_interval (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(0, 0, 14);
  time.load();
  time.tick(); // seconds -> 15, 15 % 15 == 0

  TEST_ASSERT_EQUAL_INT(1, storage.saveCount());
  TEST_ASSERT_EQUAL_UINT8(15, storage.lastSavedSeconds());
}


void test_time_tick_does_not_save_off_interval (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(0, 0, 15);
  time.load();
  time.tick(); // seconds -> 16, 16 % 15 != 0

  TEST_ASSERT_EQUAL_INT(0, storage.saveCount());
}


void test_time_tick_saves_on_seconds_rollover (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(0, 0, 59);
  time.load();
  time.tick(); // seconds -> 0, 0 % 15 == 0

  TEST_ASSERT_EQUAL_INT(1, storage.saveCount());
}


void test_time_tick_saves_every_interval_over_minute (void) {
  MockStorage storage;
  Time time(storage);

  storage.setStored(0, 0, 0);
  time.load();

  // 60 ticks: seconds lands on 15, 30, 45 and 0.
  for (int i = 0; i < 60; i++) {
    time.tick();
  }

  TEST_ASSERT_EQUAL_INT(4, storage.saveCount());
  TEST_ASSERT_EQUAL_UINT8(0, time.seconds());
  TEST_ASSERT_EQUAL_UINT8(1, time.minutes());
}


void test_time_tick_respects_custom_save_interval (void) {
  MockStorage storage;
  Time time(storage, 10);

  storage.setStored(0, 0, 9);
  time.load();
  time.tick(); // seconds -> 10, 10 % 10 == 0

  TEST_ASSERT_EQUAL_INT(1, storage.saveCount());
}