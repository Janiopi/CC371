#include <bits/stdc++.h> 
using namespace std; 

// DSU data structure 
// path compression + rank by union 
class DSU { 
	int* parent; 
	int* rank; 

public: 
	DSU(int n) 
	{ 
		parent = new int[n]; 
		rank = new int[n]; 

		for (int i = 0; i < n; i++) { 
			parent[i] = -1; 
			rank[i] = 1; 
		} 
	} 

	// Retorna el elemento representativo de un conjunto
	//(en este caso la raiz de un arbol)
	int find(int i) 
	{ 
		if (parent[i] == -1) 
			return i; 

		else{
			int result = find(parent[i]);
			parent[i]=result;
			return result;
		}

		 
	} 

	// Union por rank (altura) 
	void unite(int x, int y) 
	{ 
		int s1 = find(x); 
		int s2 = find(y); 

		if (s1 != s2) { 
			if (rank[s1] < rank[s2]) { 
				parent[s1] = s2; 
			} 
			else if (rank[s1] > rank[s2]) { 
				parent[s2] = s1; 
			} 
			else { 
				parent[s2] = s1; 
				rank[s1] += 1; 
			} 
		} 
	} 
}; 

class Graph { 
	vector<vector<int> > edgelist; 
	int V; 

public: 
	Graph(int V) { this->V = V; } 

	//Funcion añadir arista 
	void addEdge(int x, int y, int w) 
	{ 
		edgelist.push_back({ w, x, y }); 
	} 

	void kruskals_mst() 
	{ 
		// Ordenando las aristas por peso
		sort(edgelist.begin(), edgelist.end()); 

		// Inicializando el DSU 
		DSU s(V); 
		int ans = 0; 
		cout << "Las aristas del MST son: "<< endl; 
		for (auto edge : edgelist) { 
			int w = edge[0]; 
			int x = edge[1]; 
			int y = edge[2]; 

			// Si dos elementos tienen el mismo representante, quiere decir que pertenecen al mismo conjunto
            // Si unimos dichos dos elementos, se estaría formando un ciclo.
            //Entonces solo podemos unir vertices que no tengan el mismo representante

			if (s.find(x) != s.find(y)) { 
				s.unite(x, y); 
				ans += w; 
				cout << x << " -- " << y << " == " << w 
					<< endl; 
			} 
		} 
		cout << "El costo total del MST: " << ans<<endl; 
	} 
}; 

 
int main() 
{ 
	Graph g(8); 
	g.addEdge(0, 6, 53); 
	g.addEdge(0,1, 32); 
	g.addEdge(0, 2, 29); 
	g.addEdge(4, 3, 34); 
	g.addEdge(5, 3, 18);
    g.addEdge(7,4,46);
    g.addEdge(5,4,40);
    g.addEdge(0,5,60);
    g.addEdge(6,4,51);
    g.addEdge(7,0,31);
    g.addEdge(7,6,25);
    g.addEdge(7,1,21);

	 
	g.kruskals_mst(); 

	return 0; 
}
