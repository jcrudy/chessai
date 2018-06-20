from keras.layers import Input, Dense
from keras.engine.training import Model
from keras.layers.core import Dropout, Lambda
from chessai.xnornet.xnor_layers import XnorDense
from chessai.xnornet.binary_ops import binary_tanh
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

# def create_net(dropout_rate=.2):
#     inp = Input(shape=(1344,))
#     outp = inp
#     outp = Dropout(dropout_rate)(outp)
    
    
def add_layer(model, nodes=2048, dropout_rate=.2):
    inp = model.inputs
    outp = model.outputs
    outp = Dropout(dropout_rate)(outp)
    outp = XnorDense(nodes, use_bias=False, activation=binary_tanh)(outp)
    result = Model(inputs=inp, outputs = outp)

def create_nets(hidden_layers=3):
    inp = Input(shape=(1344,))
    outp = inp
    models = []
    for i in range(hidden_layers):
        outp = XnorDense(2048, use_bias=False, activation=binary_tanh)(outp)
        models.append(Model(inputs=inp, outputs=outp))