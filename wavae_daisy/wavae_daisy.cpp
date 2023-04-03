#include "wavae_daisy.h"

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		OUT_L[i] = OUT_R[i] = osc.Process() * adsr.Process(noteOn != (uint8_t)-1);
	}
}

void Init()
{
	/** Harware initialization */
	hw.Init();
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	__HAL_RCC_CRC_CLK_ENABLE(); // Enable STM32 CRC IP to use the network-runtime library

	/** Create network instance */
	if (aiInit() != 0)
	{
		hw.StartLog(true);
		hw.PrintLine("Error: could not create and initialize NN");
		while (1)
			;
	}

	/** Oscillator Initialization */
	if (aiRun(in_ref, wave_buf_one.samples) != 0) // Initial inference for starting wave
	{
		hw.StartLog(true);
		hw.PrintLine("Error: could not run inference");
		while (1)
			;
	}
	updateBuffer = &wave_buf_two;
	osc.Init(hw.AudioSampleRate(), &wave_buf_one);

	/** USB Midi Initialization */
	MidiUsbHandler::Config midi_cfg;
	midi_cfg.transport_config.periph = MidiUsbTransport::Config::INTERNAL;
	midi.Init(midi_cfg);

	noteOn = -1;
	adsr.Init(hw.AudioSampleRate());
}

int main(void)
{
	Init();

	hw.StartAudio(AudioCallback);
	while (1)
	{
		/** Listen to MIDI for new changes */
		midi.Listen();
		while (midi.HasEvents())
		{
			auto msg = midi.PopEvent();
			switch (msg.type)
			{
			case NoteOn:
				NoteOnMsg(msg);
				break;
			case NoteOff:
				NoteOffMsg(msg);
				break;
			case ControlChange:
				CCMsg(msg);
				break;
			default:
				break;
			}
		}

		/** Generate new wave */
		if (updateTable)
		{
			if (aiRun(in_data, updateBuffer->samples) != 0)
			{
				hw.StartLog(true);
				hw.PrintLine("Error: could not run inference");
			}
			updateBuffer = osc.SetWaveform(updateBuffer);
			updateTable = false;
		}
	}
}

void NoteOnMsg(MidiEvent msg)
{
	auto note_msg = msg.AsNoteOn();
	if (note_msg.velocity != 0)
	{
		/** change the frequency of the oscillator */
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

void NoteOffMsg(MidiEvent msg)
{
	auto note_msg = msg.AsNoteOff();
	if (noteOn == note_msg.note)
	{
		noteOn = -1;
		hw.SetLed(false);
	}
}

void CCMsg(MidiEvent msg)
{
	auto cc_msg = msg.AsControlChange();
	if (cc_msg.control_number == 7)
	{
		osc.SetAmp(midiMap(cc_msg.value, 0.001f, 0.7f));
	}
	else if (cc_msg.control_number == 1)
	{
		for (size_t i = 0; i < AI_VAE_IN_1_WIDTH; i++)
		{
			in_data[i] = in_ref[i] + in_scale[i] * cc_msg.value;
		}
		updateTable = true;
	}
	else
	{
		ai_float data = midiMap(cc_msg.value, -1.0f, 1.0f);
		in_data[cc_msg.control_number % AI_VAE_IN_1_WIDTH] = data;
		updateTable = true;
	}
}
