//DECLARATIONS ONLY, include in main and where function is defined
#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

struct Btn{
  int pin;
  int state;
  int last_state;
};

void buttonCheck(Btn & btn, int & led_state);

#endif