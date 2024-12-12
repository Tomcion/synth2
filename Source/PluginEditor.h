#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "GUI/OscillatorGUI.h"

class Synth2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Synth2AudioProcessorEditor (Synth2AudioProcessor&);
    ~Synth2AudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Synth2AudioProcessor& audioProcessor;
    OscillatorsPanel oscPanel;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth2AudioProcessorEditor)
};
