// Braille Linear Actuator: drive one cell of six actuators (one per dot).
// Each actuator pin goes HIGH to raise its dot, LOW to lower it.

#include <Braille.h>

const uint8_t dotPins[6] = { 2, 3, 4, 5, 6, 7 }; // actuators for dots 1..6

void showCell(uint8_t cell) {
  for (uint8_t i = 0; i < 6; i++) {
    digitalWrite(dotPins[i], Braille.dot(cell, i + 1) ? HIGH : LOW);
  }
}

void clearCell() {
  for (uint8_t i = 0; i < 6; i++) {
    digitalWrite(dotPins[i], LOW);
  }
}

void showText(const char* text) {
  for (size_t i = 0; text[i] != '\0'; i++) {
    showCell(Braille.encode(text[i]));
    delay(1000); // hold so the reader can feel the letter
  }
}

void setup() {
  for (uint8_t i = 0; i < 6; i++) {
    pinMode(dotPins[i], OUTPUT);
  }
}

void loop() {
  showText("hello");
  clearCell();
  delay(2000);
}
