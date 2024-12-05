#pragma once
 
//#include <juce_audio_basics/juce_audio_basics.h>
//#include <juce_audio_processors/juce_audio_processors.h>

#include <JuceHeader.h>

#include "Synthesis/MasterWindow.h"

class SineWaveSound   : public juce::SynthesiserSound
{
public:
    SineWaveSound() {}

    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
};


class SineWaveVoice   : public juce::SynthesiserVoice
{ 
private:
    double frequencyHz = 0.0f, level = 0.0f, time = 0.0f, timeStep;
    
public:
    SineWaveVoice()
    {
        timeStep = 1 / (double)getSampleRate();
    }

    MasterWindow masterWindow;

    bool canPlaySound (juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity,
                    juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    { 
        frequencyHz = (double)juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        masterWindow.SetNoteFreq(frequencyHz);
        level = 1.0f;
        masterWindow.SetNoteOnTime(this->time);
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        masterWindow.SetNoteOnTime(this->time);
        level = 0.0f;
		clearCurrentNote();
    }

    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}

    void renderNextBlock (juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
		while (--numSamples >= 0)
		{
            float currentSample = level * masterWindow.MixSound(time);

			for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
				outputBuffer.addSample (i, startSample, currentSample);

			++startSample;
            time += timeStep;
		}
    }
};

 
