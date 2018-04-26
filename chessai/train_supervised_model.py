from chessai.neural_model import create_conv_model,\
    create_prediction_model, create_supervised_training_model
from chessai import fics_feature_extraction
import keras.backend
from keras.utils.io_utils import HDF5Matrix
import matplotlib.pyplot as plt
from chessai.locations import model_dir
import os

def plot_history(history):
    loss_list = [s for s in history.history.keys() if 'loss' in s and 'val' not in s]
    val_loss_list = [s for s in history.history.keys() if 'loss' in s and 'val' in s]
    acc_list = [s for s in history.history.keys() if 'acc' in s and 'val' not in s]
    val_acc_list = [s for s in history.history.keys() if 'acc' in s and 'val' in s]
    
    if len(loss_list) == 0:
        print('Loss is missing in history')
        return 
    
    ## As loss always exists
    epochs = range(1,len(history.history[loss_list[0]]) + 1)
    
    ## Loss
    plt.figure(1)
    for l in loss_list:
        plt.plot(epochs, history.history[l], 'b', label='Training loss (' + str(str(format(history.history[l][-1],'.5f'))+')'))
    for l in val_loss_list:
        plt.plot(epochs, history.history[l], 'g', label='Validation loss (' + str(str(format(history.history[l][-1],'.5f'))+')'))
    
    plt.title('Loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()
    
    ## Accuracy
    plt.figure(2)
    for l in acc_list:
        plt.plot(epochs, history.history[l], 'b', label='Training accuracy (' + str(format(history.history[l][-1],'.5f'))+')')
    for l in val_acc_list:    
        plt.plot(epochs, history.history[l], 'g', label='Validation accuracy (' + str(format(history.history[l][-1],'.5f'))+')')

    plt.title('Accuracy')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.show()

conv_model = create_conv_model()
prediction_model = create_prediction_model(conv_model)
training_model = create_supervised_training_model(prediction_model)

training_data_filename = fics_feature_extraction.outfilename
number = 1
training_model_filename = os.path.join(model_dir, 'training_model_%d.keras' % number)
prediction_model_filename = os.path.join(model_dir, 'prediction_model_%d.keras' % number)
conv_model_filename = os.path.join(model_dir, 'conv_model_%d.keras' % number)

def loss(y_true, y_pred):
    # The network predicts the value function from white's perspective
    # at all times.
    # If the move was chosen by white, the boards were 
    # on black's turn (y_true == -1).  In that case the selected output should
    # be more positive than the output
    # If the move was chosen by black, on the other hand, y_true == 1 and we want
    # selected output to be more negative.
#     output = y_pred[0]
#     selected_output = y_pred[1]
    return keras.backend.sum(keras.backend.sigmoid(y_true * y_pred))

if __name__ == '__main__':
#     args = dict()
#     pieces = HDF5Matrix(training_data_filename, 'pieces', **args)
#     castle_rights = HDF5Matrix(training_data_filename, 'castle_rights', **args)
#     turn = HDF5Matrix(training_data_filename, 'turn', **args)
#     pieces_selected = HDF5Matrix(training_data_filename, 'pieces_selected', **args)
#     castle_rights_selected = HDF5Matrix(training_data_filename, 'castle_rights_selected', **args)
#     turn_selected = HDF5Matrix(training_data_filename, 'turn_selected', **args)
#     white = HDF5Matrix(training_data_filename, 'white', **args)
    from tensorflow.python.client import device_lib
    print(device_lib.list_local_devices())
    import tensorflow as tf
    sess = tf.Session(config=tf.ConfigProto(log_device_placement=True))
    training_args = dict(start=1000000, end=20000000)
    training_data_x = [
                     HDF5Matrix(training_data_filename, 'pieces', **training_args),
                     HDF5Matrix(training_data_filename, 'castle_rights', **training_args),
                     HDF5Matrix(training_data_filename, 'turn', **training_args),
                     HDF5Matrix(training_data_filename, 'pieces_selected', **training_args),
                     HDF5Matrix(training_data_filename, 'castle_rights_selected', **training_args),
                     HDF5Matrix(training_data_filename, 'turn_selected', **training_args),
                     ]
    training_data_y = [
                       HDF5Matrix(training_data_filename, 'white', **training_args),
                       ]
    validation_args = dict(start=0, end=1000000)
    validation_data_x = [
                       HDF5Matrix(training_data_filename, 'pieces', **validation_args),
                       HDF5Matrix(training_data_filename, 'castle_rights', **validation_args),
                       HDF5Matrix(training_data_filename, 'turn', **validation_args),
                       HDF5Matrix(training_data_filename, 'pieces_selected', **validation_args),
                       HDF5Matrix(training_data_filename, 'castle_rights_selected', **validation_args),
                       HDF5Matrix(training_data_filename, 'turn_selected', **validation_args),
                       ]
    validation_data_y = [
                         HDF5Matrix(training_data_filename, 'white', **validation_args),
                         ]
    
    training_model.compile(optimizer='adadelta', loss=loss)
    history = training_model.fit(training_data_x,
                                 training_data_y,
                                 epochs=10,
                                 batch_size=32768,
                                 shuffle='batch',
                                 validation_data=(validation_data_x, validation_data_y)
                          )
    training_model.save(training_model_filename)
    prediction_model.save(prediction_model_filename)
    conv_model.save(conv_model_filename)
    plot_history(history)
    

# for i in range(100):
#     for j in range(100):
#         # Generate position by i random half moves
#         board = BitBoardState.from_fen('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1')
#         for _ in range(i):
#             moves = board.all_moves()
#             if not moves:
#                 break
#             move = random.choice(moves)
#             board.make_move(move)
#     
#     # Extract features from board
#     features = board.extract_features()['pieces']
#     
    

