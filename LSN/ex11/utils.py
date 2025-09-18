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

def create_dataset(function,parameters,sigma,x_train =None,x_valid=None,npoints =None) :
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

def run_sequentialNN (data,Nlayers, Nneurons, activation = None, epochs =70,optimizer = 'adam',loss = 'mse') :
    
    model = Sequential()
    model.add(Input(shape=(1,)))
    if (Nlayers >1) :
        for j in range (Nlayers-1):
            model.add(Dense(Nneurons,activation = activation))
    model.add(Dense(1))
    model.compile(optimizer=optimizer, loss=loss, metrics=[loss])
    history = model.fit(x=data['x_train'], y=data['y_train'], 
          batch_size=32, epochs=epochs,
          shuffle=True, # a good idea is to shuffle input before at each epoch
          validation_data=(data['x_valid'], data['y_valid']))

    return model,history