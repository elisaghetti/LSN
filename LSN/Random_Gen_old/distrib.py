import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

M=100000              # Total number of throws

 # Scale x-values correctly

# Read data from file
filename = "expo.txt"
data = np.loadtxt(filename)  # Load the numbers from the file

# Plot histogram
plt.hist(data, bins=100, density=True, alpha=0.6, color='b', label="Empirical Data")



# Etichette e legenda
plt.xlabel("Valore")
plt.ylabel("Densità relativa")
plt.title("Istogramma Normalizzato al Massimo della Distribuzione")
plt.legend()
plt.grid(True)
plt.xlim(-700,200)

# Mostra il grafico
plt.show()
