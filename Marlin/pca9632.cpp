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
 * Driver for the Philips PCA9632 LED driver.
 * Written by Robert Mendon Feb 2017.
 */

#include "MarlinConfig.h"

#if ENABLED(PCA9632)

#include "pca9632.h"
#include "leds.h"
#include <Wire.h>

//#define PCA9632_MODE1_VALUE   0b00000001 //(ALLCALL) //GGE
//#define PCA9632_MODE2_VALUE   0b00010101 //(DIMMING, INVERT, CHANGE ON STOP,TOTEM) //GGE
//#define PCA9632_LEDOUT_VALUE  0b00101010 //GGE

/* Register addresses */
//#define PCA9632_MODE1       0x80 //GGE
//#define PCA9632_MODE2       0x1C //GGE
//#define PCA9632_PWM0        0x02 //GGE
//#define PCA9632_PWM1        0x03 //GGE
//#define PCA9632_PWM2        0x04 //GGE
//#define PCA9632_PWM3        0x05 //GGE
//#define PCA9632_GRPPWM      0xFF //GGE
//#define PCA9632_GRPFREQ     0x00 //GGE
//#define PCA9632_LEDOUT      0xAA //GGE
//#define PCA9632_SUBADR1     0x09 //GGE
//#define PCA9632_SUBADR2     0x0A //GGE
//#define PCA9632_SUBADR3     0x0B //GGE
//#define PCA9632_ALLCALLADDR 0x0C //GGE

//#define PCA9632_NO_AUTOINC  0x00 //GGE
//#define PCA9632_AUTO_ALL    0x80 //GGE
//#define PCA9632_AUTO_IND    0xA0 //GGE
//#define PCA9632_AUTOGLO     0xC0 //GGE
//#define PCA9632_AUTOGI      0xE0 //GGE

// Red   LED0
// Green LED1
// Blue  LED2
#define PCA9632_RED     0x03 //GGE
#define PCA9632_GRN     0x02 //GGE
#define PCA9632_BLU     0x04 //GGE

//#define LED_OFF   0x00 //GGE
//#define LED_ON    0x01 //GGE
#define LED_PWM   0x00 //GGE

#define OVLCTRL_ADDRESS 0b1100000 // GGE Adress from Dreammaker Source

//byte PCA_init = 0;

/*static void PCA9632_WriteRegister(const byte addr, const byte regadd, const byte value) {
  Wire.beginTransmission(addr);
  Wire.write(regadd);
  Wire.write(value);
  Wire.endTransmission();
}*/ //GGE

static void PCA9632_WriteAllRegisters(const byte addr, const byte regadd, const byte value1, const byte value2, const byte value3) {
  Wire.beginTransmission(addr);
  //Wire.write(PCA9632_AUTO_IND | regadd); //GGE
  Wire.write(PCA9632_RED); // RED GGE 03.01.19
  Wire.write(value1);
  Wire.write(PCA9632_GRN); // GREEN GGE 03.01.19
  Wire.write(value2);
  Wire.write(PCA9632_BLU); // BLUE GGE 03.01.19
  Wire.write(value3);
  Wire.endTransmission();
}

#if 0
  static byte PCA9632_ReadRegister(const byte addr, const byte regadd) {
    Wire.beginTransmission(addr);
    Wire.write(regadd);
    const byte value = Wire.read();
    Wire.endTransmission();
    return value;
  }
#endif

void pca9632_set_led_color(const LEDColor &color) {
  Wire.begin();
  /*if (!PCA_init) {
    PCA_init = 1;
    PCA9632_WriteRegister(PCA9632_ADDRESS,PCA9632_MODE1, PCA9632_MODE1_VALUE);
    PCA9632_WriteRegister(PCA9632_ADDRESS,PCA9632_MODE2, PCA9632_MODE2_VALUE);
  }*/ // GGE

  /*const byte LEDOUT = (color.r ? LED_PWM << PCA9632_RED : 0)
                    | (color.g ? LED_PWM << PCA9632_GRN : 0)
                    | (color.b ? LED_PWM << PCA9632_BLU : 0);
*/
  PCA9632_WriteAllRegisters(OVLCTRL_ADDRESS,LED_PWM,color.r, color.g, color.b);
  //PCA9632_WriteRegister(PCA9632_ADDRESS,PCA9632_LEDOUT, LEDOUT); /GGE
}

#endif // PCA9632
