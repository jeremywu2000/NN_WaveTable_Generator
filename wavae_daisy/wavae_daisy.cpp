#include "daisy_patch_sm.h"

using namespace daisy;
using namespace patch_sm;

DaisyPatchSM hw;
MidiUsbHandler midi;

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

	/** Initialize USB Midi */
	MidiUsbHandler::Config midi_cfg;
	midi_cfg.transport_config.periph = MidiUsbTransport::Config::INTERNAL;
	midi.Init(midi_cfg);

	/** Configure audio handler */
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
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
					hw.SetLed(true);
				else
					hw.SetLed(false);
			}
			break;
			default:
				hw.SetLed(false);
			}
		}
	}
}
