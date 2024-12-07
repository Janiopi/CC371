// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

// iPair ==> Integer Pair
typedef pair<int, int> iPair;

class Graph {
    int V; // Nro de verices

    // Almacenemaos el vertice y el peso en pares por cada arista
    list<pair<int, int> >* adj;

public:
    Graph(int V); 

    //Añadir arista
    void addEdge(int u, int v, int w);

    //Dijkstra
    void shortestPath(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

//Calcula la distancia mínima hacia cualquier vértice partiendo del origen
void Graph::shortestPath(int src)
{
    // Esta parte no la entendi xd
    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    priority_queue<iPair, vector<iPair>, greater<iPair> >
        pq;

    // Todas las distancias se inicializan en infinito
    
    vector<int> dist(V, INF);

    // Inserta el nodo origen en la priority queue e inicializa su distancia como 0
    pq.push(make_pair(0, src));
    dist[src] = 0;

    // Finaliza cuando la priority queue este vacía 
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // 'i'  itera en todos los vertices adyacentes a un vertice en particular
        list<pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            // Obtiene el vertice y el peso del adyacente de u
            int v = (*i).first;
            int weight = (*i).second;

            // En caso que se encuentre una distancia mejor
            if (dist[v] > dist[u] + weight) {
                // Mejora el camino
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    
    printf("Vertice Distancia desde el origen\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}


int main()
{
    int V = 6;
    Graph g(V);

    //Añadiendo las aristas con sus respectivos pesos
    g.addEdge(0, 1, 41);
    g.addEdge(1,2, 51);
    g.addEdge(2, 3, 50);
    g.addEdge(4, 3, 36);
    g.addEdge(3, 5, 38);
    g.addEdge(3, 0, 45);
    g.addEdge(0, 5, 29);
    g.addEdge(5, 4, 21);
     g.addEdge(1,4,32);
    g.addEdge(4,2,32);
    g.addEdge(5,1,24);
    

    g.shortestPath(0);

    return 0;
}
