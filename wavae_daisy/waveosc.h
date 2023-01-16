#pragma once
#include <math.h>

#define WAVE_LEN 256

struct Wave
{
    static const size_t wave_size = WAVE_LEN;
    float samples[wave_size + 1]{0};

    float GetSample(float id)
    {
        return Interpolate(id);
    }

  private:
    float Interpolate(float frame)
    {
        auto intPart = static_cast<size_t>(frame);
        float fracPart = frame - static_cast<float>(intPart);
        float samp0 = samples[intPart];
        float samp1 = samples[intPart + 1];
        return samp0 + (samp1 - samp0) * fracPart;
    }
};

class WaveOsc
{
  public:
    void Init(float sr, Wave *wave)
    {
        playWave = wave;
        sample_rate = sr;
        sr_resiprocal = 1 / sample_rate;
        SetWave(wave);
        SetFreq(440);
        SetAmp(0.7f);
    }

    /**
     * @brief  Set the data interpolation rate based on a looping frequency.
     *
     * This function determines the interpolation rate based on the file
     * size and the current Stk::sampleRate.  The \e frequency value
     * corresponds to file cycles per second.  The frequency can be
     * negative, in which case the loop is read in reverse order.
     *
     * @param frequency Osc frequency in Hz.
     */
    void SetFreq(float frequency)
    {
        auto norm_freq = frequency * sr_resiprocal;
        phaseInc = wave_size * norm_freq;
    }

    void SetAmp(const float a)
    {
        amp = a;
    }

    void SetWave(Wave *wave)
    {
        nextWave = wave;
        wave_size = wave->wave_size;
    }

    /**
     * @brief Compute a sample frame and return the value.
     */
    float Process()
    {
        if (curPhase >= wave_size)
        {
            curPhase -= wave_size;
            playWave = nextWave;
        }

        float out = playWave->GetSample(curPhase);

        curPhase += phaseInc;
        return out * amp;
    }

  private:
    Wave *playWave;
    Wave *nextWave;
    size_t wave_size = 1;

    float sample_rate;
    float sr_resiprocal;
    float curPhase = 0.f;
    float phaseInc;
    float amp = 1;
};
