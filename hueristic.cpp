#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#define PLAYER 'X'  // The human player
#define AI 'O'      // The computer

// Function to print the current board state
void printBoard(vector<vector<char>>& board) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            cout << board[row][col];
            if (col < 2) cout << " | ";
        }
        cout << endl;
        if (row < 2) cout << "---------" << endl;
    }
    cout << endl;
}

// Check if there are any available moves left on the board
bool isMovesLeft(vector<vector<char>>& board) {
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            if (board[row][col] == '_') return true;
    return false;
}

// Heuristic function to evaluate the board (returns a score)
int evaluate(vector<vector<char>>& board) {
    // Check rows for a win
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == PLAYER) return -10;
        }
    }

    // Check columns for a win
    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == PLAYER) return -10;
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == PLAYER) return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == PLAYER) return -10;
    }

    // No one has won yet
    return 0;
}

int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10) return score;

    if (score == -10) return score;

    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (board[row][col] == '_') {
                    board[row][col] = AI;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[row][col] = '_';
                }
            }
        }
        return best;
    }
    else {
        int best = numeric_limits<int>::max();

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (board[row][col] == '_') {
                    board[row][col] = PLAYER;

                    best = min(best, minimax(board, depth + 1, !isMax));

                    board[row][col] = '_';
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == '_') {
                board[row][col] = AI;

                int moveVal = minimax(board, 0, false);

                board[row][col] = '_';
                if (moveVal > bestVal) {
                    bestMove = {row, col};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
bool isGameOver(vector<vector<char>>& board) {
    int score = evaluate(board);
    if (score == 10) {
        cout << "AI wins!" << endl;
        return true;
    }
    if (score == -10) {
        cout << "Player wins!" << endl;
        return true;
    }
    if (!isMovesLeft(board)) {
        cout << "It's a tie!" << endl;
        return true;
    }
    return false;
}

int main() {
    vector<vector<char>> board = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    cout << "Tic-Tac-Toe Game!\n";
    printBoard(board);

    while (true) {
        int row, col;
        cout << "Enter your move (row and column: 0-2): ";
        cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != '_') {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        board[row][col] = PLAYER;

        printBoard(board);

        if (isGameOver(board)) break;

        // AI's move
        pair<int, int> aiMove = findBestMove(board);
        board[aiMove.first][aiMove.second] = AI;

        cout << "AI's move:\n";
        printBoard(board);

        if (isGameOver(board)) break;
    }

    return 0;
}
