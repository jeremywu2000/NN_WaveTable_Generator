#include <stdio.h>

#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "sine_model.h"
#include "sine_model_data.h"

#include "daisy_patch_sm.h"
#include "daisysp.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM hw;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    hw.ProcessAllControls();
    for (size_t i = 0; i < size; i++)
    {
        OUT_L[i] = IN_L[i];
        OUT_R[i] = IN_R[i];
    }
}

int main(void)
{
    char buf[50];
    int buf_len = 0;
    ai_error ai_err;
    ai_i32 nbatch;
    uint32_t timestamp;
    float y_val;

    // Chunk of memory used to hold intermediate values for neural network
    AI_ALIGNED(4) ai_u8 activations[AI_SINE_MODEL_DATA_ACTIVATIONS_SIZE];

    // Buffers used to store input and output tensors
    AI_ALIGNED(4) ai_i8 in_data[AI_SINE_MODEL_IN_1_SIZE_BYTES];
    AI_ALIGNED(4) ai_i8 out_data[AI_SINE_MODEL_OUT_1_SIZE_BYTES];

    // Pointer to our model
    ai_handle sine_model = AI_HANDLE_NULL;

    // Initialize wrapper structs that hold pointers to data and info about the
    // data (tensor height, width, channels)
    ai_buffer *ai_input = AI_SINE_MODEL_IN;   //[AI_SINE_MODEL_IN_NUM]
    ai_buffer *ai_output = AI_SINE_MODEL_OUT; //[AI_SINE_MODEL_OUT_NUM]

    // Set working memory and get weights/biases from model
    ai_network_params ai_params = {AI_SINE_MODEL_DATA_WEIGHTS(ai_sine_model_data_weights_get()),
                                   AI_SINE_MODEL_DATA_ACTIVATIONS(activations)};

    // Set pointers wrapper structs to our data buffers
    ai_input[0].data = AI_HANDLE_PTR(in_data);
    ai_output[0].data = AI_HANDLE_PTR(out_data);

    // Create instance of neural network
    ai_err = ai_sine_model_create(&sine_model, AI_SINE_MODEL_DATA_CONFIG);
    if (ai_err.type != AI_ERROR_NONE)
    {
        buf_len = sprintf(buf, "Error: could not create NN instance\r\n");
        // HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
        while (1)
            ;
    }

    // Initialize neural network
    if (!ai_sine_model_init(sine_model, &ai_params))
    {
        buf_len = sprintf(buf, "Error: could not initialize NN\r\n");
        // HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
        while (1)
            ;
    }

    hw.Init();
    hw.SetAudioBlockSize(4); // number of samples handled per callback
    hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
    hw.StartAudio(AudioCallback);
    while (1)
    {
        // Fill input buffer (use test value)
        for (uint32_t i = 0; i < AI_SINE_MODEL_IN_1_SIZE; i++)
        {
            ((ai_float *)in_data)[i] = (ai_float)2.0f;
        }

        // Perform inference
        nbatch = ai_sine_model_run(sine_model, &ai_input[0], &ai_output[0]);
        if (nbatch != 1)
        {
            buf_len = sprintf(buf, "Error: could not run inference\r\n");
            // HAL_UART_Transmit(&huart2, (uint8_t *)buf, buf_len, 100);
        }

        // Read output (predicted y) of neural network
        y_val = ((float *)out_data)[0];
    }
}
