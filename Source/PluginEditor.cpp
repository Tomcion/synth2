 #include "PluginProcessor.h"
#include "PluginEditor.h"


Synth2AudioProcessorEditor::Synth2AudioProcessorEditor (Synth2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscComponent(p)
{
    addAndMakeVisible(oscComponent);

	 setSize (600, 300); 
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
    //oscComponent.setBounds(40, 30, 20, getHeight() - 60);
}
