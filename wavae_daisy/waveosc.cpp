#include "waveosc.h"

float WaveOsc::Process()
{
    float out = waveform_->GetSample(phase_);

    phase_ += phase_inc_;
    if (phase_ >= wave_size_)
    {
        phase_ -= wave_size_;
        waveform_ = nextWave_;
        eoc_ = true;
    }
    else
    {
        eoc_ = false;
    }

    return out * amp_;
}

float WaveOsc::CalcPhaseInc(float f)
{
    return (wave_size_ * f) * sr_recip_;
}