#include "network.h"

int aiInit(void)
{
    ai_error err;

    /* Create and initialize the neural network */
    const ai_handle acts[] = {activations};
    err = ai_sine_model_create_and_init(&sine_model, acts, NULL);
    if (err.type != AI_ERROR_NONE)
    {
        return err.code;
    };

    /* Reteive pointers to the model's input/output tensors */
    ai_input = ai_sine_model_inputs_get(sine_model, NULL);
    ai_output = ai_sine_model_outputs_get(sine_model, NULL);

    return 0;
}

int aiRun(const void *in_data, void *out_data)
{
    ai_i32 n_batch;
    ai_error err;

    /* 1 - Update IO handlers with the data payload */
    ai_input[0].data = AI_HANDLE_PTR(in_data);
    ai_output[0].data = AI_HANDLE_PTR(out_data);

    /* 2 - Perform the inference */
    n_batch = ai_sine_model_run(sine_model, &ai_input[0], &ai_output[0]);
    if (n_batch != 1)
    {
        err = ai_sine_model_get_error(sine_model);
        return err.type;
    };

    return 0;
}