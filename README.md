# ardu-hour-meter

An arduino-based hour meter for a shop compressor designed around a MAX7219 8-digit 7-segment display module.

The meter is wired to the compressor motor; elapsed time is constantly saved to EEPROM and retrieved on boot while also being displayed by the MAX7219.

Also provides a button interrupt to reset counter to 0.


## Hardware Requirements

- 1x Arduino Nano
- 1x MAX7219 8-digit (dual 4-digit) 7-segment display
- 1x button


## Local Development Environment Setup
Project is setup for platformio, if on vscode, install platformio extension and init with it.
