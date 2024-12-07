// Boruvka's algorithm para hallar el MST de un grafo conectado
#include <bits/stdc++.h>
using namespace std;


class Graph {
	int V; // No. vertices
	vector<vector<int> >graph; // Diccionario para almacenar grafo { {v11,v12,peso1},{v21,v22,peso2}...}

	// Funcion para encontrar la componente que contenga el vertice i
	// (path compression technique)
    
	int find(vector<int>& parent, int i)
	{
		if (parent[i] == i) {
			return i;
		}
		return find(parent, parent[i]);
	}

	// Funcion que une dos componentes x e y
	// rank: Rango matriz adyacencia
    // (union by rank)
	void unionSet(vector<int>& parent, vector<int>& rank,
				int x, int y)
	{
		int xroot = find(parent, x);
		int yroot = find(parent, y);

		// Añade el arbol de menor rank al de mayor rank
		// (Union by Rank)
		if (rank[xroot] < rank[yroot]) {
			parent[xroot] = yroot;
		}
		else if (rank[xroot] > rank[yroot]) {
			parent[yroot] = xroot;
		}
		// Si los ranks son iguales, escoge uno como root
		// incrementa  rank en uno
		else {
			parent[yroot] = xroot;
			rank[xroot]++;
		}
	}

public:
	Graph(int vertices)
	{
		V = vertices;
		graph = vector<vector<int> >();
	}

	
	void addEdge(int u, int v, int w)
	{
		graph.push_back({ u, v, w });
	}

	void boruvkaMST()
	{
		vector<int> parent(V);

		// An array to store index of the cheapest edge of
		// subset. It store [u,v,w] for each component
		vector<int> rank(V);
		vector<vector<int> > cheapest(V,
									vector<int>(3, -1));

		// Initially there are V different trees.
		// Finally there will be one tree that will be MST
		int numTrees = V;
		int MSTweight = 0;

		// Create V subsets with single elements
		for (int node = 0; node < V; node++) {
			parent[node] = node;
			rank[node] = 0;
		}

		// Keep combining components (or sets) until all
		// components are not combined into single MST
		while (numTrees > 1) {

			// Traverse through all edges and update
			// cheapest of every component
			for (int i = 0; i < graph.size(); i++) {

				// Find components (or sets) of two corners
				// of current edge
				int u = graph[i][0], v = graph[i][1],
					w = graph[i][2];
				int set1 = find(parent, u),
					set2 = find(parent, v);

				// If two corners of current edge belong to
				// same set, ignore current edge. Else check
				// if current edge is closer to previous
				// cheapest edges of set1 and set2
				if (set1 != set2) {
					if (cheapest[set1][2] == -1
						|| cheapest[set1][2] > w) {
						cheapest[set1] = { u, v, w };
					}
					if (cheapest[set2][2] == -1
						|| cheapest[set2][2] > w) {
						cheapest[set2] = { u, v, w };
					}
				}
			}

			// Consider the above picked cheapest edges and
			// add them to MST
			for (int node = 0; node < V; node++) {

				// Check if cheapest for current set exists
				if (cheapest[node][2] != -1) {
					int u = cheapest[node][0],
						v = cheapest[node][1],
						w = cheapest[node][2];
					int set1 = find(parent, u),
						set2 = find(parent, v);
					if (set1 != set2) {
						MSTweight += w;
						unionSet(parent, rank, set1, set2);
						printf("Arista %d-%d con peso %d "
							"incluida en el MST\n",
							u, v, w);
						numTrees--;
					}
				}
			}
			for (int node = 0; node < V; node++) {

				// reset cheapest array
				cheapest[node][2] = -1;
			}
		}
		printf("Peso del MST: %d\n", MSTweight);
	}   
};
int main()
{
	Graph g(12);
	g.addEdge(0, 6, 53);
    g.addEdge(0,1,32);
    g.addEdge(0,2,29);
    g.addEdge(4,3,34);
    g.addEdge(5,3,18);
    g.addEdge(7,4,46);
    g.addEdge(5,4,40);
    g.addEdge(0,5,60);
    g.addEdge(6,4,51);
    g.addEdge(7,0,31);
    g.addEdge(7,6,25);
    g.addEdge(7,1,21);

	g.boruvkaMST();
}
// This code is contributed by prajwal kandekar
