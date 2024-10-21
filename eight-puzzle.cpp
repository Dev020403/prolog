#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <set>

using namespace std;

const int N = 3;

const vector<vector<int>> GOAL = {{1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 0}};

struct State {
    vector<vector<int>> puzzle;
    int x, y;  

    bool operator==(const State &other) const {
        return puzzle == other.puzzle;
    }

    bool operator<(const State &other) const {
        return puzzle < other.puzzle;
    }
};

int rowMove[] = {-1, 1, 0, 0};
int colMove[] = {0, 0, -1, 1};

bool isGoal(State &state) {
    return state.puzzle == GOAL;
}

bool isValidMove(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPuzzle(vector<vector<int>> &puzzle) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------" << endl;
}

void printSolution(State finalState, map<State, State> &parent) {
    if (parent[finalState] == finalState) {
        printPuzzle(finalState.puzzle);
        return;
    }
    printSolution(parent[finalState], parent);
    printPuzzle(finalState.puzzle);
}

void BFS(State start) {
    map<State, State> parent;
    set<State> visited;
    queue<State> q;

    q.push(start);
    parent[start] = start;
    visited.insert(start);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (isGoal(current)) {
            cout << "Solution found:\n";
            printSolution(current, parent);
            return;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + rowMove[i];
            int newY = current.y + colMove[i];

            if (isValidMove(newX, newY)) {
                State next = current;
                swap(next.puzzle[current.x][current.y], next.puzzle[newX][newY]); 
                next.x = newX;
                next.y = newY;

                if (visited.find(next) == visited.end()) {
                    q.push(next);
                    visited.insert(next);
                    parent[next] = current;
                }
            }
        }
    }

    cout << "No solution found!" << endl;
}

int main() {
    vector<vector<int>> initialPuzzle = {{1, 2, 3},
                                         {4, 0, 5},
                                         {7, 8, 6}};
    
    int startX, startY;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (initialPuzzle[i][j] == 0) {
                startX = i;
                startY = j;
            }
        }
    }

    State start = {initialPuzzle, startX, startY};

    BFS(start);

    return 0;
}
