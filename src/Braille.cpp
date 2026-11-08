#include "Braille.h"

// Letter patterns a..z. Bit 0..5 = dot 1..6.
static const uint8_t LETTERS[26] = {
  0x01, 0x03, 0x09, 0x19, 0x11, 0x0B, 0x1B, 0x13, 0x0A, 0x1A, // a..j
  0x05, 0x07, 0x0D, 0x1D, 0x15, 0x0F, 0x1F, 0x17, 0x0E, 0x1E, // k..t
  0x25, 0x27, 0x3A, 0x2D, 0x3D, 0x35                          // u..z
};

static const uint8_t SIGN_CAPITAL = 0x20; // dot 6
static const uint8_t SIGN_NUMBER  = 0x3C; // dots 3,4,5,6

// Common punctuation. 0xFF means "not found".
static const char    PUNCT_CHARS[] = { ' ', ',', '\'', ';', ':', '.', '!', '?', '-' };
static const uint8_t PUNCT_CELLS[] = { 0x00, 0x02, 0x04, 0x06, 0x12, 0x32, 0x16, 0x26, 0x24 };
static const uint8_t PUNCT_COUNT   = 9;

BrailleClass Braille;

static uint8_t punctCell(char c) {
  for (uint8_t i = 0; i < PUNCT_COUNT; i++) {
    if (PUNCT_CHARS[i] == c) return PUNCT_CELLS[i];
  }
  return 0xFF;
}

uint8_t BrailleClass::encode(char c) const {
  if (c >= 'a' && c <= 'z') return LETTERS[c - 'a'];
  if (c >= 'A' && c <= 'Z') return LETTERS[c - 'A'];
  if (c >= '1' && c <= '9') return LETTERS[c - '1']; // 1..9 use a..i
  if (c == '0') return LETTERS[9];                   // 0 uses j
  uint8_t p = punctCell(c);
  if (p != 0xFF) return p;
  return 0x00;
}

char BrailleClass::decode(uint8_t cell) const {
  cell &= 0x3F;
  if (cell == 0x00) return ' ';
  for (uint8_t i = 0; i < 26; i++) {
    if (LETTERS[i] == cell) return (char)('a' + i);
  }
  for (uint8_t i = 1; i < PUNCT_COUNT; i++) { // skip space at index 0
    if (PUNCT_CELLS[i] == cell) return PUNCT_CHARS[i];
  }
  return 0; // signs and unknown cells
}

bool BrailleClass::dot(uint8_t cell, uint8_t n) const {
  if (n < 1 || n > 6) return false;
  return (cell >> (n - 1)) & 0x01;
}

uint8_t BrailleClass::capitalSign() const { return SIGN_CAPITAL; }
uint8_t BrailleClass::numberSign() const  { return SIGN_NUMBER; }

size_t BrailleClass::textToCells(const char* text, uint8_t* cells, size_t maxCells) const {
  size_t n = 0;
  bool inNumber = false;
  for (size_t i = 0; text[i] != '\0'; i++) {
    char c = text[i];
    bool isDigit = (c >= '0' && c <= '9');

    if (isDigit && !inNumber) {
      if (n >= maxCells) break;
      cells[n++] = SIGN_NUMBER;
      inNumber = true;
    }
    if (!isDigit) inNumber = false;

    if (c >= 'A' && c <= 'Z') {
      if (n >= maxCells) break;
      cells[n++] = SIGN_CAPITAL;
    }

    if (n >= maxCells) break;
    cells[n++] = encode(c);
  }
  return n;
}
