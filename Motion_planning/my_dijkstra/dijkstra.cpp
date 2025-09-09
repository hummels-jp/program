#include <iostream>
#include <vector>
#include <climits>
#include <set>

using namespace std;

#define V 5

void dijkstra(int graph[V][V], int source)
{
    //
    vector<int> dist(V, INT_MAX); // store the distance, Initialize with INT_MAX
    set<int> s_set; // node with known shortest distance;
    vector<bool> u_set(V, true); // node with unknown shortest distance, if in the unknown set, value is true

    // 1 mark src as known
    u_set[source] = false;
    s_set.insert(source);
    dist[source] = 0;

    // loop the unknown set
    int u = source;
    while(u_set.empty() == false)
    {
        // 1 update the distance in the unknown set
        for(int v =0; v < V; v++)
        {
            if(u_set[v]==true && graph[u][v]!=0 && dist[u]!= INT_MAX)
            {
                if(graph[u][v] + dist[u] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        // 2 find the node in u_set with the shortest distance
        int min_dist = INT_MAX;
        int min_index = -1;
        for(int v = 0; v< V; v++)
        {
            if(u_set[v] == true && dist[v] < min_dist)
            {
                min_dist = dist[v];
                min_index = v;
            }
        }

        // no node in unknown set;
        if(min_index == -1)
        {
            break;
        }

        // 3 remove the shortest node from u_set, insert into s_set;
        s_set.insert(min_index);
        u_set[min_index] = false;

        // 4 update the u, which is the nearest to the source node
        u = min_index;
    }

    // 5 output the result
    cout << "vertex num \t\t distance from source" << endl;
    for(int v =0; v < V; v++)
    {
        cout << v << "\t\t" << dist[v] << endl;
    }
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