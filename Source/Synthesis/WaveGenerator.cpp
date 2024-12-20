#include "WaveGenerator.h"
#include "LFO.h"

#include <JuceHeader.h>


constexpr float PI = juce::MathConstants<float>::pi;

const double WaveGenerator::ToRad(double n)
{
    return n * 2.0 * PI;
}

const double WaveGenerator::ToHz(double n)
{
    return n / (2.0 * PI);
}

const double WaveGenerator::SineWave(double time)
{
    double output = sin(freq_rad * time + phase.GetValue());
    return output * (double)amplitude;
}

const double WaveGenerator::TriangleWave(double time)
{
    double output = (2.0f / PI) * asin(sin(freq_rad * time + phase.GetValue()));
    return output * (double)amplitude;
}

const double WaveGenerator::SquareWave(double time)
{
    double output = sin(freq_rad * time + phase.GetValue()) > 0 ? 1.0f : -1.0f;
    return output * (double)amplitude;
}

const double WaveGenerator::SawtoothWave(double time)
{
    double x = time * ToHz(freq_rad) + ToHz(phase.GetValue());
    double output = 2.0f * (x - std::floor(0.5f + x));
    return output * (double)amplitude;
} 

const double WaveGenerator::WhiteNoise(double time)
{
    double random = (float)rand() / (float)RAND_MAX;

    return ((random * 2.0f) - 1.0f) * (double)amplitude;
} 

void WaveGenerator::UpdatePhase(double time)
{ 
    if (this->PhaseModulator == nullptr)
        return;
    (this->PhaseModulator)->CalcPMAmplitude(this->freq_rad);
    (this->phase).CalcModuletedValue(time);

}

void WaveGenerator::UpdateParameters(double time)
{ 
    return;
}

WaveGenerator::WaveGenerator(WaveType type = SINE, float amplitude = 0.3f, float freq_rad = 0.0f)
    : type(type), amplitude(amplitude), freq_rad(freq_rad),
    PhaseModulator(nullptr),
    phase("Phase", 0.0f, 0.0f, ToRad(180.0f))
{
}

void WaveGenerator::SetPhaseModulator(PhaseLFO* lfo)
{
    this->PhaseModulator = lfo;
    (this->phase).SetAutomator((ParameterAutomator*)lfo);
}

const double WaveGenerator::ProduceWave(double time)
{
    UpdateParameters(time);
    UpdatePhase(time);

    switch (this->type)
    {
    case SINE:
        return SineWave(time);
    case TRIANGLE:
        return TriangleWave(time);
    case SQUARE:
        return SquareWave(time);
    case SAWTOOTH:
        return SawtoothWave(time);
    case NOISE:
        return WhiteNoise(time);
    } 
}

