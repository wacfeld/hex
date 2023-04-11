#include "hex.h"

Piece board[board_size][board_size];

Piece opp(Piece p)
{
  if(p == RED)
  {
    return GREEN;
  }
  else
  {
    return RED;
  }
}

Piece get(Coord co)
{
  return board[co.r][co.c];
}

void set(Coord co, Piece p)
{
  board[co.r][co.c] = p;
}
