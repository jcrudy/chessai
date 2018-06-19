from chessai.ai.flat_network import create_net
from chessai.ai.bitboard import XNor, BitBoardState, double_binary_conversion_validation_function, binary_sum_validation_function, binary_tanh_dot_validation_function
import numpy as np
from chessai.ai.xnor_to_cpp import xnor_tanh
from nose.tools import assert_equal
from numpy.ma.testutils import assert_array_almost_equal

def test_binary_conversion():
    board = BitBoardState.from_fen('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1')
    features = board.extract_flat_raw_features()
    model = create_net()
    weights = xnor_tanh(model.layers[2].get_weights()[0])
    assert double_binary_conversion_validation_function(features)
    assert binary_sum_validation_function(features)
    assert_array_almost_equal(xnor_tanh(np.dot(features, weights)), binary_tanh_dot_validation_function(features, weights))

def test_xnor():
    model = create_net()
    xnor = XNor.from_keras(model)
    board = BitBoardState.from_fen('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1')
    features = board.extract_flat_raw_features()
    print ''.join([str(int(i)) for i in np.ravel(((xnor_tanh(np.dot(features, xnor_tanh(model.layers[2].get_weights()[0]))) + 1) / 2))[:64]])
    assert_equal(model.predict(features)[0,0], xnor.evaluate(features))

if __name__ == '__main__':
    # This code will run the test in this file.'
    import sys
    import nose
    module_name = sys.modules[__name__].__file__

    result = nose.run(argv=[sys.argv[0],
                            module_name,
                            '-s', '-v'])
    
