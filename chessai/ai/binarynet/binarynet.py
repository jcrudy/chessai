import numpy as np

class Layer(object):
    def __init__(self, inlayer, outsize):
        self.inlayer = inlayer
        self.outsize = outsize

class BFCLayer(Layer):
    def __init__(self, inlayer, outsize):
        Layer.__init__(self, inlayer, outsize)
        self.weights = np.random.uniform(-1., 1., size=(inlayer.outsize, outsize))
        
    def forward(self, indata):
        binary_weights = 2 * (self.weights >= 0.) - 1
        activations = np.dot(binary_weights, indata)
        return 2 * (activations >= 0.) - 1
    
    def backward(self, indata, dout):
        pass
        
        
