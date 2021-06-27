#ifndef GRAPH_H
#define GRAPH_H

#ifdef __WIN32__
#include <windows.h>
#endif

#include <cmath>
#include <ctime>
#include <string>

#include "../inc/snake.h"

// Graphics is a double buffer display function to make the image
// consistent.
void ShowGraphics(Snake);

// Write the picture to the output matrix.
void DrawGraphics(Snake);

// Game Over show the game over frame on the screen.
void ShowGameOver();

// Randomly refresh a dot and check its legitimacy.
void MakeDot(int *, int *, Snake);

#endif