// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file test_storage.cpp
 * @brief Contract tests for the Storage interface, exercised through
 * MockStorage. The real EepromStorage is AVR-bound and cannot run natively;
 * these tests pin down the behaviour every Storage implementation (and the
 * mock itself) must uphold.
 */

#include <unity.h>

#include "mock_storage.h"


void test_storage_load_returns_stored_values (void) {
  MockStorage storage;
  storage.setStored(12, 34, 56);

  volatile uint16_t hours = 0;
  volatile uint8_t minutes = 0;
  volatile uint8_t seconds = 0;
  storage.loadTime(hours, minutes, seconds);

  TEST_ASSERT_EQUAL_UINT16(12, hours);
  TEST_ASSERT_EQUAL_UINT8(34, minutes);
  TEST_ASSERT_EQUAL_UINT8(56, seconds);
  TEST_ASSERT_EQUAL_INT(1, storage.loadCount());
}


void test_storage_save_then_load_roundtrip (void) {
  MockStorage storage;
  storage.saveTime(100, 20, 30);

  volatile uint16_t hours = 0;
  volatile uint8_t minutes = 0;
  volatile uint8_t seconds = 0;
  storage.loadTime(hours, minutes, seconds);

  TEST_ASSERT_EQUAL_UINT16(100, hours);
  TEST_ASSERT_EQUAL_UINT8(20, minutes);
  TEST_ASSERT_EQUAL_UINT8(30, seconds);
}


void test_storage_save_records_last_saved_values (void) {
  MockStorage storage;
  storage.saveTime(7, 8, 9);

  TEST_ASSERT_EQUAL_UINT16(7, storage.lastSavedHours());
  TEST_ASSERT_EQUAL_UINT8(8, storage.lastSavedMinutes());
  TEST_ASSERT_EQUAL_UINT8(9, storage.lastSavedSeconds());
  TEST_ASSERT_EQUAL_INT(1, storage.saveCount());
}


void test_storage_init_zeroes_stored_values (void) {
  MockStorage storage;
  storage.setStored(1, 2, 3);

  storage.init();

  TEST_ASSERT_EQUAL_UINT16(0, storage.storedHours());
  TEST_ASSERT_EQUAL_UINT8(0, storage.storedMinutes());
  TEST_ASSERT_EQUAL_UINT8(0, storage.storedSeconds());
  TEST_ASSERT_EQUAL_INT(1, storage.initCount());
}