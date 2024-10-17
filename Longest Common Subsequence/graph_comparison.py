import matplotlib.pyplot as plt

# Data for lengths and execution times
lengths = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
recursive_times = [6.931e-06, 2.738e-06, 5.989e-06, 1.7052e-05, 3.0149e-05, 0.000128385, 0.000435196, 0.00178298, 0.00757422, 0.0044022, 0.0467692, 0.0350002, 0.814793, 1.36013, 4.24824]
dynamic_times = [3.433e-06, 3.568e-06, 9.028e-06, 9.629e-06, 4.8893e-05, 0.000209545, 8.0684e-05, 0.00297868, 0.00127064, 0.000117138, 0.0009498, 2.9905e-05, 0.0337586, 6.2721e-05, 5.7406e-05]

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(lengths, recursive_times, label="Recursive Time", marker='o', color='r')
plt.plot(lengths, dynamic_times, label="Dynamic Time", marker='o', color='b')

# Add labels and title
plt.xlabel('Length of Strings')
plt.ylabel('Execution Time (seconds)')
plt.title('Comparison of LCS Recursive vs Dynamic Execution Times')
plt.legend()

# Display the plot
plt.grid(True)
plt.show()
