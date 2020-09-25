#ifndef SET_SNAKE_H
#define SET_SNAKE_H
#include <vector>

#include "each_point.h"
using namespace std;

// The definition of snake class which is core of this game. Snake has some
// functions to create its new body and update its location, and check if the
// snake is dead.
class Snake {
  friend void DrawGraphics(Snake);
  // Use the friend function let dot interact with snake.
  friend void MakeDot(int, int, Snake);

 private:
  int snakeLength;
  char snakeDirection;

 public:
  // Snake body which is public used.
  vector<eachPoint> snakeBody;
  // Some locations of snake's body.
  int headH;
  int headL;
  int tailH;
  int tailL;
  // The snake's constructor and destructor.
  Snake();
  ~Snake();
  void RefreshBody(
      char);         // Refresh snake's body position to achieve its movement.
  void NewBody();    // Create new nodes for the snake body.
  bool SelfCheck();  // Self-check if snake hits himself.
  int ShowSnakeLength();  // Get the length of the snake.
};

#endif