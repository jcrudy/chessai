from chessai.locations import model_dir
import os
from keras.models import load_model
from keras.utils.vis_utils import plot_model
from matplotlib import pyplot
from chessai import train_supervised_model
from keras.engine.training import Model
from chessai.train_supervised_model import training_data_filename
from keras.utils.io_utils import HDF5Matrix
from keras.engine.topology import Input
from keras.layers.merge import multiply
import pickle
import numpy as np
from matplotlib.pyplot import plot, xlabel, ylabel, show
from chessai.neural_model import prediction_model_from_training_model,\
    validation_model_from_training_model

# Load the network
current_dir = os.path.join(model_dir, '2018_04_30')
training_model_filename = os.path.join(current_dir, 'training_model.keras')
training_model_plot_filename = os.path.join(current_dir, 'training_model_plot.png')
history_filename = os.path.join(current_dir, 'fit_history.pkl')
training_model = load_model(training_model_filename)

with open(history_filename, 'r') as infile:
    history = pickle.load(infile)

y = np.array(history[1])
x = np.arange(y.shape[0])
plot(x, y)
xlabel('Epoch')
ylabel('Validation Loss')
show()
print(y[-1])

plot_model(training_model, to_file=training_model_plot_filename)

prediction_model = prediction_model_from_training_model(training_model)

# Compute accuracy on first 10000 rows
data_filename = training_data_filename
validation_args = dict(start=0, end=100000)
option_data_x = [
                   HDF5Matrix(training_data_filename, 'pieces', **validation_args),
                   HDF5Matrix(training_data_filename, 'castle_rights', **validation_args),
                   HDF5Matrix(training_data_filename, 'turn', **validation_args),
                   
                   ]
selected_data_x = [
                 HDF5Matrix(training_data_filename, 'pieces_selected', **validation_args),
                 HDF5Matrix(training_data_filename, 'castle_rights_selected', **validation_args),
                 HDF5Matrix(training_data_filename, 'turn_selected', **validation_args),
                 ]
white = [
                     HDF5Matrix(training_data_filename, 'white', **validation_args),
                     ]
validation_model = validation_model_from_training_model(training_model)
option = validation_model.predict(option_data_x + white)
selected = validation_model.predict(selected_data_x + white)
accuracy = sum(selected > option) / float(len(option))
print(accuracy)



