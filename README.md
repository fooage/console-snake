# Snake

Snake is a game that many people have played. This command line window implemented with `C++` is not bad. The double-buffered output screen solves the splash screen, improves the game experience, and provides a simple speed level that can increase speed and difficulty as the snake grows longer.

## Installation

### Download

Use git clone at where you want to store the game source code.

```bash
git clone https://github.com/fooage/snake.git
```

### Compile

Make sure you have `C++` compilation environment and `CMake`.

```bash
# Use this command in the same directory with CMakeLists.txt.
cmake ./build
cd ./build
# Use your compiler make the binary file.
make
# Here is MinGW as an example
```

## Guide

Open the `snake.exe` in the `./bin` directory and start to play this game.

### Operation guide

- First turn off the input method to ensure that the American keyboard is input.

- Use the <kbd>W</kbd>, <kbd>A</kbd>, <kbd>S</kbd>, <kbd>D</kbd> to control up, left, down, right.

- There are five levels of game difficulty. Snake will move faster and fast as the score increases.

### Game rules

1. This is a snake game with boundaries. The snake is judged as a failure when it touches a wall

2. Snake bites his body and judged as a failure.

3. Snakes need to keep eating beans refreshed on the map to improve the game scores.
