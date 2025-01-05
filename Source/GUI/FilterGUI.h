#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../paramNames.h"
#include "Knob.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


class FilterGUI : public juce::Component
{
private:
	//int id;
public:
	FilterGUI(Synth3AudioProcessor& p)
		: processor(p),
		cutoffPanel(p, juce::Colours::transparentBlack,
			0.0f, 1.0f, 0.01, 0.04f,
			"Cutoff", PARAMS_LOWPASS_CUTOFF
		),
		resonancePanel(p, juce::Colours::transparentBlack,
			0.0f, 5.0f, 0.01, 3.55f,
			"Resonance", PARAMS_LOWPASS_RESONANCE
		)
	{
		setSize(150, 150);

		titleLabel.setText(labelText, juce::dontSendNotification);
		addAndMakeVisible(&titleLabel);

		addAndMakeVisible(&cutoffPanel);
		addAndMakeVisible(&resonancePanel);
	}

	void resized() override
	{
		auto area = getLocalBounds();
		titleLabel.setBounds(area.removeFromTop(20));
		cutoffPanel.setBounds(area.removeFromLeft(80));
		resonancePanel.setBounds(area.removeFromLeft(80));
	}

private:

	Synth3AudioProcessor& processor;

	juce::String labelText = "LP Filter";
	juce::Label titleLabel;

	Knob cutoffPanel;
	Knob resonancePanel; 
};