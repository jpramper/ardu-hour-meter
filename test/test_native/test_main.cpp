// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

/**
 * @file test_main.cpp
 * @brief Single entry point for the native test program.
 *
 * PlatformIO links every test file of the test_native group into one
 * program, so all test cases from all files are registered here.
 */

#include <unity.h>


// test_format_time.cpp
void test_formatTime_blinks_seconds(void);
void test_formatTime_splits_digits(void);

// test_time.cpp
void test_time_load_reads_from_storage(void);
void test_time_save_writes_to_storage(void);
void test_time_reset_zeroes_time_and_saves(void);
void test_time_tick_increments_seconds(void);
void test_time_tick_rolls_over_minutes(void);
void test_time_tick_rolls_over_hours(void);
void test_time_tick_saves_on_interval(void);
void test_time_tick_does_not_save_off_interval(void);
void test_time_tick_saves_on_seconds_rollover(void);
void test_time_tick_saves_every_interval_over_minute(void);
void test_time_tick_respects_custom_save_interval(void);

// test_storage.cpp
void test_storage_load_returns_stored_values(void);
void test_storage_save_then_load_roundtrip(void);
void test_storage_save_records_last_saved_values(void);
void test_storage_init_zeroes_stored_values(void);

// test_display.cpp
void test_display_init_marks_initialized(void);
void test_display_clear_is_recorded(void);
void test_display_displayTime_records_last_time(void);


int main(int argc, char** argv) {
  UNITY_BEGIN();

  RUN_TEST(test_formatTime_blinks_seconds);
  RUN_TEST(test_formatTime_splits_digits);

  RUN_TEST(test_time_load_reads_from_storage);
  RUN_TEST(test_time_save_writes_to_storage);
  RUN_TEST(test_time_reset_zeroes_time_and_saves);
  RUN_TEST(test_time_tick_increments_seconds);
  RUN_TEST(test_time_tick_rolls_over_minutes);
  RUN_TEST(test_time_tick_rolls_over_hours);
  RUN_TEST(test_time_tick_saves_on_interval);
  RUN_TEST(test_time_tick_does_not_save_off_interval);
  RUN_TEST(test_time_tick_saves_on_seconds_rollover);
  RUN_TEST(test_time_tick_saves_every_interval_over_minute);
  RUN_TEST(test_time_tick_respects_custom_save_interval);

  RUN_TEST(test_storage_load_returns_stored_values);
  RUN_TEST(test_storage_save_then_load_roundtrip);
  RUN_TEST(test_storage_save_records_last_saved_values);
  RUN_TEST(test_storage_init_zeroes_stored_values);

  RUN_TEST(test_display_init_marks_initialized);
  RUN_TEST(test_display_clear_is_recorded);
  RUN_TEST(test_display_displayTime_records_last_time);

  return UNITY_END();
}