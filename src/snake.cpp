#include "../inc/snake.h"

#include <vector>

#include "../inc/point.h"
using namespace std;

extern char map[31][31];

// The snake's constructor set the start location, direction and the initial
// length of the snake.
Snake::Snake() {
  struct point temp;
  for (int i = 15; i <= 17; i++) {
    temp.r = 15;
    temp.c = i;
    this->snakeBody.push_back(temp);
  }
  this->snakeLength = 3;
  this->snakeDirection = 'a';
  this->headH = 15;
  this->headL = 15;
  this->tailH = 15;
  this->tailL = 17;
}

Snake::~Snake() {}

// Refresh snake's body position to achieve its movement. There are a judgment
// forbiden the snake reverse move.
void Snake::RefreshBody(char nowDirection) {
  tailH = snakeBody.back().r;
  tailL = snakeBody.back().c;
  for (vector<point>::iterator it = snakeBody.end() - 1; it > snakeBody.begin();
       it--) {
    it->r = (it - 1)->r;
    it->c = (it - 1)->c;
  }
  // Exclude special cases of reverse movement.
  if (this->snakeDirection == 'w' && nowDirection == 's') {
    nowDirection = 1;
  }
  if (this->snakeDirection == 'a' && nowDirection == 'd') {
    nowDirection = 1;
  }
  if (this->snakeDirection == 's' && nowDirection == 'w') {
    nowDirection = 1;
  }
  if (this->snakeDirection == 'd' && nowDirection == 'a') {
    nowDirection = 1;
  }
  if (nowDirection == 1) {
    // If there is no change in direction.
    switch (this->snakeDirection) {
      case 'w':
        snakeBody.front().r--;
        break;
      case 'a':
        snakeBody.front().c--;
        break;
      case 's':
        snakeBody.front().r++;
        break;
      case 'd':
        snakeBody.front().c++;
        break;
    }
  } else {
    // If there is a change in direction.
    switch (nowDirection) {
      case 'w':
        snakeDirection = 'w';
        snakeBody.front().r--;
        break;
      case 'a':
        snakeDirection = 'a';
        snakeBody.front().c--;
        break;
      case 's':
        snakeDirection = 's';
        snakeBody.front().r++;
        break;
      case 'd':
        snakeDirection = 'd';
        snakeBody.front().c++;
        break;
    }
  }
  // Reset the position of the snake head.
  headH = snakeBody.front().r;
  headL = snakeBody.front().c;
  return;
}

// Create new nodes for the snake body. The body of snake is a vector container,
// when the snake eat a dot there will be a new body be pushed.
void Snake::NewBody() {
  struct point newBody;
  newBody.r = tailH;
  newBody.c = tailL;
  snakeBody.push_back(newBody);
  this->snakeLength++;
}

// Self-check if snake hits himself.
bool Snake::SelfCheck() {
  for (vector<point>::iterator it = snakeBody.begin() + 1; it < snakeBody.end();
       it++) {
    if (it->r == snakeBody.front().r && it->c == snakeBody.front().c) {
      return true;
    }
  }
  return false;
}

// Get the length of the snake.
int Snake::ShowSnakeLength() { return this->snakeLength; }