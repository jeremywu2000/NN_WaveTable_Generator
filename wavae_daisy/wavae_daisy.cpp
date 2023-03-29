#include "daisy_patch_sm.h"
#include "daisysp.h"
#include "waveosc.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM hw;
WaveOsc osc;
Wave DSY_SDRAM_BSS sine;
Wave DSY_SDRAM_BSS saw;

constexpr float TWO_PI_RECIP = 1.0f / TWOPI_F;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	hw.ProcessAllControls();

	float coarse_knob = hw.GetAdcValue(CV_1);
	float coarse = fmap(coarse_knob, 36.f, 96.f);

	float voct_cv = hw.GetAdcValue(CV_5);
	float voct = fmap(voct_cv, 0.f, 60.f);

	float midi_nn = fclamp(coarse + voct, 0.f, 127.f);
	float freq = mtof(midi_nn);

	osc.SetFreq(freq);

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

	float phase = TWOPI_F / (float)WAVE_LEN;
	for (size_t i = 0; i < WAVE_LEN; i++)
	{
		sine.samples[i] = sinf(i * phase);
	}

	float t = WAVE_LEN / 2;
	float step = 1 / t;
	for (size_t i = 0; i < WAVE_LEN; i++)
	{
		if (i <= t)
			saw.samples[i] = i * step;
		else
			saw.samples[i] = (i - t) * step - 1;
	}

	osc.Init(hw.AudioSampleRate(), &saw);
	hw.StartAudio(AudioCallback);
	while (1)
	{
	}
}
