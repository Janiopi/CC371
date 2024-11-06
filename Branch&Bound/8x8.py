import heapq

class Nodo:
    def __init__(self, estado, padre=None, g=0, h=0):
        self.estado = estado
        self.padre = padre
        self.g = g  # costo desde el estado inicial hasta el estado actual
        self.h = h  # heurística (número de fichas mal colocadas)
        self.f = g + h  # función de costo total

    def __lt__(self, other):
        return self.f < other.f  # ordena por el costo total

objetivo = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]  # Estado objetivo del 8-puzzle

def calcular_heuristica(estado):
    """Calcula la heurística h(X) como el número de fichas mal colocadas."""
    h = 0
    for i in range(3):
        for j in range(3):
            if estado[i][j] != 0 and estado[i][j] != objetivo[i][j]:
                h += 1
    return h

def es_objetivo(estado):
    """Verifica si el estado actual es el objetivo."""
    return estado == objetivo

def generar_movimientos(estado):
    """Genera los movimientos válidos para el espacio vacío (0)."""
    movimientos = []
    x, y = next((i, j) for i in range(3) for j in range(3) if estado[i][j] == 0)  # Encuentra el 0

    if x > 0: movimientos.append((x - 1, y))  # Arriba
    if x < 2: movimientos.append((x + 1, y))  # Abajo
    if y > 0: movimientos.append((x, y - 1))  # Izquierda
    if y < 2: movimientos.append((x, y + 1))  # Derecha
    return movimientos

def aplicar_movimiento(estado, mov):
    """Aplica un movimiento y devuelve el nuevo estado."""
    x, y = next((i, j) for i in range(3) for j in range(3) if estado[i][j] == 0)
    nuevo_estado = [fila[:] for fila in estado]
    nuevo_estado[x][y], nuevo_estado[mov[0]][mov[1]] = nuevo_estado[mov[0]][mov[1]], nuevo_estado[x][y]
    return nuevo_estado

def resolver_8_puzzle(inicial):
    """Resuelve el 8-puzzle usando A* con heurística."""
    pq = []  # Cola de prioridad
    nodo_raiz = Nodo(inicial, g=0, h=calcular_heuristica(inicial))
    heapq.heappush(pq, nodo_raiz)

    visitados = set()
    visitados.add(tuple(map(tuple, inicial)))

    while pq:
        nodo = heapq.heappop(pq)
        
        if es_objetivo(nodo.estado):
            return reconstruir_camino(nodo)
        
        for mov in generar_movimientos(nodo.estado):
            hijo_estado = aplicar_movimiento(nodo.estado, mov)
            hijo_estado_tupla = tuple(map(tuple, hijo_estado))
            
            if hijo_estado_tupla in visitados:
                continue
            
            visitados.add(hijo_estado_tupla)
            hijo_nodo = Nodo(hijo_estado, padre=nodo, g=nodo.g + 1, h=calcular_heuristica(hijo_estado))
            heapq.heappush(pq, hijo_nodo)

    return "No se encontró solución"

def reconstruir_camino(nodo):
    """Reconstruye el camino desde el nodo raíz hasta el objetivo."""
    camino = []
    while nodo:
        camino.append(nodo.estado)
        nodo = nodo.padre
    return camino[::-1]

# Estado inicial de ejemplo
estado_inicial = [[1, 2, 3], [4, 0, 6], [7, 5, 8]]

# Ejecutar el algoritmo
camino_solucion = resolver_8_puzzle(estado_inicial)

# Mostrar el camino de solución
for paso, estado in enumerate(camino_solucion):
    print(f"Paso {paso}:")
    for fila in estado:
        print(fila)
    print()

