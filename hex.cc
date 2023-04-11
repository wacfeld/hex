#include <queue>

#include "hex.h"

Piece board[board_size][board_size];

Piece pLR = GREEN;
Piece pTB = RED;

bool left(Coord co)
{
  return co.c == 0;
}

bool right(Coord co)
{
  return co.c == board_size-1;
}

bool top(Coord co)
{
  return co.r == 0;
}

bool bottom(Coord co)
{
  return co.r == board_size-1;
}

bool matchLR(Coord co)
{
  return get(co) == pLR;
}

bool matchTB(Coord co)
{
  return get(co) == pTB;
}

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

bool valid(Coord co)
{
  if(co.r >= 0
      && co.c >= 0
      && co.r < board_size
      && co.c < board_size)
    return true;
  return false;
}

Piece get(Coord co)
{
  return board[co.r][co.c];
}

void set(Coord co, Piece p)
{
  board[co.r][co.c] = p;
}

std::vector<Coord> adjacent(Coord co)
{
  int r = co.r;
  int c = co.c;
  std::vector<Coord> v1 =
  {
    {r+1, c},
    {r, c+1},
    {r+1, c-1},
    {r, c-1},
    {r-1, c},
    {r-1, c+1},
  };

  
  std::vector<Coord> v2;
  for(Coord temp : v1)
  {
    if(valid(temp))
    {
      v2.push_back(temp);
    }
  }

  return v2;
}

bool connected(pred start, pred end, pred match)
{
  bool mark[board_size][board_size];
  
  std::queue<Coord> Q;
  for(int r = 0; r < board_size; r++)
  {
    for(int c = 0; c < board_size; c++)
    {
      mark[r][c] = false;
      if(start({r,c}) && match({r,c}))
      {
        Q.push({r,c});
        mark[r][c] = true;
      }
    }
  }

  while(!Q.empty())
  {
    Coord co = Q.front();
    Q.pop();

    if(end(co))
    {
      return true;
    }
    
    std::vector<Coord> adj = adjacent(co);
    for(Coord a : adj)
    {
      if(mark[a.r][a.c] == false)
      {
        if(match(a)) {
          mark[a.r][a.c] = true;
          Q.push(a);
        }
      }
    }
  }

  return false;
}
