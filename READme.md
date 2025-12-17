# Numerical Simulation Laboratory – Exercises (2025)

This repository contains the **12 exercises** of the *Numerical Simulation Laboratory* course delivered in **2025**.

For **each exercise**, I included a Jupyter notebook called:

- `analysis.ipynb`

In this notebook, I explain in detail how the exercise was solved and present the **main results and plots** obtained from the simulations.

For every exercise, there is also an **`output/` directory**, which contains the **numerical data files** produced by the simulations and used in the analysis notebooks.

## Repository structure

- **Exercises folders**  
  Each exercise is organized in its own directory and includes:
  - `analysis.ipynb`: explanation of the method and results  
  - `output/`: numerical outputs of the simulations  

- **`Classes/` directory**  
  This folder contains **libraries and C++ classes** that are shared among multiple exercises (e.g. random number generators, statistical utilities, common data structures).

- **`nsl_simulator/` directory**  
  All exercises that make use of the **molecular dynamics simulator** are collected in this folder.