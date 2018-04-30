from chessai.neural_model import create_conv_model,\
    create_prediction_model, create_supervised_training_model
from chessai import fics_feature_extraction
import keras.backend
from keras.utils.io_utils import HDF5Matrix
import matplotlib.pyplot as plt
from chessai.locations import model_dir
import os
from keras.models import load_model
from keras.callbacks import ModelCheckpoint, EarlyStopping
import dill

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
training_model_filename = os.path.join(model_dir, 'training_model.keras')
prediction_model_filename = os.path.join(model_dir, 'prediction_model.keras')
conv_model_filename = os.path.join(model_dir, 'conv_model.keras')
history_filename = os.path.join(model_dir, 'fit_history.pkl')
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
import keras.losses
keras.losses.loss = loss
if __name__ == '__main__':
    if os.path.exists(conv_model_filename):
        print("Loading existing conv_model")
        conv_model = load_model(conv_model_filename)
    else:
        print("Creating new conv_model")
        conv_model = create_conv_model()
    if os.path.exists(prediction_model_filename):
        print("Loading existing prediction model")
        prediction_model = load_model(prediction_model_filename)
    else:
        print("Creating new prediction model")
        prediction_model = create_prediction_model(conv_model)
    if os.path.exists(training_model_filename):
        print("Loading existing training model")
        training_model = load_model(training_model_filename)
    else:
        print("Creating new training model")
        training_model = create_supervised_training_model(prediction_model)
    if os.path.exists(history_filename):
        with open(history_filename, 'r') as history_file:
            i, j, losses = dill.load(history_file)
    else:
        i = 0
        j = 0
        losses = []
    
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
    n_samples = HDF5Matrix(training_data_filename, 'white').shape[0]
    print 'There are %d rows of data total.' % n_samples
    while True:
        print('Beginning epoch %d' % j)
        lower = 1000000 + i * 1000000
        upper = 1000000 + (i + 1) * 1000000
        print('Fitting on rows %d to %d' % (lower, upper))
        training_args = dict(start=lower, end=upper)
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
        
        history = training_model.fit(training_data_x,
                                     training_data_y,
                                     epochs=1,
                                     batch_size=32768,
                                     shuffle='batch',
                              )
        print('Fitting completed for epoch %d.  Saving progress...' % j)
        
        training_model.save(training_model_filename)
        prediction_model.save(prediction_model_filename)
        conv_model.save(conv_model_filename)
        print('Computing loss on validation set.')
        loss_ = training_model.evaluate(
                                        validation_data_x, 
                                        validation_data_y, 
                                        batch_size=32768
                                        )
        losses.append(loss_)
        print('Validation loss: %f' % loss_)
        with open(history_filename, 'w') as history_file:
            dill.dump((i, j, losses), history_file)
        print('Completed epoch %d' % j)
        
        i += 1
        j += 1
        if 1000000 + (i + 1) * 1000000 > n_samples:
            i = 0
    

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
    

