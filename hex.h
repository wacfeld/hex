#ifndef HEX_H
#define HEX_H

struct Coord
{
  int r;
  int c;
};

typedef bool (*pred)(Coord co);

enum Piece {BLANK, RED, GREEN};

Piece opp(Piece p);

Piece get(Coord co);
void set(Coord co, Piece p);

const int board_size = 8;
extern Piece board[board_size][board_size];

bool connected(pred start, pred end, pred match);

#endif
