# ardu-hour-meter

An arduino-based hour meter for a shop compressor designed around a MAX7219 8-digit 7-segment display module.

The meter is wired to the compressor motor; elapsed time is constantly saved to EEPROM and retrieved on boot while also being displayed by the MAX7219.

Also provides a button interrupt to reset counter to 0.


## Hardware Requirements

- 1x Arduino Nano
- 1x MAX7219 8-digit (dual 4-digit) 7-segment display
- 1x 10uf electrolitic capacitor
- 1x 0.1 uf ceramic capacitor
- 1x button
- 1x 10kohm resistance


## Local Development Environment Setup

Project is setup for platformio, if on vscode, install platformio extension and init with it.


## Design considerations

Current pint setup is considered for an atmega328p uno/nano (e.g. interrupt pin 2, digital output pins 10-13).

Time is saved to EEPROM every 15 seconds (defined as SAVE_INTERVAL in constants.h), where seconds and minutes are saved on 60 different addresses each. With a 100k write cycle lifespan, that's 25k hours lifetime for the EEPROM addresses being written.

Time reset button is normally LOW, interrupt is configured to detect button release (FALLING).
