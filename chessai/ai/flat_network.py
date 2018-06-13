from keras.layers import Input, Dense
from keras.engine.training import Model
from ternary_layers import TernaryDense
from keras.layers.core import Dropout, Lambda
from xnor_layers import XnorDense
from keras import backend
from binary_ops import binary_tanh

def create_net():
    inp = Input(shape=(1344,))
    outp = inp
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False, activation=binary_tanh)(outp)
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False, activation=binary_tanh)(outp)
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False, activation=binary_tanh)(outp)
    outp = Lambda(lambda x: backend.sum(x, axis=-1, keepdims=True))(outp)
    
    return Model(inputs=inp, outputs=outp)
