#include <conio.h>
#include <windows.h>

#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "../inc/point.h"
#include "../inc/snake.h"
using namespace std;

// The settings of Set cursor and buffer.
bool showCircle = false;
HANDLE outBufferA, outBufferB;
HANDLE *outPuter;
COORD coord = {0, 0};
DWORD bytes = 0;
// Map of this game is a matrix.
char map[31][31];

// ShowGraphics is a double buffer display function to make the image
// consistent. The double buffer provide an advantage is that no screen
// flickering occurs.
void ShowGraphics(Snake playerSnake) {
  showCircle = !showCircle;
  // Switch current buffer to write down the image.
  if (showCircle) {
    outPuter = &outBufferA;
  } else {
    outPuter = &outBufferB;
  }
  string temp = "                           SCORE: " +
                to_string(playerSnake.ShowSnakeLength() - 3);
  COORD scoreCoord;
  scoreCoord.X = 0;
  scoreCoord.Y = 32;
  WriteConsoleOutputCharacterA(*outPuter, temp.c_str(), temp.length(),
                               scoreCoord, &bytes);
  for (int i = 0; i <= 30; i++) {
    coord.X = 0;
    coord.Y = i;
    int k = 0;
    char temp[62] = {' '};
    for (int j = 0; j < 31; j++) {
      temp[k] = map[i][j];
      k += 2;
    }
    WriteConsoleOutputCharacterA(*outPuter, temp, 62, coord, &bytes);
  }
  // Set the new buffer to save the image.
  SetConsoleActiveScreenBuffer(*outPuter);
}

// Generate image into the current buffer. This is simple because the image had
// been writen in the matrix, but this function build the map border in matrix.
void DrawGraphics(Snake playerSnake) {
  for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 31; j++) {
      map[i][j] = ' ';
    }
  }
  // Build the map border.
  for (int i = 1; i < 31; i++) {
    map[i][1] = '#';
    map[i][30] = '#';
  }
  for (int i = 1; i < 31; i++) {
    map[1][i] = '#';
    map[30][i] = '#';
  }
  for (vector<point>::iterator it = playerSnake.snakeBody.begin();
       it < playerSnake.snakeBody.end(); it++) {
    map[it->r][it->c] = '*';
  }
}

// Refresh dot to promote the progress of the game.
void MakeDot(int *a, int *b, Snake playerSnake) {
label:
  srand(time(0));
  *a = rand() % 28 + 2;
  *b = rand() % 28 + 2;
  // There is a check to prevent refresh the dot covered by this snake. If the
  // dot is miss it will be a real trouble.
  for (vector<point>::iterator it = playerSnake.snakeBody.begin();
       it < playerSnake.snakeBody.end(); it++) {
    if (it->r == *a && it->c == *b) {
      goto label;
    }
  }
}

int main() {
  // Some window-related settings. The title of this window is snake and the
  // window have 63 columns and 34 rows.
  SetConsoleTitle("Snake");
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO CursorInfo;
  GetConsoleCursorInfo(handle, &CursorInfo);
  CursorInfo.bVisible = false;
  SetConsoleCursorInfo(handle, &CursorInfo);
  system("mode con cols=63 lines=34");
  Snake playerSnake;
  // The frist buffer.
  outBufferA = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
                                         CONSOLE_TEXTMODE_BUFFER, NULL);
  // The second buffer.
  outBufferB = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
                                         CONSOLE_TEXTMODE_BUFFER, NULL);
  CONSOLE_CURSOR_INFO cci;
  cci.bVisible = 0;
  cci.dwSize = 1;
  // Set the cursor to point to the image buffer areas.
  SetConsoleCursorInfo(outBufferA, &cci);
  SetConsoleCursorInfo(outBufferB, &cci);
  char now_direction;
  int dotH, dotL;
  int *pointDotH = &dotH, *pointDotL = &dotL;
  MakeDot(pointDotH, pointDotL, playerSnake);
  while (1) {
    // Non-blocking monitoring the control events when keyboard is pressed.
    if (kbhit()) {
      now_direction = getch();
      switch (tolower(now_direction)) {
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
    if (playerSnake.headH == 1 || playerSnake.headL == 1 ||
        playerSnake.headH == 30 || playerSnake.headL == 30 ||
        playerSnake.SelfCheck()) {
      // A screen showing the end of the game to show the player's score.
      COORD overCoord;
      overCoord.X = 23;
      overCoord.Y = 15;
      string temp = "G A M E   O V E R";
      WriteConsoleOutputCharacterA(*outPuter, temp.c_str(), temp.length(),
                                   overCoord, &bytes);
      cin.get();
      return 0;
    }
    if (playerSnake.headH == dotH && playerSnake.headL == dotL) {
      playerSnake.NewBody();
      MakeDot(pointDotH, pointDotL, playerSnake);
    }
    DrawGraphics(playerSnake);
    map[dotH][dotL] = 'o';
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