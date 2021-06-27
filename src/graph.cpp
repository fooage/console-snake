#include "../inc/graph.h"

extern vector<vector<char>> map;
extern int maxRows, maxCols;

#ifdef __WIN32__
// The settings of Set cursor and buffer.
bool showCircle = false;
extern HANDLE outBufferA, outBufferB;
extern HANDLE *outPuter;
extern COORD coord;
extern DWORD bytes;
#endif

// ShowGraphics is a double buffer display function.
void ShowGraphics(Snake playerSnake) {
#ifdef __WIN32__
  showCircle = !showCircle;
  // Switch current buffer to write down the image.
  if (showCircle) {
    outPuter = &outBufferA;
  } else {
    outPuter = &outBufferB;
  }
  char *temp = new char[maxCols * 2];
  for (int j = 0; j < maxCols * 2; j++) {
    temp[j] = ' ';
  }
  for (int i = 0; i < maxRows; i++) {
    coord.X = 0;
    coord.Y = i;
    int k = 0;
    for (int j = 0; j < maxCols; j++) {
      temp[k] = map[i][j];
      k += 2;
    }
    WriteConsoleOutputCharacterA(*outPuter, temp, maxCols * 2, coord, &bytes);
  }
  delete[] temp;
  // Set the new buffer to save the image.
  SetConsoleActiveScreenBuffer(*outPuter);
#endif
}

void DrawGraphics(Snake playerSnake) {
  for (int i = 0; i < maxRows; i++) {
    for (int j = 0; j < maxCols; j++) {
      map[i][j] = ' ';
    }
  }
  // Build the map border.
  for (int i = 0; i < maxRows; i++) {
    map[i][0] = '#';
    map[i][maxCols - 1] = '#';
  }
  for (int i = 0; i < maxCols; i++) {
    map[0][i] = '#';
    map[maxRows - 1][i] = '#';
  }
  for (vector<point>::iterator it = playerSnake.snakeBody.begin();
       it < playerSnake.snakeBody.end(); it++) {
    map[it->row][it->col] = '*';
  }
}

void MakeDot(int *a, int *b, Snake playerSnake) {
label:
  srand(time(0));
  *a = rand() % (maxRows - 2) + 1;
  *b = rand() % (maxCols - 2) + 1;
  // There is a check to prevent refresh the dot covered by this snake. If the
  // dot is miss it will be a real trouble.
  for (vector<point>::iterator it = playerSnake.snakeBody.begin();
       it < playerSnake.snakeBody.end(); it++) {
    if (it->row == *a && it->col == *b) {
      goto label;
    }
  }
}

void ShowGameOver() {
#ifdef __WIN32__
  coord.X = floor(maxCols * 2 * 1.0 / 2) - 9;
  coord.Y = ceil(maxRows * 1.0 / 2) - 1;
  string temp = "G A M E   O V E R";
  WriteConsoleOutputCharacterA(*outPuter, temp.c_str(), temp.length(), coord,
                               &bytes);
#endif
}