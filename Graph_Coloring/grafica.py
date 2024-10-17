import matplotlib.pyplot as plt

# Datos de la tabla
nodos = [1, 2, 3, 4, 5, 6, 7, 8, 9]
greedy_time = [0.000048, 0.000032, 0.000025, 0.000036, 0.000050, 0.000037, 0.000078, 0.000050, 0.000104]
brute_force_time = [0.000049, 0.000037, 0.000143, 0.001136, 0.006801, 0.100838, 1.945826, 41.947912, 1085.553720]

# Crear gráfico
plt.figure(figsize=(10, 6))
plt.plot(nodos, greedy_time, marker='o', label='Greedy Time (seconds)', color='blue')
plt.plot(nodos, brute_force_time, marker='o', label='Brute Force Time (seconds)', color='red')

# Configurar el gráfico
plt.yscale('log')  # Usar escala logarítmica para visualizar mejor los tiempos
plt.xticks(nodos)
plt.xlabel('Número de Nodos')
plt.ylabel('Tiempo (segundos)')
plt.title('Comparación de Tiempos de Ejecución: Algoritmo Greedy vs Brute Force')
plt.legend()
plt.grid(True)
plt.tight_layout()

# Mostrar gráfico
plt.show()
