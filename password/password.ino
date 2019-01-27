#include <Keypad.h>
#include <string.h>

const byte rows  = 4;
const byte cols  = 4;
byte row_pins[rows] = {9, 8, 7, 6};
byte col_pins[cols]  = {5, 4, 3, 2};
const int red_led    = 12;
const int green_led  = 13;
const int yellow_led = 11;

char keymap[rows][cols] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D',
};
Keypad pad = Keypad(makeKeymap(keymap),
                    row_pins, col_pins,
                    rows, cols);;

char password[16] = {"0000"};
char input[16];
char input_char[2];

enum {
  INVALID,
  ENTER_PASSWORD,
  CHANGE_PASSWORD_INIT,
  CHANGE_PASSWORD,
  PARTY
};

int state = INVALID;
double delta = 0.0;

void setup()
{
  Serial.begin(9600);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
}

void ResetState() {
  state = INVALID;
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(yellow_led, LOW);
  input[0] = 0;
}

enum {
  RED,
  GREEN,
  YELLOW
};

int led_party_state;

void Party() {
  if (led_party_state == RED) {
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, LOW);
  }
  if (led_party_state == GREEN) {
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, HIGH);
    digitalWrite(yellow_led, LOW);
  }
  if (led_party_state == YELLOW) {
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, HIGH);
  }
}

const double time_switch = 6000.0;

void loop()
{
  delta += 1.0;
  if (delta > time_switch) {
    delta -= time_switch;
    led_party_state = (led_party_state >= YELLOW) ? RED : led_party_state+1;
  }
  input_char[0] = pad.getKey();

  if (state == PARTY) {
    Party();
  }

  if (state == INVALID || state == PARTY) {
    digitalWrite(yellow_led, LOW);
    switch (input_char[0]) {
    case 'C': {
      ResetState();
      state = CHANGE_PASSWORD_INIT;
    } break;
    case 'A':
    {
      ResetState();
      state = ENTER_PASSWORD;
    } break;
    case 'B': {
      ResetState();
    } break;
    case 'D': {
      state = PARTY;
    } break;
    default: {

    }

    }
  }
  else if (state != PARTY) {
    digitalWrite(yellow_led, HIGH);
    switch(state) {
    case ENTER_PASSWORD:
    {
      if (isdigit(input_char[0])) {
        strcat(input, input_char);
      } else if (input_char[0] == '#'){
        if (strcmp(password, input) == 0) {
          state = INVALID;
          digitalWrite(green_led, HIGH);
          digitalWrite(red_led, LOW);
        } else {
          state = INVALID;
          digitalWrite(red_led, HIGH);
          digitalWrite(green_led, LOW);
        }
        input[0] = 0;
      } else if (input_char[0] != NO_KEY){
        state = INVALID;
        digitalWrite(red_led, HIGH);
        digitalWrite(green_led, LOW);
      }
    } break;
    case CHANGE_PASSWORD_INIT:
    {
      if (isdigit(input_char[0])) {
        strcat(input, input_char);
      } else if (input_char[0] == '#'){
        if (strcmp(password, input) == 0) {
          state = CHANGE_PASSWORD;
          digitalWrite(green_led, HIGH);
          digitalWrite(red_led, LOW);
        } else {
          state = INVALID;
          digitalWrite(red_led, HIGH);
          digitalWrite(green_led, LOW);
        }
        delay(1000);
        digitalWrite(red_led, LOW);
        digitalWrite(green_led, LOW);
        input[0] = 0;
      } else if (input_char[0] != NO_KEY){
        state = INVALID;
        digitalWrite(red_led, HIGH);
        digitalWrite(green_led, LOW);
      }
    } break;
    case CHANGE_PASSWORD:
    {
      if (isdigit(input_char[0])) {
        strcat(input, input_char);
      } else if (input_char[0] == '#'){
        if (strcpy(password, input) != 0) {
          state = INVALID;
          digitalWrite(green_led, HIGH);
          digitalWrite(red_led, LOW);
        } else {
          state = INVALID;
          digitalWrite(red_led, HIGH);
          digitalWrite(green_led, LOW);
        }
        input[0] = 0;
      } else if (input_char[0] != NO_KEY){
        state = INVALID;
        digitalWrite(red_led, HIGH);
        digitalWrite(green_led, LOW);
      }

    } break;
    default: {

    }
    }
  }
}
