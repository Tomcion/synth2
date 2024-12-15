 #include "PluginProcessor.h"
#include "PluginEditor.h"


Synth2AudioProcessorEditor::Synth2AudioProcessorEditor (Synth2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscPanel(p), masterEnvPanel(p)
{ 
	setSize (900, 600); 

    addAndMakeVisible(&oscPanel);
    addAndMakeVisible(&masterEnvPanel);
}

Synth2AudioProcessorEditor::~Synth2AudioProcessorEditor()
{
}
 
//==============================================================================
void Synth2AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    //g.drawFittedText ("Hello World!!", getLocalBounds(), juce::Justification::centred, 1);
}

void Synth2AudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    oscPanel.setBounds(area.removeFromLeft(getWidth() / 2.0f));
    masterEnvPanel.setBounds(area);
}
