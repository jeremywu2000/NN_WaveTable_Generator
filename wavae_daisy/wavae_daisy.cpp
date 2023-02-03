#define _USE_MATH_DEFINES

#include "daisy_patch_sm.h"
#include "waveosc.h"

using namespace daisy;
using namespace patch_sm;

DaisyPatchSM hw;
WaveOsc osc;
Wave DSY_SDRAM_BSS sine;
Wave DSY_SDRAM_BSS tri;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    hw.ProcessAllControls();

    // Exponential smoothing on frequency reading
    // float freq;

    for (size_t i = 0; i < size; i++)
    {
        float sig = osc.Process();
        OUT_L[i] = sig;
        OUT_R[i] = sig;
    }
}

int main(void)
{
    hw.Init();
    bool flag = 0;
    auto step = static_cast<float>(2 * M_PI / WAVE_LEN);
    for (size_t i = 0; i < WAVE_LEN; i++)
    {
        sine.samples[i] = sinf(i * step);
    }

    for (size_t i = 0; i < WAVE_LEN; i++)
    {
        // tri.samples[i] = i * ((float)2.0 / (float)WAVE_LEN) + -1;
        tri.samples[i] = 0.5 * sinf(i * step);
    }

    // step = 2.f / WAVE_LEN;
    // for(auto idx = 0; idx < WAVE_LEN; idx++)
    // {
    //     auto t          = idx * step - 1;
    //     freqWaveIm[idx] = 2 * (fabsf(t) - 0.5f);
    //     freqWaveRe[idx] = 0.0f;
    // }

    osc.Init(hw.AudioSampleRate(), &sine);
    hw.StartAudio(AudioCallback);
    while (1)
    {
        System::Delay(5000);
        if (!flag)
        {
            osc.SetWave(&tri);
        }
        else
        {
            osc.SetWave(&sine);
        }
        flag = !flag;
    }
}
