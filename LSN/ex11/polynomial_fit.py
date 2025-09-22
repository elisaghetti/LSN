import numpy as np
import matplotlib.pyplot as plt

import os
os.environ["CUDA_VISIBLE_DEVICES"] = "-1"

# compose the NN model
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Input,Dense, Activation
import utils
from tensorflow.keras import backend as K
from tensorflow.keras.utils import get_custom_objects

def order3_polynomial(pars,x): return pars[0]*x**3+pars[1]*x**2+pars[2]*x +pars[3]

#target parameters
a = 3
b=-2
c=-3
d=4
pars = [a,b,c,d]
sigma = 0.1
data = utils.create_dataset(order3_polynomial,pars,sigma)
with open('./OUTPUT/polynomial_valid_data.csv',"w") as out:
    out.write('x_valid\ty_valid\ty_target\n')
    for i in range(len(data['x_valid'])):
        out.write(f"{data['x_valid'][i]}\t{data['y_valid'][i]}\t{data['y_target'][i]}\n")

Nl = [2,15,10]
Nn = [30,5,20]
hist =[]
pred = []
x = np.linspace(-1,1,50)
for i in range (3):
    model,history = run_sequentialNN(data,Nlayers=Nl[i],Nneurons=Nn[i],activation ='relu')
    y=model.predict(x)
    hist.append(history.history['loss'])
    pred.append(y)

with open(ntrain_file,"w") as out:
    out.write("ntrain\tepoch\tloss\n")
    for j,nt in enumerate(Nt):
        for i in range(len(ntrain_hist[j])):
            out.write(f"{nt}\t{i}\t{ntrain_hist[j][i]}\n")

