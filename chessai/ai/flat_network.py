from keras.layers import Input, Dense
from keras.engine.training import Model
from ternary_layers import TernaryDense
from keras.layers.core import Dropout
from xnor_layers import XnorDense

def create_net():
    inp = Input(shape=(1344,))
    outp = inp
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False)(outp)
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False)(outp)
    outp = Dropout(.2)(outp)
    outp = XnorDense(2048, use_bias=False)(outp)
    outp = Dense(1, activation='linear')(outp)
    
    return Model(inputs=inp, outputs=outp)






