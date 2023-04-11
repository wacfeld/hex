#ifndef HEX_H
#define HEX_H

struct Coord
{
  int r;
  int c;
};

enum Piece {BLANK, RED, GREEN};

const int board_size = 8;
extern Piece board[board_size][board_size];

#endif
