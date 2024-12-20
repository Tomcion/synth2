#pragma once

#include <JuceHeader.h>
#include "Synthesizer.h"


class Synth3AudioProcessor  : public juce::AudioProcessor
{
public:
    Synth3AudioProcessor();
    ~Synth3AudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
   #endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
 
    int numberOfOscs = 3;

    juce::AudioProcessorValueTreeState parameters; 
private:

    juce::Synthesiser synth;
    CustomSynthVoice* voice;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth3AudioProcessor)
};
