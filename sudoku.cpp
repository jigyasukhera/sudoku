#include <dos.h>
#include <unistd.h>
#include <windows.h>  // for  beep sound

#include <cstdlib>  // for using rand and srand functions
#include <ctime>    // for using time function
#include <iomanip>
#include <iostream>
#include <limits>
#include <thread>         // For multithreading
#include <unordered_set>  // for using unordered sets datatype
#include <utility>        // for using pairs

using namespace std;
int hours = 0;
int minutes = 0;
int seconds = 0;
bool running = true;

class Sudoku {
   private:
    char arr[9][9];

    pair<int, int> translate(int num) {
        return make_pair((num / 9), (num % 9) - 1);
    }

    bool is_valid_move(int num, pair<int, int> p) {
        // for row and coloum

        for (int i = 0; i < 9; ++i) {
            if (num == (int)arr[p.first][i])
                return false;
            else if (num == (int)arr[i][p.second])
                return false;
        }

        // for 3*3 boxes
        if (p.first < 3) {
            if (p.second < 3) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            } else if (p.second < 6) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            } else {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            }
        } else if (p.first < 6) {
            if (p.second < 3) {
                for (int i = 3; i < 6; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            } else if (p.second < 6) {
                for (int i = 3; i < 6; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            } else {
                for (int i = 3; i < 6; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            }
        } else {
            if (p.second < 3) {
                for (int i = 6; i < 9; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            } else if (p.second < 6) {
                for (int i = 6; i < 9; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            } else {
                for (int i = 6; i < 9; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        if (num == (int)arr[i][j]) return false;
                    }
                }
            }
        }

        return true;
    }

   public:
    void displayClock() {
        // system call to clear the screen

        cout << setfill(' ') << setw(55) << "         TIMER		 \n";
        cout << setfill(' ') << setw(55) << " --------------------------\n";
        cout << setfill(' ') << setw(29);
        cout << "| " << setfill('0') << setw(2) << hours << " hrs | ";
        cout << setfill('0') << setw(2) << minutes << " min | ";
        cout << setfill('0') << setw(2) << seconds << " sec |" << endl;
        cout << setfill(' ') << setw(55) << " --------------------------\n";
    }
    void timer() {
        // infinite loop because timer will keep
        // counting. To kill the process press
        // Ctrl+D. If it does not work ask
        // ubuntu for other ways.
        while (running) {
            // sleep system call to sleep
            // for 1 second
            sleep(1);
            // increment seconds
            seconds++;

            // if seconds reaches 60
            if (seconds == 60) {
                // increment minutes
                minutes++;

                // if minutes reaches 60
                if (minutes == 60) {
                    // increment hours
                    hours++;
                    minutes = 0;
                }
                seconds = 0;
            }
        }
    }
    void play() {
        while (!isboard_full()) {
            // Clear the screen
            // system("CLS");

            // Display the timer and board
            displayClock();   // Display the updated timer.
            display_board();  // Display the Sudoku board.

            int n;
            int c;
            pair<int, int> p;

            cout << "Enter number = ";
            cin >> n;

            if (cin.fail()) {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<std::streamsize>::max(),
                           '\n');  // Ignore invalid input
                cout << "Invalid input." << endl;
            }

            cout << "Enter position = ";
            cin >> p.first >> p.second;
            if (cin.fail()) {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<std::streamsize>::max(),
                           '\n');  // Ignore invalid input
                cout << "Enter values from 1-9." << endl;
            }
            // make_a_move(n, p);

            int m = n + 48;
            pair<int, int> p1(p.first - 1, p.second - 1);

            if (arr[p1.first][p1.second] == ' ') {
                if (n > 0 && n < 10 && is_valid_move(m, p1))

                {
                    arr[p1.first][p1.second] = m;

                } else {
                    Beep(800, 1000);
                    cout << "INVALID MOVE!" << endl;
                }
            }

            else {
                Beep(800, 1000);  // 523 hertz (C5) for 500 milliseconds
                                  // cin.get();
                cout << "INVALID MOVE POSITION OCCUPIED!" << endl;
            }
            system("CLS");
        }
        running = false;  // Stop the timer

        cout << "Congratulations! You've completed the Sudoku puzzle!" << endl;
    }
    void initialize() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) arr[i][j] = ' ';
        }
    }

    void display_board() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) cout << "- - ";

            cout << '-' << endl;

            for (int k = 0; k < 10; ++k) {
                if (k == 9)
                    cout << "|";
                else
                    cout << "| " << arr[i][k] << ' ';
            }

            cout << endl;
        }

        for (int i = 0; i < 9; ++i) cout << "- - ";

        cout << '-' << endl;
    }

    void generate_board(int difficulty) {
        if (difficulty > 0) {
            if (difficulty == 1) {
                unordered_set<int> Set;
                srand(time(NULL));

                while (Set.size() < 36) Set.insert(1 + (rand() % 81));

                for (unordered_set<int>::iterator itr = Set.begin();
                     itr != Set.end(); ++itr) {
                    pair<int, int> p = translate(*(itr));
                    int num = 48 + 1 + (rand() % 9);
                    while (!is_valid_move(num, p)) {
                        num = 48 + 1 + (rand() % 9);
                    }
                    arr[p.first][p.second] = num;
                }

                return;

            } else if (difficulty == 2) {
                unordered_set<int> Set;
                srand(time(NULL));

                while (Set.size() < 27) Set.insert(1 + (rand() % 81));

                for (unordered_set<int>::iterator itr = Set.begin();
                     itr != Set.end(); ++itr) {
                    pair<int, int> p = translate(*(itr));
                    int num = 48 + 1 + (rand() % 9);
                    while (!is_valid_move(num, p)) {
                        num = 48 + 1 + (rand() % 9);
                    }
                    arr[p.first][p.second] = num;
                }
                return;

            } else {
                unordered_set<int> Set;
                srand(time(NULL));

                while (Set.size() < 18) Set.insert(1 + (rand() % 81));

                for (unordered_set<int>::iterator itr = Set.begin();
                     itr != Set.end(); ++itr) {
                    pair<int, int> p = translate(*(itr));
                    int num = 48 + 1 + (rand() % 9);
                    while (!is_valid_move(num, p)) {
                        num = 48 + 1 + (rand() % 9);
                    }
                    arr[p.first][p.second] = num;
                }
                return;
            }
        } else {
            cout << "Try Again";
            cout << endl;
        }
    }

    bool isboard_full() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j)
                if (arr[i][j] == ' ') return 0;
        }
        return 1;
    }
};

int main() {
    Sudoku g1;
    int i;

    // Start the timer in a separate thread
    thread timerThread(&Sudoku::timer, &g1);

    g1.initialize();
    cout << "------------------------------------------------WELCOME TO "
            "SUDOKU----------------------------------------------------"
         << endl;
    cout << "Enter the difficulty level U want:\n 1.) Easy\n 2.) Medium\n 3.) "
            "Hard\n";
    cin >> i;

    g1.generate_board(i);
    g1.play();

    // Stop the timer and join the thread
    running = false;
    timerThread.join();

    return 0;
}
