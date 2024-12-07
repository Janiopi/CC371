// C++ program to find single source shortest path Using Bellman
// -Ford algorithm

#include <iostream>
#include <vector>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    
    // Initially distance from source to all 
    // other vertices is not known(Infinite).
    vector<int> dist(V, 1e8);
    dist[src] = 0;
  
    // Relaxation of all the edges V times, not (V - 1) as we
    // need one additional relaxation to detect negative cycle
    for (int i = 0; i < V; i++) {
        for (vector<int> edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                
                // If this is the Vth relaxation, then there is
                // a negative cycle
                if(i == V - 1)
                    return {-1};
               
                // Update shortest distance to node v
                dist[v] = dist[u] + wt;
            }
        }
    }

    return dist;
}

int main() {
    int V = 6;
    vector<vector<int>> edges = {{0, 1, 41}, {0, 5, 29}, {1, 2, 51}, 
                                 {1, 4, 32}, {2, 3, 50},{3,0,15},
                                 {3,5,-38},{4,3,36},{4,2,32},
                                 {5,1,-29},{5,4,21}};

    int src = 0;
    vector<int> ans = bellmanFord(V, edges, src);
    for (int dist : ans) 
        cout << dist << " ";
    return 0;
}