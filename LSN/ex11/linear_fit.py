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


def line (pars,x) : return pars[0]*x +pars[1]

m = 2
b=1
pars = [m,b]
sigma = 0
#dependence of loss on number of epochs

epochs_data =utils.create_dataset(line,pars,sigma)
epochs_model,epochs_history = utils.run_sequentialNN(epochs_data,Nlayers=1,Nneurons=1,optimizer = 'sgd')
epochs_hist =epochs_history.history['loss']
epochs_file = './OUTPUT/epochs_loss.csv'

with open(epochs_file,"w") as out:
    out.write("epoch\tloss\n")
    for i in range(len(epochs_hist)):
        out.write(f"{i}\t{epochs_hist[i]}\t{epochs_history.history['val_loss'][i]}\n")

#dependence of loss on training dataset size
ntrain_hist,scores = []
Ntmax = 1200
Nt = np.linspace(300,1200,11)
ntrain_data_max = utils.create_dataset(line,pars,sigma,npoints=Ntmax)


for n in Nt:
    ntrain_data = utils.cut_dataset(ntrain_data_max,int(n))
    model,history = utils.run_sequentialNN(ntrain_data,Nlayers=1,Nneurons=1,optimizer = 'sgd')
    ntrain_loss.append(history.history['loss'])
    score= model.evaluate(X_test, Y_test,verbose=1)
    scores.append(score)
ntrain_scorefile  = './OUTPUT/ntrain_score.csv' 
with open(ntrain_scorefile,"w") as out:
    out.write("ntrain\tscore_loss\tscore_acc\n")
    for i,nt in enumerate(Nt):
        out.write(f"{nt}\t{scores[i][0]}\t{scores[i][1]}")
    out.close()
ntrain_file  = './OUTPUT/ntrain_loss.csv'
with open(ntrain_file,"w") as out:
    out.write("ntrain\tepoch\tloss\n")
    for j,nt in enumerate(Nt):
        for i in range(len(ntrain_hist[j])):
            out.write(f"{nt}\t{i}\t{ntrain_hist[j][i]}\n")


#dependence of loss on sigma
sigmas = np.linspace(0.1,1.6,11)
print(sigmas)
sigma_hist,sigma_scores = [],[]
x_train,x_valid = utils.generate_xpoints(-1,1,500)

for sigma in sigmas: 
    data = utils.create_dataset(line,pars,sigma,x_train = x_train,x_valid=x_valid)
    sigma_model,sigma_history = utils.run_sequentialNN(data,Nlayers=1,Nneurons=1,optimizer = 'sgd')
    sigma_hist.append(sigma_history.history['loss'])
    score= sigma_model.evaluate(X_test, Y_test,verbose=1)
    sigma_scores.append(score)
sigma_scorefile  = './OUTPUT/sigma_score.csv' 
with open(sigma_scorefile,"w") as out:
    out.write("sigma\tscore_loss\tscore_acc\n")
    for i,nt in enumerate(Nt):
        out.write(f"{nt}\t{sigma_scores[i][0]}\t{sigma_scores[i][1]}")
    out.close()
sigma_file  = './OUTPUT/sigma_loss.csv'
with open(sigma_file,"w") as out:
    out.write("sigma\tepoch\tloss\n")
    for j,sigma in enumerate(sigmas):
        for i in range(len(sigma_hist[j])):
            out.write(f"{sigma}\t{i}\t{sigma_hist[j][i]}\n")