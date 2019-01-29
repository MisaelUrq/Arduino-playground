#include <string.h>

#define FOR_RANGE(start_index, end_index) for (byte index = start_index; index < end_index; ++index)

const byte buttons  = 3;
const byte leds     = 4;
const byte leds_pins[leds] = {13, 12, 11, 10};
const byte buttons_pins[buttons] = {4, 3, 2};

int delta = 0.0;
const int time_switch = 28000;

enum {
  LED_RED,
  LED_GREEN,
  LED_YELLOW,
  LED_WHITE,
};

enum {
  MODE_NONE,
  MODE_LINEAR,
  MODE_BLINK,
  MODE_PINK_PONG,
};

struct State {
  bool    are_leds_on;
  bool    time_switch_pass;
  int     mode;
};

State state;

void setup() {
  Serial.begin(9600);
  FOR_RANGE(0, leds) {
    pinMode(leds_pins[index], OUTPUT);
  }
  FOR_RANGE(0, buttons) {
    pinMode(buttons_pins[index], INPUT);
  }
}

void ChangeState(State *state, int mode) {
  state->are_leds_on = (state->are_leds_on && state->mode == mode) ? false : true;
  if (state->are_leds_on) {
    state->mode = mode;
  } else {
    state->mode = MODE_NONE;
    FOR_RANGE(0, leds) {
      digitalWrite(leds_pins[index], LOW);
    }
  }
}

byte current_led = 0;
byte pink_ponk_ball = 0;
short direction     = 1;

void loop() {
  delta += 1;
  if (delta > time_switch)  {
    delta -= time_switch;
    state.time_switch_pass = true;
    current_led = (current_led >= leds-1) ? 0 : current_led+1;
    pink_ponk_ball += direction;
    if (pink_ponk_ball >= leds-1 || pink_ponk_ball <= 0) {
      direction *= -1;
    }
  } else {
    state.time_switch_pass = false;
  }

  if (digitalRead(buttons_pins[0]) == HIGH) {
      ChangeState(&state, MODE_LINEAR);
  }
  if (digitalRead(buttons_pins[1]) == HIGH) {
    ChangeState(&state, MODE_BLINK);
  }
  if (digitalRead(buttons_pins[2]) == HIGH) {
      ChangeState(&state, MODE_PINK_PONG);
  }

  switch (state.mode) {
  case MODE_LINEAR: {
    if (state.time_switch_pass) {
      FOR_RANGE(0, leds) {
        if (index == current_led) {
          digitalWrite(leds_pins[index], HIGH);
        } else {
          digitalWrite(leds_pins[index], LOW);
        }
      }
    }
  } break;
  case MODE_BLINK: {
    if (state.time_switch_pass) {
      if (current_led % 2 == 0) {
          digitalWrite(leds_pins[0], HIGH);
          digitalWrite(leds_pins[1], LOW);
          digitalWrite(leds_pins[2], HIGH);
          digitalWrite(leds_pins[3], LOW);
      } else {
          digitalWrite(leds_pins[0], LOW);
          digitalWrite(leds_pins[1], HIGH);
          digitalWrite(leds_pins[2], LOW);
          digitalWrite(leds_pins[3], HIGH);
      }
    }
  } break;
  case MODE_PINK_PONG: {
    if (state.time_switch_pass) {
      FOR_RANGE(0, leds) {
        if (index == pink_ponk_ball) {
          digitalWrite(leds_pins[index], HIGH);
        } else {
          digitalWrite(leds_pins[index], LOW);
        }
      }
    }
  } break;
  default: {

  }
  }
}
