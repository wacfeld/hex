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

const int board_size = 10;
extern Piece board[board_size][board_size];

bool connected(pred start, pred end, pred match);

extern Piece pLR;
extern Piece pTB;

bool left(Coord co)     ;
bool right(Coord co)    ;
bool top(Coord co)      ;
bool bottom(Coord co)   ;
bool matchLR(Coord co)  ;
bool matchTB(Coord co)  ;


#endif
