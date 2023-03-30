#include "daisy_patch_sm.h"
#include "daisysp.h"
#include "vaeosc.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM hw;
MidiUsbHandler midi;
Adsr adsr; // Note ADSR envelope
WaveOsc osc;

Wave *updateBuffer;
Wave DSY_SDRAM_BSS wave_buf_one;
Wave DSY_SDRAM_BSS wave_buf_two;
uint8_t noteOn; // Last MIDI note number
bool updateTable;

/** Midi Interface helper functions */
void NoteOnMsg(MidiEvent msg);
void NoteOffMsg(MidiEvent msg);
void CCMsg(MidiEvent msg);

inline float midiMap(uint8_t value, float min, float max)
{
    float offset = value * U82F_SCALE;
    return min + (max - min) * offset;
}