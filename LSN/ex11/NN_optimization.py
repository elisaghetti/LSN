import numpy as np
import matplotlib.pyplot as plt

import os
os.environ["CUDA_VISIBLE_DEVICES"] = "-1"

# compose the NN model
import tensorflow as tf
from tensorflow import keras

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Input,Dense, Activation
from tensorflow.keras import backend as K
from tensorflow.keras.utils import get_custom_objects
from utils import create_dataset, compare_NN, run_sequentialNN

def order3_polynomial(x,pars): return pars[0]*x**3+pars[1]*x**2+pars[2]*x +pars[3]

#target parameters
a = 3
b=-2
c=-3
d=4
pars = [a,b,c,d]
sigma = 0.1
data = create_dataset(order3_polynomial,sigma,-1,1,parameters=par&)

#OPTIMIZATION OF NN STRUCTURE: number of layers and neurons
Nlayers = [2,3,15,10,10]
Nneurons = [30,5,5,20]

#hist,pred,labels,scores = utils.compare_NNconfigurations(Nlayers,Nneurons,data)
hist,pred,labels,scores = compare_NN(data,Nlayers,Nneurons,'structure')

mask = scores==np.min(scores)
best_label=np.array(labels)[mask]
with open('optimal_nn.csv','w') as out:
    out.write("Choice of layers and neurons:\n")
    for i in range(len(hist)):
        out.write(f"{labels[i]}\t{scores[i]}\n")
    out.write(f"BEST: {best_label} \t evaluated loss: {np.min(scores)}\n\n")

activations = ['relu','sigmoid','tanh','selu']
Nl = 10
Nn =20
#ac_hist,ac_pred,ac_labels,ac_scores = utils.compare_activations(Nl,Nn,activations,data)
ac_hist,ac_pred,ac_labels,ac_scores = compare_NN(data,Nl,Nn,'activation',activations)


#try compostion of 2 best activations: first tanh i inner layers and relu in output, then opposite 

#tanh-relu

model1,hist1 = run_sequentialNN(data,Nl,Nneurons=Nn,activation='tanh',output_activation='relu',epochs=35)
score1 = model1.evaluate(data['x_valid'],data['y_valid'], batch_size=32, verbose=1)
ac_labels.append('inner: tanh, output: relu')
ac_scores.append(score1[0])

#relu-tanh

model2,hist2 = run_sequentialNN(data,Nl,Nneurons=Nn,activation='relu',output_activation='tanh',epochs=35)
score2 = model2.evaluate(data['x_valid'],data['y_valid'], batch_size=32, verbose=1)
ac_labels.append('inner: relu, output: tanh')
ac_scores.append(score2[0])

mask = ac_scores==np.min(ac_scores)
best_ac_label=np.array(ac_labels)[mask]

with open('optimal_nn.csv','a') as out:
    out.write("Choice of activation function:\n")
    for i in range(len(ac_scores)):
        out.write(f"{ac_labels[i]}\t{ac_scores[i]}\n")
    out.write(f"BEST: {best_ac_label} \t evaluated loss: {np.min(ac_scores)}\n\n")
#optimizer

opt_list = ['adam','sgd','adadelta']

#opt_hist,opt_pred,opt_labels,opt_scores = utils.compare_optimizers(Nlayer,Nneurons,opt_list,data)
opt_hist,opt_pred,opt_labels,opt_scores =compare_NN(data,Nl,Nn,'optimizer',opt_list)

mask = opt_scores==np.min(opt_scores)
best_opt_label=np.array(opt_labels)[mask]
with open('optimal_nn.csv','a') as out:
    out.write("Choice of optimizer:\n")
    for i in range(len(opt_scores)):
        out.write(f"{opt_labels[i]}\t{opt_scores[i]}\n")
    out.write(f"BEST: {best_opt_label} \t evaluated loss: {np.min(opt_scores)}\n\n")

loss_list = ['mse','mae','msle']

loss_hist,loss_pred,loss_labels,loss_scores =compare_NN(data,Nl,Nn,'loss',par_list=loss_list)

print(loss_scores)
mask = loss_scores==np.min(loss_scores)
best_loss_label=np.array(loss_labels)[mask]

with open('optimal_nn.csv','a') as out:
    out.write("Choice of loss function:\n")
    for i in range(len(loss_scores)):
        out.write(f"{loss_labels[i]}\t{loss_scores[i]}\n")
    out.write(f"BEST: {best_loss_label} \t evaluated loss: {np.min(loss_scores)}\n")