#include "daisy_patch_sm.h"
#include "daisysp.h"
#include "waveosc.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM hw;
MidiUsbHandler midi;
WaveOsc osc;

Wave DSY_SDRAM_BSS sine;
Wave DSY_SDRAM_BSS saw;
constexpr float TWO_PI_RECIP = 1.0f / TWOPI_F;

uint8_t noteOn;
Adsr adsr;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	hw.ProcessAllControls();

	for (size_t i = 0; i < size; i++)
	{
		OUT_L[i] = OUT_R[i] = osc.Process() * adsr.Process(noteOn != -1);
	}
}

int main(void)
{
	hw.Init();

	/** Initialize USB Midi */
	MidiUsbHandler::Config midi_cfg;
	midi_cfg.transport_config.periph = MidiUsbTransport::Config::INTERNAL;
	midi.Init(midi_cfg);

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

	/** Configure audio handler */
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	/** Initialize our tone */
	osc.Init(hw.AudioSampleRate(), &saw);
	noteOn = -1;
	adsr.Init(hw.AudioSampleRate());

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
