#include <Keypad.h>

const byte rows  = 4;
const byte cols  = 4;
byte row_pins[rows]  = {9, 8, 7, 6};
byte col_pins[cols]  = {5, 4, 3, 2};
const byte output_pin = 10;

char keymap[rows][cols] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D',
};
Keypad pad = Keypad(makeKeymap(keymap),
                    row_pins, col_pins,
                    rows, cols);

float percentage; // From 0 to 1 inclusive.

void setup()
{
  Serial.begin(9600);
  for (byte index = 0; index < rows; index++){
   	pinMode(row_pins[index], INPUT);
  }
  for (byte index = 0; index < cols; index++){
   	pinMode(col_pins[index], INPUT);
  }
  pinMode(output_pin, OUTPUT);
}

void loop()
{
  
  char input = pad.getKey();

  if (input != NO_KEY) {
    switch (input) {
    case '1': {
      percentage = .1;
    } break;
    case '2': {
      percentage = .2;
    } break;
    case '3': {
      percentage = .3;
    } break;
    case '4': {
      percentage = .4;
    } break;
    case '5': {
      percentage = .5;
    } break;
    case '6': {
      percentage = .6;
    } break;
    case '7': {
      percentage = .7;
    } break;
    case '8': {
      percentage = .8;
    } break;
    case '9': {
      percentage = .9;
    } break;
    default: {
      percentage = 0;
    }
    }
  }
  
  analogWrite(output_pin, (int)(255 * percentage));
}
