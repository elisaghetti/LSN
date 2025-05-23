import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

with open("integral.txt", 'r') as file:
    numbers = np.array([float(line.strip()) for line in file if line.strip()])
N=100000;
N_blocks= 1000; 
n= N/N_blocks;

x = np.arange(N_blocks) * n  

plt.figure()

plt.scatter(x,numbers)
plt.show
