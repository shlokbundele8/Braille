// Text to Braille: print each letter as a 6-dot cell on the Serial Monitor.

#include <Braille.h>

void printCell(uint8_t cell) {
  // Rows show dots 1,2,3 on the left and 4,5,6 on the right.
  for (uint8_t row = 1; row <= 3; row++) {
    Serial.print(Braille.dot(cell, row) ? 'O' : '.');
    Serial.print(' ');
    Serial.println(Braille.dot(cell, row + 3) ? 'O' : '.');
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { }

  const char* text = "Braille 123";
  uint8_t cells[64];
  size_t n = Braille.textToCells(text, cells, 64);

  Serial.print("Text: ");
  Serial.println(text);
  Serial.println();
  for (size_t i = 0; i < n; i++) {
    printCell(cells[i]);
  }
}

void loop() {
}
