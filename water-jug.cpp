#include <iostream>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct State
{
    int jug1, jug2;

    bool operator==(const State &other) const
    {
        return (jug1 == other.jug1 && jug2 == other.jug2);
    }

    bool operator<(const State &other) const
    {
        if (jug1 == other.jug1)
            return jug2 < other.jug2;
        return jug1 < other.jug1;
    }
};

void printSolution(State finalState, map<State, State> parent)
{
    if (parent[finalState] == finalState)
    {
        cout << "(" << finalState.jug1 << ", " << finalState.jug2 << ")" << endl;
        return;
    }
    printSolution(parent[finalState], parent);
    cout << "(" << finalState.jug1 << ", " << finalState.jug2 << ")" << endl;
}

void BFS(int a, int b, int target)
{
    set<State> visited;
    map<State, State> parent;
    queue<State> q;

    State initialState = {0, 0};
    q.push(initialState);
    visited.insert(initialState);
    parent[initialState] = initialState;

    while (!q.empty())
    {
        State current = q.front();
        q.pop();

        if (current.jug1 == target || current.jug2 == target)
        {
            printSolution(current, parent);
            return;
        }

        vector<State> nextStates = {
            {a, current.jug2},
            {current.jug1, b},
            {0, current.jug2},
            {current.jug1, 0},
            {min(a, current.jug1 + current.jug2), current.jug1 + current.jug2 - min(a, current.jug1 + current.jug2)},
            {current.jug1 + current.jug2 - min(b, current.jug1 + current.jug2), min(b, current.jug1 + current.jug2)}};

        for (auto nextState : nextStates)
        {
            if (visited.find(nextState) == visited.end())
            {
                visited.insert(nextState);
                q.push(nextState);
                parent[nextState] = current;
            }
        }
    }

    cout << "No solution found!" << endl;
}

int main()
{
    int a = 4, b = 3, target = 2;
    BFS(a, b, target);
    return 0;
}
