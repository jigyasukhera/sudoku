#include <windows.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <utility>

using namespace std;

class Sudoku {
   private:
    char board[9][9];

    // Translate a number (1-81) to a grid position (row, col)
    pair<int, int> translate(int num) {
        return make_pair((num - 1) / 9, (num - 1) % 9);
    }

    // Check if a move is valid
    bool is_valid_move(int num, pair<int, int> pos) {
        int row = pos.first;
        int col = pos.second;

        // Check if the cell is already occupied
        if (board[row][col] != ' ') {
            return false;
        }

        // Check row and column for duplicates
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num || board[i][col] == num) {
                return false;
            }
        }

        // Check the 3x3 subgrid for duplicates
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[startRow + i][startCol + j] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    // Generate a Sudoku board based on difficulty
    void generate_board(int difficulty) {
        srand(time(NULL));
        unordered_set<int> positions;

        int numCells;
        switch (difficulty) {
            case 1:
                numCells = 36;
                break;  // Easy
            case 2:
                numCells = 27;
                break;  // Medium
            case 3:
                numCells = 18;
                break;  // Hard
            default:
                numCells = 36;
                break;  // Default to Easy
        }

        while (positions.size() < numCells) {
            int pos = 1 + (rand() % 81);
            positions.insert(pos);
        }

        for (int pos : positions) {
            pair<int, int> p = translate(pos);
            int num = '1' + (rand() % 9);
            while (!is_valid_move(num, p)) {
                num = '1' + (rand() % 9);
            }
            board[p.first][p.second] = num;
        }
    }

    // Display the Sudoku board
    void display_board() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) cout << "- - ";

            cout << '-' << endl;

            for (int k = 0; k < 10; ++k) {
                if (k == 9)
                    cout << "|";
                else
                    cout << "| " << board[i][k] << ' ';
            }

            cout << endl;
        }

        for (int i = 0; i < 9; ++i) cout << "- - ";

        cout << '-' << endl;
    }

    // Check if the board is full
    bool is_board_full() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

   public:
    Sudoku() { initialize(); }

    // Initialize the board with empty cells
    void initialize() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = ' ';
            }
        }
    }

    // Main game loop
    void play() {
        int difficulty;
        cout << "------------------------------------------------WELCOME TO "
                "SUDOKU----------------------------------------------------"
             << endl;
        cout << "Enter the difficulty level you want:\n 1.) Easy\n 2.) "
                "Medium\n 3.) Hard\n";
        cin >> difficulty;

        if (difficulty < 1 || difficulty > 3) {
            cout << "Invalid difficulty level. Defaulting to Easy." << endl;
            difficulty = 1;
        }

        generate_board(difficulty);
        display_board();

        while (!is_board_full()) {
            int num;
            pair<int, int> pos;

            cout << "Enter number (1-9) or 0 to quit: ";
            cin >> num;

            if (cin.fail() || num < 0 || num > 9) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 9."
                     << endl;
                continue;
            }

            if (num == 0) {
                cout << "Thanks for playing! Goodbye!" << endl;
                return;
            }

            cout << "Enter position (row col, 1-9): ";
            cin >> pos.first >> pos.second;

            if (cin.fail() || pos.first < 1 || pos.first > 9 ||
                pos.second < 1 || pos.second > 9) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid position. Please enter values between 1 and 9."
                     << endl;
                continue;
            }

            pos.first--;  // Convert to 0-based index
            pos.second--;

            if (is_valid_move('0' + num, pos)) {
                board[pos.first][pos.second] = '0' + num;
                display_board();
            } else {
                Beep(523, 500);  // Beep sound for invalid move
                cout << "Invalid move! Try again." << endl;
            }
        }

        cout << "Congratulations! You've completed the Sudoku!" << endl;
    }
};

int main() {
    Sudoku game;
    game.play();
    return 0;
}
