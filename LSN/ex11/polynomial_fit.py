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

def order3_polynomial(pars,x): return pars[0]*
