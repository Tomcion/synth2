 #include "PluginProcessor.h"
#include "PluginEditor.h"


Synth3AudioProcessorEditor::Synth3AudioProcessorEditor (Synth3AudioProcessor& p)
    : AudioProcessorEditor (&p),
    audioProcessor (p), oscPanel(p), masterEnvPanel(p),
    filterPanel(p), saturatorPanel(p), phaseLfoPanel(p)
{ 
	setSize (900, 600); 

    addAndMakeVisible(&oscPanel);
    addAndMakeVisible(&masterEnvPanel);
    addAndMakeVisible(&filterPanel); 
    addAndMakeVisible(&saturatorPanel); 
    addAndMakeVisible(&phaseLfoPanel); 
}

Synth3AudioProcessorEditor::~Synth3AudioProcessorEditor()
{
}
 
//==============================================================================
void Synth3AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    //g.drawFittedText ("Hello World!!", getLocalBounds(), juce::Justification::centred, 1);
}

void Synth3AudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    oscPanel.setBounds(area.removeFromLeft(getWidth() / 2.0f));
    masterEnvPanel.setBounds(area.removeFromTop(getHeight() / 3.0f));
    filterPanel.setBounds(area.removeFromLeft(getWidth() / 4.0f));
    saturatorPanel.setBounds(area.removeFromTop(getHeight() / 3.0f));
    phaseLfoPanel.setBounds(area);
}
