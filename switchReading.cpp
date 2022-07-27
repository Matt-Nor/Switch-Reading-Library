/*
  switchReading.cpp - source file for reading inputs from switches
  Author: Matt Norman

  MIT License

  Copyright (c) 2022 Matt Norman

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
 */

#if defined (ARDUINO_AVR_MEGA2560)
#include "switchReading.h"

/**
 *  Constructor class.
 */

switchReading::switchReading (){
}

/**
 *  initalize buttons
 */

void switchReading::switchSetup(){
for (int i = 0; i < SWITCH_COUNT; i++) {
    // Define the switch circuit type - circuit_type is:
    // circuit_C1 (INPUT) or circuit_C2 (INPUT_PULLUP)
    pinMode(switches[i].switch_pin, switches[i].circuit_type);
    // Establish 'meaning' for switch on/off for a button switch, depending on circuit type.
    // This is used only by button read function, it has no relevance for toggle switches.
    if (switches[i].circuit_type == CIRCUIT_C2) {
      // Switch is NOT configured with a pull down switch resistor
      switches[i].switch_on_value = LOW;  // switch pin goes LOW when switch pressed, ie on
    } else {
      // Circuit_type_C1, so switch IS configured with a pull down switch resistor
      switches[i].switch_on_value = HIGH;  // switch pin goes HIGH when switch pressed, ie on
    }
  }
}

/**
 *  read button input
 */
bool switchReading::read_switch(uint8_t sw){
if (switches[sw].switch_type == BUTTON_SWITCH) {
    return read_button_switch(sw);
  }
  return read_toggle_switch(sw);
}

/**
 *  toggle switch input 
 */

bool switchReading::read_toggle_switch(uint8_t sw){
int pin_value = digitalRead(switches[sw].switch_pin);  // test current state of toggle pin
  if (switches[sw].circuit_type == CIRCUIT_C2) {
    // Need to invert HIGH/LOW if circuit design sets pin HIGH representing switch in off state
    // ie inititialised as INPUT_PULLUP
    pin_value = !pin_value;
  }
  if (pin_value != switches[sw].switch_status && !switches[sw].switch_pending) {
    // Switch change detected so start debounce cycle
    switches[sw].switch_pending = true;
    switches[sw].elapse_timer = millis();  // set start of debounce timer
  } else {
    if (switches[sw].switch_pending) {
      // We are in the switch transition cycle so check if debounce period has elapsed
      if (millis() - switches[sw].elapse_timer >= DEBOUNCE) {
        // Debounce period elapse so assume switch has settled down after transition
        switches[sw].switch_status = !switches[sw].switch_status;  // flip status
        switches[sw].switch_pending = false;                       // cease transition cycle
        return SWITCHED;
      }
    }
  }
  return !SWITCHED;
}

/**
 *  button switch input 
 */

bool switchReading::read_button_switch(uint8_t sw){
int switch_pin_reading;
  switch_pin_reading = digitalRead(switches[sw].switch_pin);
  if (switch_pin_reading == switches[sw].switch_on_value && !switches[sw].switch_pending) {
    // Switch is pressed (ON), so start/restart debounce process
    switches[sw].elapse_timer = millis();
    switches[sw].switch_pending = true;

    return SWITCHED;  // now waiting for debounce to conclude
  }
  if (switches[sw].switch_pending) {
    // Switch was pressed, now released (OFF), so check if debounce time elapsed
    if (millis() - switches[sw].elapse_timer > DEBOUNCE) {
      // dounce time elapsed, so switch press cycle complete
      switches[sw].switch_pending = false;
      return !SWITCHED;
    }
  }

  return !SWITCHED;
}

uint16_t switchReading::pollSwitches(){
uint16_t msg = 0;

  for (int sw = 0; sw < SWITCH_COUNT; sw++) {
    if (read_switch(sw) == SWITCHED) {
      msg = ((uint16_t)switches[0].switch_status << 8) | ((uint8_t)switches[sw].switch_pin);
    }
  }
  return msg;
}
#endif