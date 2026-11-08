#ifndef BRAILLE_H
#define BRAILLE_H

#include <stdint.h>
#include <stddef.h>

// Dot layout in one cell:
//   1 4
//   2 5
//   3 6
// A cell is one byte. Bit 0..5 = dot 1..6.

class BrailleClass {
public:
  // One character to one cell. Space and unknown give an empty cell (0).
  uint8_t encode(char c) const;

  // One cell to one character. Empty cell gives space. Unknown gives 0.
  char decode(uint8_t cell) const;

  // True if dot n (1..6) is raised in this cell.
  bool dot(uint8_t cell, uint8_t n) const;

  // Signs used before capitals and numbers.
  uint8_t capitalSign() const;
  uint8_t numberSign() const;

  // Turn text into a list of cells, adding capital and number signs.
  // Returns the number of cells written (never more than maxCells).
  size_t textToCells(const char* text, uint8_t* cells, size_t maxCells) const;
};

extern BrailleClass Braille;

#endif
