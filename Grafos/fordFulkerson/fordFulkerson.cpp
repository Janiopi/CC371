// C++ program for implementation of Ford Fulkerson
// algorithm
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

// Nro de Vertices
#define V 5

/*Return true si hay un camino desde el origen 's' al target 't' en el grafo 
. Parent[] almacenará el camino */
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
	// Marca todos los vertices como no visitados en un array
	
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	// Crea una queue, enqueue vertices origen y lo marca como visitado
	
	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS 
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {
		
				// Una vez se encuentra el target, solo se tiene que guardar su padre y termina 
				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// En caso de nunca alcanzar t desde s
	return false;
}

// Returna el flujo máximo desde s hacia t en un Grafo
int fordFulkerson(int graph[V][V], int s, int t)
{
	int u, v;


	//Crea un grafo donde se irán actualizando los flujos
	int rGraph[V][V];
	//Realiza una copia del grafo
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V]; // Este array almacena los caminos obtenidos por BFS

	int max_flow = 0; // No hay flujo inicial

	// Aumenta el flujo mientras exista un camino desde s hacia t
	while (bfs(rGraph, s, t, parent)) {
		// Halla el flujo maximo del camino actual.
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		// Actualiza los flujos en las aristas
	
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		// Suma el flujo de cada camino para obtener el flujo maximo
		max_flow += path_flow;
	}


	return max_flow;
}


int main()
{
	// Matriz de adyacencia de nuestro grafo
	int graph[V][V]
		= { { 0, 20, 30, 10, 0},
		{ 0, 0, 40, 0, 20},
		{ 0, 0, 0, 10, 20},
		{ 0, 0, 5, 0, 20},
		{ 0, 0, 0, 0, 0}
			 };

	cout << "El flujo máximo es "
		<< fordFulkerson(graph, 0, 4);

	return 0;
}
