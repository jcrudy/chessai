from keras.layers import Input, Conv2D, Dense, concatenate, Flatten, Activation
from keras.engine.training import Model
from toolz.curried import keymap, valmap
from toolz.dicttoolz import merge
from keras.layers.convolutional import Conv2DTranspose
from keras.layers.merge import subtract

def create_conv_model():
    pieces = Input(shape=(20,8,8))
    conv1 = Conv2D(100, 2, activation='relu', data_format='channels_first')(pieces)
    conv2 = Conv2D(100, 2, activation='relu', data_format='channels_first')(conv1)
    return Model(inputs=pieces, outputs=[conv1, conv2])

def create_auto_encoder(conv_model):
    return Model(inputs=conv_model.inputs, outputs=Conv2DTranspose(100, 2, activation='relu', data_format='channels_first')(Conv2DTranspose(100, 2, activation='relu', data_format='channels_first')(conv_model.outputs[1])))

def create_prediction_model(conv_model):
    turn = Input(shape=(1,))
    castle_rights = Input(shape=(4,))
    return Model(inputs = conv_model.inputs + [castle_rights, turn],
                 outputs = Dense(1, activation='linear')((Dense(1000, activation='relu')(Dense(1000, activation='relu')(concatenate([Flatten()(conv_model.outputs[0]), 
                                                                                             Flatten()(conv_model.outputs[1]), 
                                                                                             Flatten()(conv_model.inputs),
                                                                                             castle_rights,
                                                                                             turn])))))
                 )

def create_supervised_training_model(prediction_model):
    pieces = Input(shape=(20,8,8))
    pieces_selected = Input(shape=(20,8,8))
    turn = Input(shape=(1,))
    turn_selected = Input(shape=(1,))
    castle_rights = Input(shape=(4,))
    castle_rights_selected = Input(shape=(4,))
    
    output = prediction_model([pieces, castle_rights, turn])
    selected_output = prediction_model([pieces_selected, castle_rights_selected, turn_selected])
    
    return Model(inputs=[pieces, castle_rights, turn, pieces_selected, castle_rights_selected, turn_selected],
                 outputs=[subtract([output, selected_output])])

if __name__ == '__main__':
    print create_conv_model()
    print create_auto_encoder(create_conv_model())
    print create_prediction_model(create_conv_model())
    print create_supervised_training_model(create_prediction_model(create_conv_model()))
