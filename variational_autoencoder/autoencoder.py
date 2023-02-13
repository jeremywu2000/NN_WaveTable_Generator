from tensorflow import keras
from keras.models import Model
from keras.layers import Input, Conv2D, ReLU, BatchNormalization, Flatten, Dense, Reshape, Conv2DTranspose, Activation, Lambda
from keras import backend as K
from keras.optimizers import Adam
from keras.losses import MeanSquaredError
import numpy as np
import os
import pickle
import tensorflow as tf

tf.compat.v1.disable_eager_execution()

def _calculate_reconstruction_loss(y_target, y_predicted):
    error = y_target-y_predicted
    reconstruction_loss = K.mean(K.square(error), axis=[1,2,3])
    return reconstruction_loss

def calculate_kl_loss(model):
    
    def _calculate_kl_loss(*args):
        kl_loss = -0.5 * K.sum(1 + model.log_variance - K.square(model.mu) - K.exp(model.log_variance), axis=1)
        return kl_loss
    return _calculate_kl_loss

class VAE:
    """
    VAE represents a Deep Convolutiuonal variational autoencoder architecture with mirrored encoder and decoder components.
    """

    def __init__(self, input_shape, conv_filters, conv_kernels, conv_strides, latent_space_dim):
        self.input_shape=input_shape # [width, height, channel] [28,28,1]
        self.conv_filters=conv_filters # [2,4,8]
        self.conv_kernels=conv_kernels # [3,5,3]
        self.conv_strides=conv_strides # [1,2,2]
        self.latent_space_dim=latent_space_dim
        self.reconstruction_loss_weight=1000

        self.encoder = None
        self.decoder = None
        self.model = None

        self._num_conv_layers = len(conv_filters)

        self._build() #building encoder decoder model

    def summary(self):
        self.encoder.summary()
        self.decoder.summary()
        self.model.summary()
    
    def compile(self, learning_rate=0.0001):
        optimizer = Adam(learning_rate=learning_rate)
        self.model.compile(optimizer=optimizer, 
                            loss=self._calculate_combined_loss,
                            metrics=[_calculate_reconstruction_loss, calculate_kl_loss(self)])


    
    def train(self, x_train, batch_size, num_epochs):
        # input should be the same as the output in the params,
        # we are trying to reconstruct the output and have it as similar as possible to the input
        self.model.fit(x_train, 
                        x_train,
                        batch_size=batch_size,
                        epochs=num_epochs,
                        shuffle=True)
    def save(self, save_folder="."):
        self._create_folder_if_doesnt_exist(save_folder)
        self._save_parameters(save_folder)
        self._save_weights(save_folder)

    def load_weights(self, weights_path):
        self.model.load_weights(weights_path)
    
    def reconstruct(self, images):
        latent_representations = self.encoder.predict(images)
        reconstructed_images = self.decoder.predict(latent_representations)
        return reconstructed_images, latent_representations

    @classmethod
    def load(cls,save_folder="."):
        parameters_path = os.path.join(save_folder, "parameters.pkl")
        with open(parameters_path, 'rb') as f: #reading mode for binary file
            parameters = pickle.load(f)
        autoencoder = VAE(*parameters) #passing parameters as positional arguments
        weights_path = os.path.join(save_folder, "weights.h5")
        autoencoder.load_weights(weights_path)
        return autoencoder

    def _calculate_combined_loss(self, y_target, y_predicted):
        reconstruction_loss = _calculate_reconstruction_loss(y_target, y_predicted)
        kl_loss= calculate_kl_loss(self)()
        combined_loss = self.reconstruction_loss_weight * reconstruction_loss + kl_loss
        return combined_loss


    def _create_folder_if_doesnt_exist(self, save_folder):
        if not os.path.exists(save_folder):
            os.makedirs(save_folder)
    
    def _save_parameters(self, save_folder):
        parameters = [
            self.input_shape,
            self.conv_filters,
            self.conv_kernels,
            self.conv_strides,
            self.latent_space_dim,
        ]
        save_path = os.path.join(save_folder, "parameters.pkl")
        with open(save_path, "wb") as f: #writing mode for binary file
            pickle.dump(parameters,f)

    def _save_weights(self, save_folder):
        save_path = os.path.join(save_folder, "weights.h5")
        self.model.save_weights(save_path)

    def _build(self):
        self._build_encoder()
        self._build_decoder()
        self._build_autoencoder()
    
    def _build_autoencoder(self):
        model_input = self._model_input
        model_output = self.decoder(self.encoder(model_input))
        self.model = Model(model_input, model_output, name="autoencoder")

    def _build_decoder(self):
        decoder_input = self._add_decoder_input()
        dense_layer = self._add_dense_layer(decoder_input)
        reshape_layer = self._add_reshape_layer(dense_layer)
        conv_transpose_layers = self._add_conv_transpose_layers(reshape_layer)
        decoder_output = self._add_decoder_output(conv_transpose_layers)
        self.decoder = Model(decoder_input,decoder_output, name="decoder") #instantiate a keras model

    def _add_decoder_input(self):
        return Input(shape=self.latent_space_dim, name="decoder_input")

    def _add_dense_layer(self, decoder_input):
        num_neurons = np.prod(self._shape_before_bottleneck)
        dense_layer = Dense(num_neurons, name="decoder_dense")(decoder_input)
        return dense_layer
        
    def _add_reshape_layer(self, dense_layer):
        return Reshape(self._shape_before_bottleneck)(dense_layer)

    def _add_conv_transpose_layers(self, graph_of_layers):
        """Add conv transpose blocks."""
        # Loop through all conv layers in reverse order and stop at first layer
        for layer_index in reversed(range(1, self._num_conv_layers)):
            # [0,1,2] -> [2,1]
            graph_of_layers=self._add_conv_transpose_layer(layer_index, graph_of_layers)
        return graph_of_layers

    def _add_conv_transpose_layer(self, layer_index, graph_of_layers):
        layer_number=self._num_conv_layers - layer_index
        conv_transpose_layer = Conv2DTranspose(
            filters=self.conv_filters[layer_index],
            kernel_size=self.conv_kernels[layer_index],
            strides=self.conv_strides[layer_index],
            padding="same",
            name=f"decoder_conv_transpose_layer_{layer_number}"
        )
        graph_of_layers = conv_transpose_layer(graph_of_layers)
        graph_of_layers = ReLU(name=f"decoder_relu_{layer_number}")(graph_of_layers)
        graph_of_layers = BatchNormalization(name=f"decode_bn_{layer_number}")(graph_of_layers)
        return graph_of_layers
    
    def _add_decoder_output(self, graph_of_layers):
        conv_transpose_layer = Conv2DTranspose(
            filters=1, #[24,24,1] we can interpret spectrograms as grayscale images (1 channel as output)
            kernel_size=self.conv_kernels[0], #getting first convolutional layer in terms of kernels
            strides=self.conv_strides[0], #getting first convolutional layer in terms of strides
            padding="same",
            name=f"decoder_conv_transpose_layer_{self._num_conv_layers}" #=3
        )
        #apply this to incomming graph of layers
        graph_of_layers=conv_transpose_layer(graph_of_layers)
        output_layer= Activation("sigmoid", name="sigmoid_layer")(graph_of_layers) #activation layer where we use sigmoid
        return output_layer

    def _build_encoder(self):
        encoder_input = self._add_encoder_input()
        #building the conv layers
        conv_layers = self._add_conv_layers(encoder_input) #sends back graph of layers
        #build bottleneck, output to encoder
        bottleneck = self._add_bottleneck(conv_layers)
        self._model_input = encoder_input
        self.encoder = Model(encoder_input,bottleneck, name="encoder")


    def _add_encoder_input(self):
        return Input(shape=self.input_shape, name="encoder_input")
    
    def _add_conv_layers(self, encoder_input):
        graph_of_layers=encoder_input
        #go step by step through all layers and add
        for layer_index in range(self._num_conv_layers):
            graph_of_layers=self._add_conv_layer(layer_index, graph_of_layers) #graph_of_layers will be graph of layers, conv blocks
        return graph_of_layers

    def _add_conv_layer(self, layer_index, graph_of_layers):
        #conv 2d + ReLU + batch normalization
        layer_number=layer_index+1
        conv_layer= Conv2D(
            filters=self.conv_filters[layer_index],
            kernel_size=self.conv_kernels[layer_index],
            strides=self.conv_strides[layer_index],
            padding="same",
            name=f"encoder_conv_layer_{layer_number}"
        )
        graph_of_layers=conv_layer(graph_of_layers)
        graph_of_layers = ReLU(name=f"encoder_relu_{layer_number}")(graph_of_layers)
        graph_of_layers= BatchNormalization(name=f"encoder_bn_{layer_number}")(graph_of_layers)
        return graph_of_layers
    
    def _add_bottleneck(self, graph_of_layers):
        """Flatten data and add bottleneck with Gaussian sampling (Dense layer)."""

        self._shape_before_bottleneck= K.int_shape(graph_of_layers)[1:] #[2,7,7,32] batchsize(dont care),height width num of channels

        graph_of_layers= Flatten()(graph_of_layers)
        # graph_of_layers = Dense(self.latent_space_dim, name="encoder_output")(graph_of_layers)
        self.mu = Dense(self.latent_space_dim, name="mu")(graph_of_layers)
        self.log_variance = Dense(self.latent_space_dim, name="log_variance")(graph_of_layers)

        def sample_point_from_normal_distribution(args):
            mu, log_variance = args
            epsilon = K.random_normal(shape=K.shape(self.mu), mean=0.,stddev=1.)
            sampled_point=mu+K.exp(log_variance/2)*epsilon
            return sampled_point

        #sample a data point from this gaussian distribution that is parametrized by this mu and log var
        graph_of_layers = Lambda(sample_point_from_normal_distribution, name="encoder_output")([self.mu,self.log_variance])

        return graph_of_layers

if __name__ == "__main__":
    autoencoder = VAE(
        input_shape=(28,28,1),
        conv_filters=(32,64,64,64),
        conv_kernels=(3,3,3,3),
        conv_strides=(1,2,2,1),
        latent_space_dim=2
    )
    autoencoder.summary()