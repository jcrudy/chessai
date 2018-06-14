from keras.layers import Input, Dense
from keras.engine.training import Model
from ternary_layers import TernaryDense
from keras.layers.core import Dropout, Lambda
from xnor_layers import XnorDense
from binary_ops import binary_tanh
from keras import backend as K

def ktotal(x):
    return K.sum(x, axis=-1, keepdims=True)

def create_net():
    inp = Input(shape=(1344,))
    outp = inp
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False, activation=binary_tanh)(outp)
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False, activation=binary_tanh)(outp)
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False, activation=binary_tanh)(outp)
    outp = Lambda(ktotal)(outp)
    
    return Model(inputs=inp, outputs=outp)
