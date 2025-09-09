#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

struct Node {
    int x, y;
    int g, h; // g: 起点到当前点的代价，h: 启发式估价
    Node* parent;
    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}
    int f() const { return g + h; }
};

struct cmp {
    bool operator()(const Node* a, const Node* b) const {
        return a->f() > b->f();
    }
};

int heuristic(int x1, int y1, int x2, int y2) {
    // 曼哈顿距离
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<pair<int, int>> AStar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int m = grid.size(), n = grid[0].size();
    
    vector<vector<bool>> closed(m, vector<bool>(n, false));

    priority_queue<Node*, vector<Node*>, cmp> open;
    open.push(new Node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second)));

    vector<pair<int, int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}}; // 四方向

    while (!open.empty()) {
        Node* cur = open.top(); open.pop();
        if (cur->x == goal.first && cur->y == goal.second) {
            // 回溯路径
            vector<pair<int, int>> path;
            while (cur) {
                path.push_back({cur->x, cur->y});
                cur = cur->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        closed[cur->x][cur->y] = true;
        for (auto& d : dirs) {
            int nx = cur->x + d.first, ny = cur->y + d.second;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 0 && !closed[nx][ny]) {
                open.push(new Node(nx, ny, cur->g + 1, heuristic(nx, ny, goal.first, goal.second), cur));
            }
        }
    }
    return {}; // 无路径
}

int main() {
    vector<vector<int>> grid = {
        {0,0,0,0,0},
        {1,1,0,1,0},
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,0,0}
    };
    pair<int, int> start = {0, 0}, goal = {4, 4};
    auto path = AStar(grid, start, goal);
    if (!path.empty()) {
        cout << "A*路径: ";
        for (auto& p : path) cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
    } else {
        cout << "无可行路径" << endl;
    }
    return 0;
}