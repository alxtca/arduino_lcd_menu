//FUNCTION DEFINITIONS
#include <Arduino.h>
#include "button.h"

//button check should only detect state change
// then run provided function if button state did change

// & (reference) - use it to update global variables. Without "&" function will create local copy.
void runOnClick(Btn & btn, int & led_state, void(*f)()){
    // read the pushbutton input pin:
  btn.state = digitalRead(btn.pin);

  // compare the buttonState to its previous state
  if (btn.state != btn.last_state) {
    // if the state has changed, increment the counter
    if (btn.state == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      f();//RUN APPROPRIATE FUNCTION HERE
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  btn.last_state = btn.state;
}