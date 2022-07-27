/*
  switchReading.h - header file to read inputs from switches
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

#ifndef controllerLayout_h
#define controllerLayout_h

// Define circuit type used for switch
#define CIRCUIT_C1 INPUT         // switch circuit requires an external pull down 10k ohm resistor
#define CIRCUIT_C2 INPUT_PULLUP  // switch type reqires no other components beyond the button switch

// define characterisitcs of switches
#define DEBOUNCE 100  // number of millisecs to wait for a switch to settle once activated
#define SWITCHED true  // signifies switch has been pressed/switch cycle complete
#define ON true        // used for toggle switch staus
#define NOT_USED true  // helps self document code

//define switch type
#define BUTTON_SWITCH 1  
#define TOGGLE_SWITCH 2

#if defined (ARDUINO_AVR_MEGA2560)

#include "Arduino.h"
#include "controllerLayout.h"


class switchReading
{
private:
struct switch_control {
  int switch_type;                 // type of switch connected
  int switch_pin;                  // digital input pin assigned to the switch
  int circuit_type;                // the type of circuit wired to the switch
  bool switch_on_value;            // used for BUTTON SWITCHES only - defines what "on" means, set up in setup()
  bool switch_pending;             // records if switch in transition or not
  long unsigned int elapse_timer;  // records debounce timer count when associated switch is in transition
  bool switch_status;              // used for TOGGLE SWITCHES only - current state of toggle switch.
} switches[SWITCH_COUNT] = {
  // Note order of preset entries not relevant, but keep in a tidy order

  TOGGLE_SWITCH,
  CAMERA_SELECT,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,

  TOGGLE_SWITCH,
  DRIVE_POWER,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,

  TOGGLE_SWITCH,
  VIDEO_TRANSMIT_POWER,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,
  
  TOGGLE_SWITCH,
  MICROPHONE_RECORD,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,

  TOGGLE_SWITCH,
  LIGHT_POWER_RIGHT,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,

  TOGGLE_SWITCH,
  LIGHT_POWER_LEFT,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,

  TOGGLE_SWITCH,
  SHUTTER_SELECT,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,

  TOGGLE_SWITCH,
  CAMERA_POWER_RIGHT,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,

  TOGGLE_SWITCH,
  CAMERA_POWER_LEFT,
  CIRCUIT_C2,
  NOT_USED,
  false,
  0,
  !ON,

  BUTTON_SWITCH,
  APERTURE_INC,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  APERTURE_DEC,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  ISO_INC,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  ISO_DEC,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  SHUTTER_SPEED_INC,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  SHUTTER_SPEED_DEC,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  MENU,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  UP_ARROW,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  DOWN_ARROW,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  LEFT_ARROW,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  RIGHT_ARROW,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  SELECT,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  PLAY_BACK,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  TRIGGER_AF,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  SHUTTER,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  RECORD_VIDEO,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  CUSTOM_ONE,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  CUSTOM_TWO,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  CUSTOM_THREE,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,

  BUTTON_SWITCH,
  CUSTOM_FOUR,
  CIRCUIT_C2,
  LOW,
  false,
  0,
  NOT_USED,
};

public:
switchReading();
void switchSetup ();
bool read_switch (uint8_t sw);
bool read_toggle_switch (uint8_t sw);
bool read_button_switch (uint8_t sw);
uint16_t pollSwitches();

};
#endif
#endif