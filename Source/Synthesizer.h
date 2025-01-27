#pragma once
 
#include <JuceHeader.h>

#include "Synthesis/Envelope.h"
#include "Synthesis/Oscillator.h"
#include "Synthesis/LFO.h"
#include "Synthesis/Saturator.h"
#include "Synthesis/Filter.h"
 
class CustomSynthSound : public juce::SynthesiserSound
{
public:
    CustomSynthSound() {}

    bool appliesToNote(int) override
    {
        return true;
    }

    bool appliesToChannel(int) override
    {
        return true;
    }
};


class CustomSynthVoice : public juce::SynthesiserVoice
{ 
private:
    double frequencyHz = 0.0f, level = 0.0f, time = 0.0f, timeStep, newSample = 0.0f;
    int id;

    juce::Synthesiser& synth;
    
    OscillatorsWindow oscillatorsWindow;
    EnvelopesWindow envelopesWindow;
    LFOsWindow lfosWindow;

    Envelope* masterEnvelope;
    Saturator* saturator;
    Biquad* filter;

    PhaseLFO* phaseLFO;

    //juce::dsp::ProcessorChain<juce::dsp::LadderFilter<float>> processorChain;

public:
    CustomSynthVoice(juce::Synthesiser& synthesiser, int id)
        : synth(synthesiser), id(id)
    {
        timeStep = 1 / (double)getSampleRate();

        // Initializtion parameters don't matter here (they will be overriden anyway)
		Oscillator* osc1 = new Oscillator(1, SAWTOOTH, 0.31f, 1);
		oscillatorsWindow.AddOscillator(osc1);

		Oscillator* osc2 = new Oscillator(2, SQUARE, 0.21f, 0);
		oscillatorsWindow.AddOscillator(osc2);

		Oscillator* osc3 = new Oscillator(3, NOISE, 0.03f, 3);
		oscillatorsWindow.AddOscillator(osc3);

        masterEnvelope = new Envelope(0.0f, 0.3f, 0.5f, 0.3f);

		filter = new Biquad();
		filter->setBiquad(bq_type_lowpass, 0.04, 3.55, 0);
 
		saturator = new Saturator(10.0f, 0.36f, true);

        phaseLFO = new PhaseLFO("LFO Phase", 0.3f, 6.0f);
        osc1->SetPhaseModulator(phaseLFO);
        osc2->SetPhaseModulator(phaseLFO);
        osc3->SetPhaseModulator(phaseLFO);

        //auto& filter = processorChain.get<0>();
        //filter.setCutoffFrequencyHz(500.0f);
        //filter.setResonance(0.7f);
        //filter.setMode(juce::dsp::LadderFilter<float>::Mode::LPF24);
    }

    ~CustomSynthVoice()
    {
        delete masterEnvelope;
        delete saturator;
        delete filter;
        delete phaseLFO;
    }

    void prepareToPlayVoice(double sampleRate, int samplesPerBlock, int numChannels)
    {
        //juce::dsp::ProcessSpec spec;
        //spec.sampleRate = sampleRate;
        //spec.maximumBlockSize = samplesPerBlock;
        //spec.numChannels = numChannels;
        //processorChain.prepare(spec);
    }

    void SetOscillatorWithIndex(int i, int wf, float level, int octave, float detune)
    {
        oscillatorsWindow.SetStateWithIndex(i, wf, level, octave, detune);
    }

    void SetMasterEnvelope(float attack, float decay, float sustain, float release)
    {
        masterEnvelope->SetState(attack, decay, sustain, release);
    }

    void SetSaturator(bool enabled, float drive, float output)
    {
        saturator->SetState(enabled, drive, output);
    }

    void SetLowPassFilter(float cutoff, float resonance)
    {
        //filter->setFc(cutoff);
        //filter->setQ(resonance);
    }

    void SetPhaseLFO(float amount, float freq)
    {
        phaseLFO->SetState(amount, freq);
    }

    void SetNoteFreq(float freq)
    {
        oscillatorsWindow.SetNoteFrequency(freq);
    }
    
    void SetNoteOnTime(double time)
    {
        //envelopesWindow.SetNoteOnTime(time);
        masterEnvelope->SetNoteOnTime(time);
    }

    void SetNoteOffTime(double time)
    {
        //envelopesWindow.SetNoteOffTime(time);
        masterEnvelope->SetNoteOffTime(time);
    } 

    double MixSound(double time)
    {
        double output = oscillatorsWindow.MixOscillators(time);
        output *= masterEnvelope->CalcAutomation(time);
        //if (output == 0.0f)
        //    clearCurrentNote();

        output = filter->process(output); // filter nie dziala ciagle bo sie odswierza za czesto (chyba)
        output = saturator->Saturate(output);
        return output;
    }

    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<CustomSynthSound*> (sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity,
                    juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    { 
        frequencyHz = (double)juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        SetNoteFreq(frequencyHz);
        //level = 1.0f;

    //    CustomSynthVoice* voice;
    //    DBG(midiNoteNumber);
    //    for (int i = 0; i < synth.getNumVoices(); i++)
    //    {
    //        if (voice = dynamic_cast<CustomSynthVoice*>(synth.getVoice(i)))
    //        { 
				//DBG(juce::String(voice->id) + " " + juce::String(this->id) + " " + juce::String((int)(voice->id != this->id)) + " " + juce::String((int)(midiNoteNumber == voice->getCurrentlyPlayingNote())));
    //            if (midiNoteNumber == voice->getCurrentlyPlayingNote()
    //                && voice->id != this->id)
    //            {
    //                voice->clearCurrentNote();
    //                break;
    //            }
    //        }
    //    }

        SetNoteOnTime(this->time);
    }

    void stopNote(float /*velocity*/, bool allowTailOff) override
    {
        SetNoteOffTime(this->time);
        //level = 0.0f;
		//clearCurrentNote();
    }

    void pitchWheelMoved(int) override      {}
    void controllerMoved(int, int) override {}

    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    { 
        // mix oscillators
        for (int i = 0; i < numSamples; i++)
        {
            newSample = MixSound(time);

			for (auto j = 0; j < outputBuffer.getNumChannels(); j++)
				outputBuffer.addSample (j, startSample + i, newSample); 

            time += timeStep; 
        }

        // apply filter
        //juce::dsp::AudioBlock<float> audioBlock(outputBuffer);
        //juce::dsp::ProcessContextReplacing<float> context(audioBlock); 
        //processorChain.get<0>().process(context); 

        // apply saturation
        //for (int i = 0; i < numSamples; i++)
        //{ 
        //    for (auto j = 0; j < outputBuffer.getNumChannels(); j++)
        //    {
        //        newSample = outputBuffer.getSample(j, startSample + i);
        //        outputBuffer.addSample(j, startSample + i, newSample);
        //    }
        //}
        
    }
};

 
