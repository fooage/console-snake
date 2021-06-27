#ifdef __WIN32__
#include <conio.h>
#include <windows.h>
HANDLE outBufferA =
           CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
                                     CONSOLE_TEXTMODE_BUFFER, NULL),
       outBufferB =
           CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
                                     CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE *outPuter;
COORD coord = {0, 0};
DWORD bytes = 0;
#endif

#include <cmath>
#include <iostream>

#include "../inc/graph.h"
#include "../inc/point.h"
#include "../inc/snake.h"
using namespace std;

// Map of this game is a matrix.
vector<vector<char>> map;
int maxRows = 0, maxCols = 0;

int main() {
#ifdef __WIN32__
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  CONSOLE_SCREEN_BUFFER_INFO screenInfo;
  // Hide the cursor when screen output.
  cursorInfo.bVisible = false;
  cursorInfo.dwSize = 1;
  // Set the cursor to point to the image buffer areas.
  SetConsoleCursorInfo(outBufferA, &cursorInfo);
  SetConsoleCursorInfo(outBufferB, &cursorInfo);
  // Get the info of this console and set the row and column for the matrix.
  GetConsoleScreenBufferInfo(handle, &screenInfo);
  maxRows = screenInfo.srWindow.Bottom + 1;
  maxCols = ceil((screenInfo.srWindow.Right + 1) * 1.0 / 2);
#endif
  map = vector<vector<char>>(maxRows, vector<char>(maxCols));
  Snake playerSnake;
  char nowDirection;
  int dotRow, dotCol;
  int *pDotRow = &dotRow, *pDotCol = &dotCol;
  MakeDot(pDotRow, pDotCol, playerSnake);
  while (1) {
// Non-blocking monitoring the control events when keyboard is pressed.
#ifdef __WIN32__
    if (kbhit()) {
      nowDirection = getch();
#endif
      switch (tolower(nowDirection)) {
        case 'w':
          playerSnake.RefreshBody('w');
          break;
        case 'a':
          playerSnake.RefreshBody('a');
          break;
        case 's':
          playerSnake.RefreshBody('s');
          break;
        case 'd':
          playerSnake.RefreshBody('d');
          break;
      }
    } else {
      playerSnake.RefreshBody(1);
    }
    // Check if it hits the wall or hits the body.
    if (playerSnake.headRow == 0 || playerSnake.headCol == 0 ||
        playerSnake.headRow == maxRows - 1 ||
        playerSnake.headCol == maxCols - 1 || playerSnake.SelfCheck()) {
      // TODO: A screen showing the end of the game to show the player's score.
      ShowGameOver();
      cin.get();
      return 0;
    }
    if (playerSnake.headRow == dotRow && playerSnake.headCol == dotCol) {
      playerSnake.NewBody();
      MakeDot(pDotRow, pDotCol, playerSnake);
    }
    DrawGraphics(playerSnake);
    map[dotRow][dotCol] = 'o';
    ShowGraphics(playerSnake);
    // Level the difficulty of the game by the scores. Game use the sleep
    // function to control the speed of snake.
    if (playerSnake.ShowSnakeLength() - 3 < 5) {
      Sleep(300);
    } else if (5 <= playerSnake.ShowSnakeLength() - 3 &&
               playerSnake.ShowSnakeLength() - 3 < 10) {
      Sleep(250);
    } else if (10 <= playerSnake.ShowSnakeLength() - 3 &&
               playerSnake.ShowSnakeLength() - 3 < 15) {
      Sleep(200);
    } else if (15 <= playerSnake.ShowSnakeLength() - 3 &&
               playerSnake.ShowSnakeLength() - 3 < 20) {
      Sleep(150);
    } else if (20 <= playerSnake.ShowSnakeLength() - 3 &&
               playerSnake.ShowSnakeLength() - 3 < 25) {
      Sleep(100);
    } else {
      Sleep(50);
    }
  }
  return 0;
}