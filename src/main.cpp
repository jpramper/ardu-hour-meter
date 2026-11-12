// Copyright 2026 Juan Pablo Ramirez
// SPDX-License-Identifier: MIT

#include "LedControl.h"

#define adress 0
LedControl lc = LedControl(11, 13, 10, 1); //(dataPin,clkPin,csPin,numDevices=1) 
unsigned long delaytime = 250;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  lc.shutdown(adress, false);
  lc.clearDisplay(adress);

  for (int i = 0; i < 8; i++) {
    lc.setRow(adress, i, B11111111);
    delay(delaytime);
  }
  lc.clearDisplay(adress);
    delay(delaytime);
}

void loop() {
  lc.setDigit(adress, 0, 1, false);
  lc.setChar(adress, 1, '-', false);
  
  delay(500);
  lc.clearDisplay(adress); 
}
