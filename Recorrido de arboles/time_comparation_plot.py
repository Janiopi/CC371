import matplotlib.pyplot as plt
import numpy as np

# Datos de la tabla
n_values = [10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]
inorder = [4.14e-06, 4.18e-05, 0.00071953, 0.0115278, 0.068623, 0.928443, 10.418, 139.775]
postorder = [3.03e-06, 3.93e-05, 0.000339778, 0.00232591, 0.0817676, 0.947642, 10.3861, 149.183]
preorder = [3.06e-06, 4.06e-05, 0.000348268, 0.00207519, 0.0932903, 0.954555, 10.5253, 153.865]
breadth_first = [0.000454904, 0.000422282, 0.00111289, 0.0311468, 0.150766, 1.45075, 14.607, 181.819]
n_values_2 = [10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]


# Crear el gráfico de líneas
plt.figure(figsize=(10, 6))

plt.plot(n_values, inorder, label='Inorder', marker='o')
plt.plot(n_values, postorder, label='PostOrder', marker='o')
plt.plot(n_values, preorder, label='PreOrder', marker='o')
plt.plot(n_values, breadth_first, label='BreadthFirst', marker='o')


# Configurar escala logarítmica en el eje x
plt.xscale('log')

# Etiquetas y título
plt.xlabel('n (Tamaño del árbol)')
plt.ylabel('Tiempo (segundos)')
plt.title('Comparación de Tiempos de Ejecución de Recorridos en Árboles')
plt.legend()

# Mostrar el gráfico
plt.grid(True)
plt.tight_layout()
plt.show()
