#include <stdio.h>

#include "vae.h"
#include "vae_data.h"

// Pointer to our model
static ai_handle vae = AI_HANDLE_NULL;

/* Global array to handle the activations buffer */
AI_ALIGNED(32)
static ai_u8 activations[AI_VAE_DATA_ACTIVATIONS_SIZE];

// Buffer used to store input tensors
AI_ALIGNED(32)
static ai_float in_data[AI_VAE_IN_1_SIZE]{0};

// Buffer used to store output tensors
// AI_ALIGNED(32)
// static ai_float out_data[AI_VAE_OUT_1_SIZE];

/* Array of pointer to manage the model's input/output tensors */
static ai_buffer *ai_input;
static ai_buffer *ai_output;

// Network initialization function (Bootstarp)
int aiInit(void);

// Run inference
int aiRun(const void *in_data, void *out_data);
