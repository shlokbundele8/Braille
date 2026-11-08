// Braille to Text: a 6-key Braille keyboard.
// Hold the dot keys for a letter, then press Enter to print it.

#include <Braille.h>

const uint8_t dotPins[6] = { 2, 3, 4, 5, 6, 7 }; // dots 1..6
const uint8_t enterPin   = 8;

void setup() {
  Serial.begin(9600);
  for (uint8_t i = 0; i < 6; i++) {
    pinMode(dotPins[i], INPUT_PULLUP);
  }
  pinMode(enterPin, INPUT_PULLUP);
  Serial.println("Hold dot keys, then press Enter.");
}

void loop() {
  if (digitalRead(enterPin) == LOW) {
    uint8_t cell = 0;
    for (uint8_t i = 0; i < 6; i++) {
      if (digitalRead(dotPins[i]) == LOW) {
        cell |= (1 << i);
      }
    }

    char c = Braille.decode(cell);
    Serial.println(c != 0 ? c : '?');

    delay(200);                                 // simple debounce
    while (digitalRead(enterPin) == LOW) { }    // wait for release
  }
}
