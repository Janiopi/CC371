def es_valido(laberinto, x, y, visitado):
    # Verifica si la celda está dentro de los límites del laberinto, si es un camino y no ha sido visitada
    return (0 <= x < len(laberinto) and 0 <= y < len(laberinto[0]) and
            laberinto[x][y] == 0 and not visitado[x][y])

def resolver_laberinto(laberinto, x, y, x_dest, y_dest, visitado, distancia_actual, menor_distancia):
    # Si llegamos a la salida, actualizamos la menor distancia si es menor que la actual
    if x == x_dest and y == y_dest:
        return min(menor_distancia, distancia_actual)

    # Marcamos la celda actual como visitada
    visitado[x][y] = True

    # Movimientos posibles: derecha, abajo, izquierda, arriba
    movimientos = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    
    for mov in movimientos:
        nuevo_x, nuevo_y = x + mov[0], y + mov[1]
        
        # Exploramos el siguiente paso si es válido y no lleva a una distancia mayor a la menor encontrada
        if es_valido(laberinto, nuevo_x, nuevo_y, visitado) and distancia_actual + 1 < menor_distancia:
            menor_distancia = resolver_laberinto(laberinto, nuevo_x, nuevo_y, x_dest, y_dest, visitado, distancia_actual + 1, menor_distancia)

    # Desmarcamos la celda actual para permitir otras rutas
    visitado[x][y] = False
    return menor_distancia

def encontrar_salida(laberinto, inicio, destino):
    x_ini, y_ini = inicio
    x_dest, y_dest = destino
    filas, columnas = len(laberinto), len(laberinto[0])
    
    # Matriz de celdas visitadas
    visitado = [[False] * columnas for _ in range(filas)]
    
    # Usamos un valor grande como distancia inicial mínima
    menor_distancia = float('inf')
    
    # Llamada inicial al algoritmo
    distancia_minima = resolver_laberinto(laberinto, x_ini, y_ini, x_dest, y_dest, visitado, 0, menor_distancia)
    
    # Si la distancia mínima no ha cambiado, significa que no hay camino hacia la salida
    return distancia_minima if distancia_minima != float('inf') else -1

laberinto = [
    [0, 1, 0, 0, 0],
    [0, 1, 0, 1, 0],
    [0, 0, 0, 1, 0],
    [0, 1, 0, 0, 0],
    [0, 0, 0, 1, 0]
]
inicio = (0, 0)
destino = (4, 4)

distancia = encontrar_salida(laberinto, inicio, destino)
print("La menor distancia para llegar a la salida es:", distancia)
