#include <iostream>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = '_';

void printBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                return true;
            }
        }
    }
    return false;
}

int evaluate(char board[3][3])
{

    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == COMPUTER)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            if (board[0][col] == COMPUTER)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == COMPUTER)
            return +10;
        else if (board[0][0] == PLAYER)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == COMPUTER)
            return +10;
        else if (board[0][2] == PLAYER)
            return -10;
    }

    return 0;
}

int minimax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);
    if (score == 10)
        return score - depth;

    if (score == -10)
        return score + depth;
    if (!isMovesLeft(board))
        return 0;

    if (isMax)
    {
        int best = numeric_limits<int>::min();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = COMPUTER;

                    best = max(best, minimax(board, depth + 1, !isMax));

                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    else
    {
        int best = numeric_limits<int>::max();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(char board[3][3])
{
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;
                if (moveVal > bestVal)
                {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main()
{
    char board[3][3] = {
        {'X', 'O', 'X'},
        {'O', 'O', 'X'},
        {'_', '_', '_'}};

    cout << "Initial board:" << endl;
    printBoard(board);

    pair<int, int> bestMove = findBestMove(board);

    cout << "The best move for the computer is: " << endl;
    cout << "Row: " << bestMove.first << ", Column: " << bestMove.second << endl;

    board[bestMove.first][bestMove.second] = COMPUTER;

    cout << "Board after the computer's move:" << endl;
    printBoard(board);

    return 0;
}
