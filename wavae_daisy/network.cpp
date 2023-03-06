#include "network.h"

int aiInit(void)
{
    ai_error err;

    /* Create and initialize the neural network */
    const ai_handle acts[] = {activations};
    err = ai_vae_create_and_init(&vae, acts, NULL);
    if (err.type != AI_ERROR_NONE)
    {
        return err.code;
    };

    /* Reteive pointers to the model's input/output tensors */
    ai_input = ai_vae_inputs_get(vae, NULL);
    ai_output = ai_vae_outputs_get(vae, NULL);

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
    n_batch = ai_vae_run(vae, &ai_input[0], &ai_output[0]);
    if (n_batch != 1)
    {
        err = ai_vae_get_error(vae);
        return err.type;
    };

    return 0;
}