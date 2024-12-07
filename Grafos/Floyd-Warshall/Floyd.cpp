
#include <bits/stdc++.h>
using namespace std;


#define V 4

#define INF 99999

void printSolution(int dist[][V]);

void floydWarshall(int dist[][V])
{

    int i, j, k;

    for (k = 0; k < V; k++) {
         for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != INF
                        && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    
    printSolution(dist);
}


void printSolution(int dist[][V])
{
    cout << "La siguiente mtriz imprime las distancias mínimas entre cualquier par de vértices\n ";
            
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF"
                     << " ";
            else
                cout << dist[i][j] << "   ";
        }
        cout << endl;
    }
}

int main()
{
    //Matriz de adyacencia del grafo
    int graph[V][V] = { { INF, 8, -1, INF },
                        { 6, INF, INF, 3 },
                        { INF, 5, INF, INF },
                        { INF, INF, 2, INF } };

    
    floydWarshall(graph);
    return 0;
}

// Créditos a Mythri J L
