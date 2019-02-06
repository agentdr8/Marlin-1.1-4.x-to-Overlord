/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Driver for the DreamMaker Overlord RGB LED 
 * Based on code by Robert Mendon Feb 2017
 * Rewritten by Georg Geraskin (ruzki) Jan 2019
 */

#include "MarlinConfig.h"

#if ENABLED(STM8S003F3_OVERLORD)

#include "stm8s003f3_OVERLORD.h"
#include "leds.h"
#include <Wire.h>

#define STM8S003F3_RED     0x03 
#define STM8S003F3_GRN     0x02 
#define STM8S003F3_BLU     0x04 

#define LED_PWM   0x00 

#define OVLCTRL_ADDRESS 0b1100000 // GGE Adress from Dreammaker Source

static void STM8S003F3_WriteAllRegisters(const byte addr, const byte regadd, const byte value1, const byte value2, const byte value3) {
  Wire.beginTransmission(addr);
  Wire.write(STM8S003F3_RED); // RED GGE 03.01.19
  Wire.write(value1);
  Wire.write(STM8S003F3_GRN); // GREEN GGE 03.01.19
  Wire.write(value2);
  Wire.write(STM8S003F3_BLU); // BLUE GGE 03.01.19
  Wire.write(value3);
  Wire.endTransmission();
}

void pca9632_set_led_color(const LEDColor &color) {
  Wire.begin();
  STM8S003F3_WriteAllRegisters(OVLCTRL_ADDRESS,LED_PWM,color.r, color.g, color.b);
}

#endif // STM8S003F3_OVERLORD
