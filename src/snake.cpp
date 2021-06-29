#include "../inc/snake.h"

using namespace std;

extern vector<vector<char>> map;

// The snake's constructor set the start location, direction and the initial
// length of the snake.
Snake::Snake() {
    struct point head;
    head.row = map.size() / 2;
    head.col = map[0].size() / 2;
    this->snakeBody.push_back(head);
    this->snakeLength = 1;
    this->snakeDirection = 'd';
    this->headRow = head.row;
    this->headCol = head.col;
    this->tailRow = head.row;
    this->tailCol = head.col;
}

Snake::~Snake() {}

// Refresh snake's body position to achieve its movement. There are a judgment
// forbiden the snake reverse move.
void Snake::RefreshBody(char nowDirection) {
    tailRow = snakeBody.back().row;
    tailCol = snakeBody.back().col;
    for (vector<point>::iterator it = snakeBody.end() - 1;
         it > snakeBody.begin(); it--) {
        it->row = (it - 1)->row;
        it->col = (it - 1)->col;
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
                snakeBody.front().row--;
                break;
            case 'a':
                snakeBody.front().col--;
                break;
            case 's':
                snakeBody.front().row++;
                break;
            case 'd':
                snakeBody.front().col++;
                break;
        }
    } else {
        // If there is a change in direction.
        switch (nowDirection) {
            case 'w':
                snakeDirection = 'w';
                snakeBody.front().row--;
                break;
            case 'a':
                snakeDirection = 'a';
                snakeBody.front().col--;
                break;
            case 's':
                snakeDirection = 's';
                snakeBody.front().row++;
                break;
            case 'd':
                snakeDirection = 'd';
                snakeBody.front().col++;
                break;
        }
    }
    // Reset the position of the snake head.
    headRow = snakeBody.front().row;
    headCol = snakeBody.front().col;
    return;
}

// Create new nodes for the snake body. The body of snake is a vector container,
// when the snake eat a dot there will be a new body be pushed.
void Snake::NewBody() {
    struct point newBody;
    newBody.row = tailRow;
    newBody.col = tailCol;
    snakeBody.push_back(newBody);
    this->snakeLength++;
}

// Self-check if snake hits himself.
bool Snake::SelfCheck() {
    for (vector<point>::iterator it = snakeBody.begin() + 1;
         it < snakeBody.end(); it++) {
        if (it->row == snakeBody.front().row &&
            it->col == snakeBody.front().col) {
            return true;
        }
    }
    return false;
}

// Get the length of the snake.
int Snake::ShowSnakeLength() { return this->snakeLength; }