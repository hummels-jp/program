#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

// 
struct Node
{
    int x_;
    int y_;
    int g_; // the cost between start and current node
    int h_; // the estimate cost between current node and target node
    Node* parent_; // the preorder node

    Node(int x, int y, int g, int h, Node* parent = nullptr): x_(x), y_(y), g_(g), h_(h), parent_(parent)
    {

    }

    // get the current node cost
    int f() const
    {
        return g_ + h_;
    }
};

// functor, compare two node
struct node_compare
{
    bool operator()(const Node* a , const Node* b) const
    {
        return a->f() > b->f();
    }
};

// heuristic function, manhaton distances
int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1-x2) + abs(y1-y2);
}

vector<pair<int, int>> astar_path(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> end)
{
    int rows = grid.size();
    int columns = grid[0].size();

    // clost table store the node in the shortest path
    vector<vector<bool>> closed_table(rows, vector<bool>(columns, false));

    // open table store other nodes
    priority_queue<Node*, vector<Node*>, node_compare> open_table;

    // add the start Node into open table
    open_table.push(new Node(start.first, start.second, 
        0, heuristic(start.first, start.second, end.first, end.second)));

    // four directions 
    vector<pair<int, int>> dirs = {{0,1}, {1,0}, {0, -1}, {-1, 0}};

    while(open_table.empty() == false)
    {
        Node* cur = open_table.top();
        open_table.pop();

        // if find the end, reverse the path
        if(cur->x_ == end.first && cur->y_ == end.second)
        {
            vector<pair<int, int>> path;

            while(cur != nullptr)
            {
                path.push_back({cur->x_, cur->y_});
                cur = cur->parent_;
            }

            reverse(path.begin(), path.end());
            return path;
        }

        // add current node to closed table and update open table
        closed_table[cur->x_][cur->y_] = true;
        for(auto& direction : dirs)
        {
            int nx = cur->x_ + direction.first;
            int ny = cur->y_ + direction.second;

            if(nx >=0 && nx< rows && ny>=0&&ny< columns && grid[nx][ny]== 0 && closed_table[nx][ny] == false)
            {
                open_table.push(new Node(nx, ny, cur->g_ + 1, heuristic(nx, ny, end.first, end.second), cur));
            }
        }
    }

    // no path exists
    return {};
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
    auto path = astar_path(grid, start, goal);
    if (!path.empty()) {
        cout << "A*路径: ";
        for (auto& p : path) cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
    } else {
        cout << "无可行路径" << endl;
    }
    return 0;
}