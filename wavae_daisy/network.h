#include <stdio.h>

#include "sine_model.h"
#include "sine_model_data.h"

// Pointer to our model
static ai_handle sine_model = AI_HANDLE_NULL;

// Chunk of memory used to hold intermediate values for neural network
AI_ALIGNED(4)
static ai_u8 activations[AI_SINE_MODEL_DATA_ACTIVATIONS_SIZE];

// Buffers used to store input and output tensors
AI_ALIGNED(4)
static ai_i8 in_data[AI_SINE_MODEL_IN_1_SIZE_BYTES];
AI_ALIGNED(4)
static ai_i8 out_data[AI_SINE_MODEL_OUT_1_SIZE_BYTES];

// Initialize wrapper structs that hold pointers to data and info about the
// data (tensor height, width, channels)
static ai_buffer *ai_input;
static ai_buffer *ai_output;

// Network initialization function (Bootstarp)
int aiInit(void);

// Run inference
int aiRun(const void *in_data, void *out_data);
