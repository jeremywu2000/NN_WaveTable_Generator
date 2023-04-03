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

AI_ALIGNED(32)
const ai_float in_ref[AI_VAE_IN_1_SIZE] = {
    0.351148f, 0.9831969f, 0.7927125f, -0.31251898f, -0.9668902f, -0.8044036f, 0.12415902f, 0.38402104f,
    -0.36125502f, 0.12305812f, 0.34741426f, -0.02636559f, -0.39627057f, -0.72743654f, -0.6125344f, 0.09021038f};

AI_ALIGNED(32)
const ai_float in_scale[AI_VAE_IN_1_SIZE] = {
    -0.00704634f, -0.0118047f, -0.01863964f, -0.01700873f, -0.01041651f, -0.00995503f, -0.00525968f, -0.00724763f,
    0.00641576f, 0.00284305f, 0.01115839f, 0.01914814f, 0.02127206f, 0.02093011f, 0.00901887f, 0.00314193f};

inline float midiMap(uint8_t value, float min, float max)
{
    float offset = value * U82F_SCALE;
    return min + (max - min) * offset;
}