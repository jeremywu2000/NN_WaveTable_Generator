#pragma once

#define WAVE_LEN 256

struct Wave
{
    static const size_t wave_size = WAVE_LEN;
    float samples[wave_size]{0};

    float GetSample(float idx)
    {
        auto x = static_cast<size_t>(idx);
        float x_offset = idx - static_cast<float>(x);

        float ym1 = samples[(x + wave_size - 1) % wave_size];
        float y0 = samples[x];
        float y1 = samples[(x + 1) % wave_size];
        float y2 = samples[(x + 2) % wave_size];

        return Interpolate(x_offset, ym1, y0, y1, y2);
    }

private:
    float Interpolate(float x_offset, float ym1, float y0, float y1, float y2)
    {
        // Hermite interpolation
        float c = (y1 - ym1) * 0.5f;
        float v = y0 - y1;
        float w = c + v;
        float a = w + v + (y2 - y0) * 0.5f;
        float b_neg = w + a;

        return ((((a * x_offset) - b_neg) * x_offset + c) * x_offset + y0);
    }
};

class WaveOsc
{
public:
    WaveOsc() {}
    ~WaveOsc() {}

    /** Initializes the Oscillator

        \param sample_rate - sample rate of the audio engine being run, and the frequency that the Process function will be called.
        \param wave - pointer to the wave to iterate through.

        Defaults:
        - freq_ = 100 Hz
        - amp_ = 0.5
        - waveform_ = sine wave.
    */
    void Init(float sample_rate, Wave *wave)
    {
        sr_ = sample_rate;
        sr_recip_ = 1.0f / sample_rate;
        freq_ = 100.0f;
        amp_ = 0.5f;
        phase_ = 0.0f;
        phase_inc_ = CalcPhaseInc(freq_);

        waveform_ = wave;
        SetWaveform(wave);
    }

    /** Changes the frequency of the Oscillator, and recalculates phase increment.

        \param f - Oscillator frequency in Hz.
     */
    inline void SetFreq(const float f)
    {
        freq_ = f;
        phase_inc_ = CalcPhaseInc(f);
    }

    /** Sets the amplitude of the waveform.
     */
    inline void SetAmp(const float a) { amp_ = a; }

    /** Sets the next waveform to be synthesized by the Process() function.
     */
    inline void SetWaveform(Wave *wave)
    {
        nextWave_ = wave;
        wave_size_ = wave->wave_size;
    }

    /** Returns true if cycle is at end of cycle. Set during call to Process.
     */
    inline bool IsEOC() { return eoc_; }

    /** Processes the waveform to be generated, returning one sample. This should be called once per sample period.
     */
    float Process();

    /** Adds a value 0.0-1.0 (mapped to 0.0-wave_size_) to the current phase.
     */
    void PhaseAdd(float _phase) { phase_ += (_phase * wave_size_); }

    /** Resets the phase to the input argument. If no argumeNt is present, it will reset phase to 0.0;
     */
    void Reset(float _phase = 0.0f) { phase_ = _phase; }

private:
    float CalcPhaseInc(float f);

    Wave *waveform_;
    Wave *nextWave_;
    size_t wave_size_ = 1;

    float amp_, freq_;
    float sr_, sr_recip_, phase_, phase_inc_;
    bool eoc_;
};
