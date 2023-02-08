#include "daisy_patch_sm.h"
#include "network.h"

using namespace daisy;
using namespace patch_sm;

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
    hw.Init();
    hw.StartLog(true);
    hw.PrintLine("Daisy Patch SM started. Test Beginning");

    __HAL_RCC_CRC_CLK_ENABLE();

    int err = 0;
    float y_val;

    // Create instance of neural network
    err = aiInit();
    if (err != 0)
    {
        hw.PrintLine("Error: %d could not create and initialize NN", err);
        while (1)
            ;
    }

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
        if (aiRun(in_data, out_data) != 0)
        {
            hw.PrintLine("Error: could not run inference");
        }

        // Read output (predicted y) of neural network
        y_val = ((float *)out_data)[0];
        hw.PrintLine(FLT_FMT3, FLT_VAR3(y_val));
    }
}
