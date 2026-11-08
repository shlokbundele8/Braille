// Vibration Braille: buzz each letter on one vibration motor.
// For every dot 1..6: a short buzz means the dot is raised, a silent gap means it is not.

#include <Braille.h>

const uint8_t motorPin = 9;

const unsigned long dotTime    = 200; // buzz or silent slot for one dot
const unsigned long dotGap     = 200; // gap between dots
const unsigned long letterGap  = 800; // gap between letters

void buzzCell(uint8_t cell) {
  for (uint8_t n = 1; n <= 6; n++) {
    if (Braille.dot(cell, n)) {
      digitalWrite(motorPin, HIGH);
      delay(dotTime);
      digitalWrite(motorPin, LOW);
    } else {
      delay(dotTime); // silent slot = empty dot
    }
    delay(dotGap);
  }
}

void buzzText(const char* text) {
  for (size_t i = 0; text[i] != '\0'; i++) {
    buzzCell(Braille.encode(text[i]));
    delay(letterGap);
  }
}

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  buzzText("hi");
  delay(2000);
}
