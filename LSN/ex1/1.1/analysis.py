import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

M=100000              # Total number of throws
N=100                 # Number of blocks
L=int(M/N)  

x = np.arange(N) * L  # Scale x-values correctly

# Read data from files
with open("average.txt", 'r') as file:
    numbers = np.array([float(line.strip()) for line in file if line.strip()])

with open("errors.txt", 'r') as file:
    err_prog = np.array([float(line.strip()) for line in file if line.strip()])

# Plot with error bars
plt.figure()

plt.errorbar(x, numbers - 0.5, yerr=err_prog, fmt='o', capsize=5, label="Data with Error Bars")

# Labels and grid
plt.xlabel('#throws')
plt.ylabel('<r> - 1/2')
plt.grid(True)
plt.legend()

x1 = np.arange(N) * L   
with open("variance.txt", 'r') as file:
    var_numbers = np.array([float(line.strip()) for line in file if line.strip()])

with open("errors.txt", 'r') as file:
    var_err_prog = np.array([float(line.strip()) for line in file if line.strip()])

plt.figure()
# Plot with error bars
plt.errorbar(x1, var_numbers - 1/12, yerr=var_err_prog, fmt='o', capsize=5, label="Data with Error Bars")

# Labels and grid
plt.xlabel('#throws')
plt.ylabel('<r> - 1/12')
plt.grid(True)
plt.legend()

with open("Chi.txt", 'r') as file:
    chi_squared = np.array([float(line.strip()) for line in file if line.strip()])

x_values = np.linspace(0, 1, len(chi_squared))
plt.figure()
plt.scatter(x_values,chi_squared)
plt.figure()
plt.hist(chi_squared, bins=30)
plt.xlabel('Chi-squared values')
plt.ylabel('Frequency')
plt.title('Chi-squared Histogram')
plt.grid(True)
plt.show()