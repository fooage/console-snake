#ifndef SNAKE_H
#define SNAKE_H
#include <vector>

#include "point.h"
using namespace std;

// Snake has some functions to create its new body and update its location, and
// check if the snake is dead.
class Snake {
  friend void DrawGraphics(Snake);
  // Use the friend function let dot interact with snake.
  friend void MakeDot(int, int, Snake);

private:
  int snakeLength;
  char snakeDirection;

public:
  // Snake body which is public used.
  vector<point> snakeBody;
  int headRow;
  int headCol;
  int tailRow;
  int tailCol;
  Snake();
  ~Snake();
  void RefreshBody(char); // Refresh body position to achieve its movement.
  void NewBody();         // Create new nodes for the snake body.
  bool SelfCheck();       // Self-check if snake hits himself.
  int ShowSnakeLength();  // Get the length of the snake.
};

#endif
