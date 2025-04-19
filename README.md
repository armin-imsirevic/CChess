# Chess Engine 1.0

## Overview
This repository contains the source code for a basic chess engine written in C. The project is in its early stages and currently includes foundational definitions and a simple main program.

## Files

### 1. `definitions.h`
This file contains essential definitions and enumerations used throughout the chess engine. Key components include:
- Piece types (e.g., `whitePawn`, `blackKing`)
- File and rank enumerations (e.g., `FILE_A`, `RANK_1`)
- Square constants (e.g., `A1`, `H8`)
- Boolean values (`TRUE`, `FALSE`)

### 2. `main.c`
This is the main entry point of the program. Currently, it prints "Start!" to the console.

### 3. `makefile`
A simple makefile to compile the project using `clang`. Running `make` will produce an executable named `main`.

## How to Build
1. Ensure you have `clang` installed on your system.
2. Run the following command in the terminal:
   ```
   make
   ```
3. This will generate an executable file named `main`.

## How to Run
After building the project, run the executable with:
```bash
./main
```

## Future Plans
- Implement a chessboard representation.
- Add move generation and validation.
- Develop a basic AI for playing chess.

## License
This project is currently unlicensed. Feel free to use it for personal or educational purposes.