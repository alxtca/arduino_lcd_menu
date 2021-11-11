//VARIABLES AND CONSTANTS, include in main
#include <Arduino.h>
#include "button.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#ifndef VARIABLES_H
#define VARIABLES_H

// Define LCD pinout
inline constexpr int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
// Define I2C Address - change if reqiuired
inline constexpr int i2c_addr = 0x27;
inline LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

//menu items
const char main_menu[][16] = {
  "Play Game",
  "Play Music"
};

//BUTTONS
inline Btn btn1 = {18, LOW}; //select
inline Btn btn2 = {2, LOW}; //menu down
inline Btn btn3 = {3, LOW}; //menu up

//LEDs
const int led_pin = 22;
inline int led_state = HIGH;

#endif