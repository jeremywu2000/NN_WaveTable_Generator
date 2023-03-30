#include "vaeosc.h"

float Wave::Interpolate(float x_offset, float ym1, float y0, float y1, float y2)
{
    // Hermite interpolation
    float c = (y1 - ym1) * 0.5f;
    float v = y0 - y1;
    float w = c + v;
    float a = w + v + (y2 - y0) * 0.5f;
    float b_neg = w + a;

    return ((((a * x_offset) - b_neg) * x_offset + c) * x_offset + y0);
}

float WaveOsc::Process()
{
    float out = waveform_->GetSample(phase_);

    phase_ += phase_inc_;
    if (phase_ >= wave_size_)
    {
        phase_ -= wave_size_;
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