#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "GUI/OscillatorGUI.h"
#include "GUI/EnvelopeGUI.h"
#include "GUI/FilterGUI.h"
#include "GUI/SaturatorGUI.h"
#include "GUI/LFOGUI.h"

class Synth3AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Synth3AudioProcessorEditor (Synth3AudioProcessor&);
    ~Synth3AudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Synth3AudioProcessor& audioProcessor;
    OscillatorsPanel oscPanel;
    EnvelopeGUI masterEnvPanel;
    FilterGUI filterPanel;
    SaturatorGUI saturatorPanel;
    LFOGUI phaseLfoPanel;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth3AudioProcessorEditor)
};
