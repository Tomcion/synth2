#pragma once
 
//#include <juce_audio_basics/juce_audio_basics.h>
//#include <juce_audio_processors/juce_audio_processors.h>

#include <JuceHeader.h>

#include "Synthesis/Envelope.h"
#include "Synthesis/Oscillator.h"
#include "Synthesis/LFO.h"
#include "Synthesis/Saturator.h"
#include "Synthesis/Filter.h"
 
class CustomSynthSound   : public juce::SynthesiserSound
{
public:
    CustomSynthSound() {}

    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
};


class CustomSynthVoice   : public juce::SynthesiserVoice
{ 
private:
    double frequencyHz = 0.0f, level = 0.0f, time = 0.0f, timeStep;
    
    OscillatorsWindow oscillatorsWindow;
    EnvelopesWindow envelopesWindow;
    LFOsWindow lfosWindow;

    Envelope* masterEnvelope;
    Saturator* saturator;
    Biquad* filter;

    Oscillator mainOscillator;
public:
    CustomSynthVoice()
        : mainOscillator(1, SINE, 0.5f, 3)
    {
        timeStep = 1 / (double)getSampleRate();
    }

    void SetOscillator(float level)
    {
        mainOscillator.setState(level);
    }

    void SetNoteFreq(float freq)
    {
        mainOscillator.SetOscFrequencyRad(freq);
    }
    
    void SetNoteOnTime(double time)
    {
        envelopesWindow.SetNoteOnTime(time);
    }

    void SetNoteOffTime(double time)
    {
        envelopesWindow.SetNoteOffTime(time);
    }

    double MixSound(double time)
    {
        double output = mainOscillator.ProduceWave(time);
        //double output = oscillatorsWindow.MixOscillators(time);
        //output *= masterEnvelope->CalcAutomation(time);
        //output = filter->process(output);
        //output = saturator->Saturate(output);
        return output;
    }

    bool canPlaySound (juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<CustomSynthSound*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity,
                    juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    { 
        frequencyHz = (double)juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        SetNoteFreq(frequencyHz);
        level = 1.0f;
        SetNoteOnTime(this->time);
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        SetNoteOnTime(this->time);
        level = 0.0f;
		clearCurrentNote();
    }

    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}

    void renderNextBlock (juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
		while (--numSamples >= 0)
		{
            float currentSample = level * MixSound(time);

			for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
				outputBuffer.addSample (i, startSample, currentSample);

			++startSample;
            time += timeStep;
		}
    }
};

 
