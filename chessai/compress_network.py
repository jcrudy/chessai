from chessai.locations import model_dir
import os
from keras.models import load_model
from chessai.neural_model import prediction_model_from_training_model
from keras_compressor.compressor import compress
from tensorflow.contrib.keras.python.keras.utils.layer_utils import count_total_params


current_dir = os.path.join(model_dir, '2018_05_01')
training_model_filename = os.path.join(current_dir, 'training_model.keras')
training_model_plot_filename = os.path.join(current_dir, 'training_model_plot.png')
history_filename = os.path.join(current_dir, 'fit_history.pkl')

training_model = load_model(training_model_filename)
prediction_model = prediction_model_from_training_model(training_model)

total_params_before = sum(count_total_params(prediction_model))
print(total_params_before)
compressed_prediction_model = compress(model=prediction_model, acceptable_error=.01)
total_params_after = sum(count_total_params(prediction_model))
print(total_params_after)
