#include <iostream>
#include <limits>
using namespace std;

const int HUMAN = -1;
const int AI = 1;

int board[3][3] = {0};

bool isMovesLeft(int b[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == 0)
                return true;
    return false;
}

int evaluate(int b[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2])
        {
            if (b[row][0] == AI)
                return +10;
            else if (b[row][0] == HUMAN)
                return -10;
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col])
        {
            if (b[0][col] == AI)
                return +10;
            else if (b[0][col] == HUMAN)
                return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == AI)
            return +10;
        else if (b[0][0] == HUMAN)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == AI)
            return +10;
        else if (b[0][2] == HUMAN)
            return -10;
    }

    return 0;
}

int minimax(int b[3][3], int depth, bool isMax)
{
    int score = evaluate(b);

    if (score == 10)
        return score;
    if (score == -10)
        return score;
    if (!isMovesLeft(b))
        return 0;

    if (isMax)
    {
        int best = numeric_limits<int>::min();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b[i][j] == 0)
                {
                    b[i][j] = AI;
                    best = max(best, minimax(b, depth + 1, !isMax));
                    b[i][j] = 0;
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
                if (b[i][j] == 0)
                {
                    b[i][j] = HUMAN;
                    best = min(best, minimax(b, depth + 1, !isMax));
                    b[i][j] = 0;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(int b[3][3])
{
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (b[i][j] == 0)
            {
                b[i][j] = AI;
                int moveVal = minimax(b, 0, false);
                b[i][j] = 0;

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
    board[0][0] = HUMAN; // X (human)
    board[0][2] = AI;    // O (AI)
    board[1][1] = HUMAN;
    board[2][2] = AI;

    pair<int, int> bestMove = findBestMove(board);
    cout << "The best move is: Row = " << bestMove.first << ", Col = " << bestMove.second << endl;
    return 0;
}
