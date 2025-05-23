import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

M=100000              # Total number of throws

 # Scale x-values correctly

# Read data from file
filename = "expo.txt"
data_exp = np.loadtxt(filename)  # Load the numbers from the file

filename = "unif.txt"
data_unif = np.loadtxt(filename)

filename = "cauchy.txt"
data_cauchy = np.loadtxt(filename)

# Plot histogram
plt.figure()
plt.hist(data_exp, density=True, alpha=0.6, color='b', label="Empirical Data")
"""
plt.figure()
plt.hist(data_unif, bins=30density=True, alpha=0.6, color='b', label="Empirical Data")

plt.figure()
plt.hist(data_cauchy, bins=30, density=True, alpha=0.6, color='b', label="Empirical Data")

"""



# Mostra il grafico
plt.show()
