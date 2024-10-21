#include <iostream>
#include <stack>
#include <vector>
#include <set>
using namespace std;

struct Node
{
    vector<vector<int>> state;
    int empty_x, empty_y;
    int level;
    Node *parent;
};

bool isGoal(const vector<vector<int>> &state)
{
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    return state == goal;
}

void printState(const vector<vector<int>> &state)
{
    for (const auto &row : state)
    {
        for (int num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}

vector<Node *> getNeighbors(Node *node)
{
    vector<Node *> neighbors;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++)
    {
        int newX = node->empty_x + dx[i];
        int newY = node->empty_y + dy[i];

        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3)
        {
            vector<vector<int>> newState = node->state;
            swap(newState[node->empty_x][node->empty_y], newState[newX][newY]);

            Node *neighbor = new Node{newState, newX, newY, node->level + 1, node};
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

void dfs(vector<vector<int>> start)
{
    stack<Node *> s;
    set<vector<vector<int>>> visited;

    Node *root = new Node{start, 2, 2, 0, nullptr};
    s.push(root);
    visited.insert(start);

    while (!s.empty())
    {
        Node *current = s.top();
        s.pop();

        if (isGoal(current->state))
        {
            cout << "Goal reached in " << current->level << " moves.\n";
            printState(current->state);
            return;
        }

        vector<Node *> neighbors = getNeighbors(current);
        for (Node *neighbor : neighbors)
        {
            if (visited.find(neighbor->state) == visited.end())
            {
                s.push(neighbor);
                visited.insert(neighbor->state);
            }
        }
    }
}

int main()
{
    vector<vector<int>> start = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    dfs(start);
    return 0;
}
