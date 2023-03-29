#include "daisy_patch_sm.h"
#include "daisysp.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM hw;
MidiUsbHandler midi;
Oscillator osc;

uint8_t noteOn;
Adsr adsr;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	hw.ProcessAllControls();
	for (size_t i = 0; i < size; i++)
	{
		OUT_L[i] = OUT_R[i] = osc.Process() * adsr.Process(noteOn != -1) * 0.7;
	}
}

int main(void)
{
	hw.Init();

	/** Initialize USB Midi */
	MidiUsbHandler::Config midi_cfg;
	midi_cfg.transport_config.periph = MidiUsbTransport::Config::INTERNAL;
	midi.Init(midi_cfg);

	/** Configure audio handler */
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_96KHZ);

	/** Initialize our tone */
	noteOn = -1;
	osc.Init(hw.AudioSampleRate());
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
