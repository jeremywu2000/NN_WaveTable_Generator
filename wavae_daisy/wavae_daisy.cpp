#include "daisy_patch_sm.h"
#include "network.h"

using namespace daisy;
using namespace patch_sm;

DaisyPatchSM hw;
static uint32_t start, end, dur;

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

	// Enable STM32 CRC IP to use the network-runtime library
	__HAL_RCC_CRC_CLK_ENABLE();

	int err = 0;

	// Create instance of neural network
	err = aiInit();
	if (err != 0)
	{
		hw.PrintLine("Error: %d could not create and initialize NN", err);
		while (1)
			;
	}

	ai_float *in_ptr = (ai_float *)in_data;

	in_ptr[0] = -0.03772060200572014;
	in_ptr[1] = -0.00241672620177269;
	in_ptr[2] = 0.015059288591146469;
	in_ptr[3] = 0.04252573847770691;
	in_ptr[4] = 0.07208582758903503;
	in_ptr[5] = 0.08476673066616058;
	in_ptr[6] = 0.11673141270875931;
	in_ptr[7] = 0.15359428524971008;
	in_ptr[8] = 0.19379079341888428;
	in_ptr[9] = 0.22240658104419708;
	in_ptr[10] = 0.30685362219810486;
	in_ptr[11] = 0.43470239639282227;
	in_ptr[12] = 0.9310518503189087;
	in_ptr[13] = 1.0460214614868164;
	in_ptr[14] = -1.8028243780136108;
	in_ptr[15] = 0.706463098526001;

	// Read output (predicted y) of neural network
	// ai_float *out_prt = (ai_float *)out_data;
	// for (uint32_t i = 0; i < AI_VAE_OUT_1_SIZE; i++)
	// {
	// 	hw.PrintLine(FLT_FMT3, FLT_VAR3(out_prt[i]));
	// }

	while (1)
	{
		start = System::GetNow();

		// Perform inference
		if (aiRun(in_data, out_data) != 0)
		{
			hw.PrintLine("Error: could not run inference");
		}

		end = System::GetNow();
		dur = (end - start); // us
		hw.PrintLine("%d", dur);
	}
}
