#include<iostream>
#include<string>
#include<sstream>
using namespace std;

const int ROWS = 3;
const int COLS = 3;
char board[ROWS][COLS];

void initializeGame();
void printCurrentBoard();
void getUserInput(char currentPlayer);
bool cellAlreadyOccupied(int row, int col);
char getWinner();
bool isBoardFull();

int main() {
    initializeGame();
    char currentPlayer = 'X';

    for (int turn = 0; turn < 9; turn++) {
        printCurrentBoard();
        getUserInput(currentPlayer);

        char winner = getWinner();
        if (winner != ' ') {
            printCurrentBoard();
            cout << "Player " << winner << " wins!\n";
            return 0;
        }
        else if (isBoardFull()) {
            printCurrentBoard();
            cout << "Its a draw!\n";
                return 0;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printCurrentBoard();
    return 0;
}


void initializeGame() {
	for (int i = 0; i < ROWS;i++) {
		for (int j = 0; j < COLS;j++) {
			board[i][j] = ' '; //empty cell
		}
	}
}
void printCurrentBoard() {
	for (int i = 0;i < ROWS;i++) {
		cout << " ";
		for (int j = 0; j < COLS;j++) {
			cout << board[i][j];
			if (j < COLS - 1) cout << " | ";
		}
		cout << "\n";
		if (i < ROWS - 1) cout << "---|---|---\n";
	}
}
bool cellAlreadyOccupied(int row, int col) {
    return board[row][col] != ' ';
}

void getUserInput(char currentPlayer) {
    string inputLine;
    int row, col;
    bool valid = false;

    while (!valid) {
        cout << "Player " << currentPlayer << ", enter row (1-3) and column (1-3): ";
        getline(cin, inputLine);
        istringstream iss(inputLine);

        if (iss >> row >> col) {
            row--; col--; // convert to 0-based index
            if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                if (!cellAlreadyOccupied(row, col)) {
                    board[row][col] = currentPlayer;
                    valid = true;
                }
                else {
                    cout << "That cell is already occupied. Try again.\n";
                }
            }
            else {
                cout << "Row and column must be between 1 and 3. Try again.\n";
            }
        }
        else {
            cout << "Invalid input format. Please enter two numbers separated by a space.\n";
        }
    }
}
char getWinner() {
    // Rows
    for (int i = 0; i < ROWS; i++) {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return board[i][0];
    }
    // Columns
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] != ' ' &&
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j])
            return board[0][j];
    }
    // Diagonals
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return board[0][0];

    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return board[0][2];

    return ' ';
}
bool isBoardFull() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == ' ') {
                return false;  // found an empty cell
            }
        }
    }
    return true;  // no empty cells found
}
