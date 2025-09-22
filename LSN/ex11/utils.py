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

def generate_xpoints(npoints =500):
    np.random.seed(0)
    x_train = np.random.uniform(-1, 1, npoints)
    x_valid = np.random.uniform(-1, 1, 50)
    x_valid.sort()
    return x_train,x_valid

def create_dataset(function,parameters,sigma,x_train =None,x_valid=None,npoints =500) :
    if (x_train is None or x_valid is None):x_train,x_valid = generate_xpoints(npoints)
    y_target = function(parameters,x_valid)

    y_train = np.random.normal(function(parameters,x_train),sigma) # actual measures from which we want to guess regression parameters
    y_valid = np.random.normal(function(parameters,x_valid),sigma)

    dataset = {
        "x_valid" : x_valid,
        "y_valid" : y_valid,
        "y_target": y_target,
        "x_train" : x_train,
        "y_train" : y_train     
    }
    return dataset

def cut_dataset(data, cut_pos):
    cut_dataset = {
        "x_valid": data['x_valid'][:cut_pos],
        "y_valid": data['y_valid'][:cut_pos],
        "y_target": data['y_target'][:cut_pos],
        "x_train": data['x_train'][:cut_pos],
        "y_train": data['y_train'][:cut_pos]
    }
    return cut_dataset

def run_sequentialNN (data,Nlayers, Nneurons=None, activation = None, output_activation = None,epochs =70,optimizer = 'adam',loss = 'mse',create_rand_Nn = False) :
    print('begin run')
    model = Sequential()
    model.add(Input(shape=(1,)))
    if (Nlayers >1) :
        for j in range (Nlayers-1):
            if (create_rand_Nn): 
                if (j==0) : print('Generated neurons:')
                Nneurons = np.random.randint(1,30)
                print(Nneurons)
            model.add(Dense(Nneurons,activation = activation))
    model.add(Dense(1,activation = output_activation))
    model.compile(optimizer=optimizer, loss=loss, metrics=[loss])
    history = model.fit(x=data['x_train'], y=data['y_train'], 
          batch_size=32, epochs=epochs,
          shuffle=True, # a good idea is to shuffle input before at each epoch
          validation_data=(data['x_valid'], data['y_valid']),verbose =0)

    return model,history

def compare_loss_epochs(function,pars,sigma) :
    epochs_data =create_dataset(function,pars,sigma)
    epochs_model,epochs_history = run_sequentialNN(epochs_data,Nlayers=1,Nneurons=1,optimizer = 'sgd')
    epochs_hist =epochs_history.history['loss']

    return epochs_hist

def compare_loss_Ntrain(function,pars,sigma,Nt) :
    Ntmax = int(np.max(Nt))
    ntrain_data_max = create_dataset(function,pars,sigma,npoints=Ntmax)
    ntrain_hist=[]
    for n in Nt:
        ntrain_data = cut_dataset(ntrain_data_max,int(n))
        model,history = run_sequentialNN(ntrain_data,Nlayers=1,Nneurons=1,epochs=35,optimizer = 'sgd')
        ntrain_hist.append(history.history['loss'])

    return ntrain_hist

def compare_loss_sigma(function,pars,sigmas) :

    x_train,x_valid = generate_xpoints()
    sigma_hist=[]
    for sigma in sigmas: 
        data = create_dataset(function,pars,sigma,x_train = x_train,x_valid=x_valid)
        sigma_model,sigma_history =run_sequentialNN(data,Nlayers=1,Nneurons=1,epochs=35,optimizer = 'sgd')
        sigma_hist.append(sigma_history.history['loss'])
    return sigma_hist

def compare_NN(data,Nl,Nn,id,par_list=None):
    x = np.linspace(-1,1,50)
    hist =[]
    pred = []
    labels=[]
    scores=[]
    if (par_list is None): n_var = len(Nl)
    else : n_var =len(par_list)
    for i in range (n_var):
        
        if(id=='structure'):
          
            if (i==n_var-1):  
                model,history = run_sequentialNN(data,Nlayers=Nl[i],Nneurons=None,activation ='relu',create_rand_Nn=True,epochs=50)
                labels.append(f'layers= {Nl[i]} neurons = random')
            else : 
                model,history = run_sequentialNN(data,Nlayers=Nl[i],Nneurons=Nn[i],activation ='relu',epochs=50)
                labels.append(f'layers= {Nl[i]} neurons = {Nn[i]}')

        if(id=='activation'):
            model,history = run_sequentialNN(data,Nlayers=Nl,Nneurons=Nn,activation =par_list[i],epochs=50)
            labels.append(par_list[i])

        if(id =='optimizer'):
            model,history = run_sequentialNN(data,Nlayers=Nl,Nneurons=Nn,activation ='relu',epochs=50,optimizer = par_list[i])
            labels.append(par_list[i])
        
        if(id =='loss'):
            model,history = run_sequentialNN(data,Nlayers=Nl,Nneurons=Nn,activation ='relu',epochs=50,optimizer = 'adam',loss = par_list [i])
            labels.append(par_list[i])
        #print(labels[i])
        
        y=model.predict(x)
        score = model.evaluate(data['x_valid'],data['y_valid'], batch_size=32, verbose=1)
        scores.append(score[0])
        hist.append(history.history['loss'])
        pred.append(y)

    return hist,pred,labels,scores

def compare_NNconfigurations(Nl,Nn,data) :
    x = np.linspace(-1,1,50)
    hist =[]
    pred = []
    labels=[]
    scores=[]

    for i in range (len(Nl)):
        if (i==len(Nl)-1):  
            model,history = run_sequentialNN(data,Nlayers=Nl[i],Nneurons=None,activation ='relu',create_rand_Nn=True,epochs=35)
            labels.append(f'layers= {Nl[i]} neurons = random')
        else : 
            model,history = run_sequentialNN(data,Nlayers=Nl[i],Nneurons=Nn[i],activation ='relu',epochs=35)
            labels.append(f'layers= {Nl[i]} neurons = {Nn[i]}')
        print(labels[i])
        y=model.predict(x)
        score = model.evaluate(data['x_valid'],data['y_valid'], batch_size=32, verbose=1)
        scores.append(score[0])
        hist.append(history.history['loss'])
        pred.append(y)
        

    return hist,pred,labels,scores

def compare_activations(Nl,Nn,activ_list,data): 
    hist =[]
    pred = []
    labels = []
    scores=[]
    x = np.linspace(-1,1,50)
    for i in range (len(activ_list)):
        model,history = run_sequentialNN(data,Nlayers=Nl,Nneurons=Nn,activation =activ_list[i],epochs=35)
        y=model.predict(x)
        score = model.evaluate(data['x_valid'], data['y_valid'], batch_size=32, verbose=1)
        scores.append(score[0])
        hist.append(history.history['loss'])
        pred.append(y)
        labels.append(activ_list[i])

    return hist,pred,labels,scores

def compare_optimizers(Nl,Nn,opt_list,data):
    hist =[]
    pred = []
    labels = []
    scores=[]
    x = np.linspace(-1,1,50)
    for i in range (len(opt_list)):
        model,history = run_sequentialNN(data,Nlayers=Nl,Nneurons=Nn,activation ='relu',epochs=35,optimizer = opt_list[i])
        y=model.predict(x)
        score = model.evaluate(data['x_valid'], data['y_valid'], batch_size=32, verbose=1)
        scores.append(score[0])
        hist.append(history.history['loss'])
        pred.append(y)
        labels.append(opt_list[i])

    return hist,pred,labels,scores