#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <set>
using namespace std;

struct Node {
    vector<vector<int>> state;
    int empty_x, empty_y;
    int g, h;
    Node *parent;

    int f() const { return g + h; }
};

struct Compare {
    bool operator()(Node *a, Node *b) {
        return a->f() > b->f();
    }
};

int heuristic(const vector<vector<int>> &state) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    int h = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i][j] != 0 && state[i][j] != goal[i][j])
                h++;
        }
    }
    return h;
}

bool isGoal(const vector<vector<int>> &state) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    return state == goal;
}

vector<Node*> getNeighbors(Node *node) {
    vector<Node*> neighbors;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newX = node->empty_x + dx[i];
        int newY = node->empty_y + dy[i];

        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
            vector<vector<int>> newState = node->state;
            swap(newState[node->empty_x][node->empty_y], newState[newX][newY]);

            Node *neighbor = new Node{newState, newX, newY, node->g + 1, heuristic(newState), node};
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

void aStar(vector<vector<int>> start) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    set<vector<vector<int>>> visited;

    Node *root = new Node{start, 2, 2, 0, heuristic(start), nullptr};
    pq.push(root);
    visited.insert(start);

    while (!pq.empty()) {
        Node *current = pq.top();
        pq.pop();

        if (isGoal(current->state)) {
            cout << "Goal reached!\n";
            return;
        }

        vector<Node*> neighbors = getNeighbors(current);
        for (Node *neighbor : neighbors) {
            if (visited.find(neighbor->state) == visited.end()) {
                pq.push(neighbor);
                visited.insert(neighbor->state);
            }
        }
    }
}

int main() {
    vector<vector<int>> start = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    aStar(start);
    return 0;
}
