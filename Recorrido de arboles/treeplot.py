import matplotlib.pyplot as plt
import networkx as nx

def read_tree(filename):
    with open(filename, 'r') as f:
        data = f.read().strip().split()
    return list(map(int, data))

def plot_tree(nodes, rotate=False):
    G = nx.Graph()
    pos = {}
    labels = {}
    
    if not nodes:
        return

    queue = [(0, 0)]  # (index, depth)
    while queue:
        index, depth = queue.pop(0)
        if index >= len(nodes) or nodes[index] == -1:
            continue
        node = nodes[index]
        pos[node] = (depth, index)

        # Adjust positions for rotation
        x, y = depth, index
        if rotate:
            pos[node] = (y, -x)  # Swap x and y to rotate the tree
        else:
            pos[node] = (x, -y)

        labels[node] = str(node)

        left_index = 2 * index + 1
        right_index = 2 * index + 2
        if left_index < len(nodes) and nodes[left_index] != -1:
            G.add_edge(node, nodes[left_index])
            queue.append((left_index, depth + 1))
        if right_index < len(nodes) and nodes[right_index] != -1:
            G.add_edge(node, nodes[right_index])
            queue.append((right_index, depth + 1))
    
    # Draw the graph
    nx.draw(G, pos, labels=labels, with_labels=True, node_size=1000, node_color='lightblue', font_size=30, font_weight='bold')
    plt.show()




nodes = read_tree('generated_tree.txt')
plot_tree(nodes,True)
