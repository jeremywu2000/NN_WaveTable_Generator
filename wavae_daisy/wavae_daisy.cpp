#include "daisy_patch_sm.h"
#include "daisysp.h"
#include "waveosc.h"
#include "network.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM hw;
MidiUsbHandler midi;
WaveOsc osc;
Adsr adsr;

uint8_t noteOn;
Wave DSY_SDRAM_BSS wave_buf_one;
Wave DSY_SDRAM_BSS wave_buf_two;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		OUT_L[i] = OUT_R[i] = osc.Process() * adsr.Process(noteOn != -1);
	}
}

int main(void)
{
	hw.Init();
	__HAL_RCC_CRC_CLK_ENABLE(); // Enable STM32 CRC IP to use the network-runtime library

	hw.StartLog(true);
	hw.PrintLine("Daisy Patch SM started. Test Beginning");

	/** Initialize USB Midi */
	MidiUsbHandler::Config midi_cfg;
	midi_cfg.transport_config.periph = MidiUsbTransport::Config::INTERNAL;
	midi.Init(midi_cfg);

	int err = 0;

	/** Create network instance */
	err = aiInit();
	if (err != 0)
	{
		hw.PrintLine("Error: %d could not create and initialize NN", err);
		while (1)
			;
	}

	/** Configure audio peripherals */
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	noteOn = -1;
	adsr.Init(hw.AudioSampleRate());
	// Initial inference for starting wave
	if (aiRun(in_data, out_data) != 0)
	{
		hw.PrintLine("Error: could not run inference");
	}
	osc.Init(hw.AudioSampleRate(), &wave_buf_one);

	hw.StartAudio(AudioCallback);
	while (1)
	{
		/** Listen to MIDI for new changes */
		midi.Listen();

		/** When there are messages waiting in the queue... */
		while (midi.HasEvents())
		{
			/** Pull the oldest one from the list... */
			auto msg = midi.PopEvent();
			switch (msg.type)
			{
			case NoteOn:
			{
				/** and change the frequency of the oscillator */
				auto note_msg = msg.AsNoteOn();
				if (note_msg.velocity != 0)
				{
					noteOn = note_msg.note;
					osc.SetFreq(daisysp::mtof(noteOn));
					hw.SetLed(true);
				}
				else
				{
					if (noteOn == note_msg.note)
					{
						noteOn = -1;
						hw.SetLed(false);
					}
				}
			}
			break;
			case NoteOff:
			{
				auto note_msg = msg.AsNoteOff();
				if (noteOn == note_msg.note)
				{
					noteOn = -1;
					hw.SetLed(false);
				}
			}
			break;
			default:
				break;
			}
		}
	}
}
