#include <iostream>
#include <vector>
#include <climits>
#include <set>

using namespace std;

#define V 5

void dijkstra(int graph[V][V], int src) {
    vector<int> dist(V, INT_MAX); // Distance from src to i
    set<int> S; // Vertices with known shortest path
    vector<bool> U(V, true); // Vertices with unknown shortest path

    // Mark src as known
    U[src] = false;
    S.insert(src);
    dist[src] = 0;

    int u = src;
    while (!U.empty()) {
        // Update distances for neighbors of u
        for (int v = 0; v < V; ++v) {
            // U[v] : v is still in the unknown set
            // graph[u][v]: wether there is edge between u and V
            // dist[u] != INT_MAX: whether u can be arrived (from the start point to u)
            if (U[v] && graph[u][v] && dist[u] != INT_MAX) {
                // if the shortest path through u is smaller than the exit shortest value ,Update
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        // Find vertex in U with minimum dist
        int minDist = INT_MAX, minVertex = -1;
        for (int v = 0; v < V; ++v) {
            if (U[v] && dist[v] < minDist) {
                minDist = dist[v];
                minVertex = v;
            }
        }
        if (minVertex == -1) break; // No reachable vertex left
        S.insert(minVertex);
        U[minVertex] = false;
        
        // get the shortest node which is nearest to the source node
        u = minVertex;
    }

    cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < V; i++)
        cout << i << " \t\t " << dist[i] << endl;
}

int main() {
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };
    dijkstra(graph, 0);
    return 0;
}