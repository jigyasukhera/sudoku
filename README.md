# Sudoku Game in C++

## Overview
This is a simple console-based Sudoku game implemented in C++. The program generates a Sudoku board based on the selected difficulty level and allows the user to play by entering numbers into empty cells. The game ensures valid moves and alerts the player in case of invalid entries.

## Features
- Generates a Sudoku board with three difficulty levels:
  - Easy (36 pre-filled numbers)
  - Medium (27 pre-filled numbers)
  - Hard (18 pre-filled numbers)
- Allows the player to enter numbers and positions
- Checks for valid moves before placing a number
- Alerts the user with a beep sound if an invalid move is attempted
- Detects when the board is full and ends the game with a congratulatory message
- Option to quit the game by entering `0`

## Requirements
- A C++ compiler (e.g., g++, MinGW, MSVC)
- Windows OS (for `Beep()` function, which may not work on other OS)

## How to Compile and Run
1. Open a terminal or command prompt.
2. Navigate to the directory containing the `Sudoku.cpp` file.
3. Compile the program using:
   ```sh
   g++ Sudoku.cpp -o Sudoku.exe
   ```
4. Run the executable:
   ```sh
   ./Sudoku.exe
   ```

## How to Play
1. The game starts by asking the user to select a difficulty level.
2. The Sudoku board is displayed with some pre-filled numbers.
3. The user is prompted to enter a number (1-9) or `0` to quit.
4. The user enters a row and column (1-9) to place the number.
5. If the move is valid, the board updates; otherwise, an alert is given.
6. The game continues until the board is full or the player quits.

## Notes
- The board is randomly generated based on difficulty.
- The program ensures that the initial numbers placed do not violate Sudoku rules.
- The implementation uses basic console output and may not include advanced error handling or solving functionalities.

## Future Improvements
- **There may be a case that a game board is generated that is not solvable. This indicates the requirement of a solver, which will be included soon.**
- Implement a Sudoku solver to check for solvable boards.
- Improve the UI with a graphical interface.
- Add a hint system to assist players.
- Make it platform-independent by removing `Beep()` or replacing it with a cross-platform alternative.

## License
This project is open-source and free to use, modify, and distribute.

## Author
Developed as a simple demonstration of Sudoku logic using C++.
