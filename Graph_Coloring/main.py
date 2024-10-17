import random
import itertools
import networkx as nx
import matplotlib.pyplot as plt
import time


def is_valid_coloring(graph, coloring):
    for u, v in graph.edges():
        if coloring[u] == coloring[v]:
            return False
    return True


def greedy_coloring(graph):
    coloring = {}
    for node in graph.nodes():
        #Obtiene los colores de los nodos adyacentes
        adjacent_colors = {coloring.get(neighbor) for neighbor in graph.neighbors(node)}
        #Obtiene el menor color posible, de tal forma que sea diferente a los adyacentes
        coloring[node] = next(color for color in itertools.count() if color not in adjacent_colors)
    return coloring


def brute_force_coloring(graph):
    n_nodes = len(graph.nodes())
    
    # Prueba con diferentes números de colores
    for k in range(1, n_nodes + 1):
        # Genera todas las combinaciones posibles de k colores para n nodos
        for coloring in itertools.product(range(k), repeat=n_nodes):
            coloring_dict = {node: coloring[node] for node in graph.nodes()}
            if is_valid_coloring(graph, coloring_dict):
                return coloring_dict, k  # Retorna un coloreo válido y el número cromático
    return None, None  # No existe coloreo válido

def measure_execution_times(step_sizes, output_file):
    with open(output_file, 'w') as f:
        f.write("Nodes,Greedy Time (seconds),Brute Force Time (seconds)\n")  # Header for the output file
        
        for n_nodes in step_sizes:
            print(f"Running tests for {n_nodes} nodes...")

            # Create a graph
            G = nx.Graph()
            G.add_nodes_from(range(n_nodes))

            # Randomly add edges between nodes
            for i in range(n_nodes):
                for j in range(i+1, n_nodes):
                    #if random.random() < 0.3:  # Sparse graph with random edges
                        G.add_edge(i, j)

            # Measure time for Greedy Coloring
            start_time = time.time()
            greedy_coloring(G)
            greedy_time = time.time() - start_time

            # Measure time for Brute Force Coloring
            start_time = time.time()
            brute_force_coloring(G)
            brute_force_time = time.time() - start_time

            # Write the results to the file
            f.write(f"{n_nodes},{greedy_time:.6f},{brute_force_time:.6f}\n")
            print(f"Nodes: {n_nodes}, Greedy Time: {greedy_time:.6f} s, Brute Force Time: {brute_force_time:.6f} s")




n_nodes = int(input("Digite el número de nodos: "))

print("Opciones de coloreo")
print("1. Fuerza bruta")
print("2. Greedy ")
print("3. Ejecutar múltiples veces")

opcion = input("Escoja una opción: ")

# Create the graph
G = nx.Graph()
G.add_nodes_from(range(n_nodes))

# Randomly add edges between nodes
for i in range(n_nodes):
    for j in range(i+1, n_nodes):
        if random.random() < 0.3:  # Lower probability for sparse graph
            G.add_edge(i, j)

coloring_result = None
k = 0

# Choose coloring method
match opcion:
    case '1':
        start_time = time.time()
        coloring_result, k = brute_force_coloring(G)
        end_time = time.time()
        if coloring_result is None:
            print("No valid coloring found.")
        else:
            print(f"Brute force execution time: {end_time-start_time:.6f}seconds")
    case '2':
        start_time = time.time()
        coloring_result = greedy_coloring(G)
        end_time=time.time()
        k = len(set(coloring_result.values()))
        print(f"Greedy execution time: {end_time-start_time:.6f}seconds")

    case '3':
        # Define the step sizes for the number of nodes (e.g., 1, 10, 20, 30, ...)
        step_sizes = list(range(1, 11, 1))  # Adjust the range and step as needed

        # Specify the output file for writing the times 
        output_file = "graph_coloring_times.txt"

        # Measure execution times and save to the file
        measure_execution_times(step_sizes, output_file)
        print(f"Execution times have been saved to {output_file}.")




    case _:
        print("Opción inválida")
        exit()

# Display the result
if coloring_result:
    print('Coloring: ', coloring_result)
    print('Chromatic number (minimum number of colors):', k)

    # Visualization
    color_map = [coloring_result[node] for node in G.nodes()]
    nx.draw(G, node_color=color_map, with_labels=True, font_weight='bold')
    plt.show()
else:
    print("No coloring could be applied.")
