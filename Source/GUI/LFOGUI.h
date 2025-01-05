#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../paramNames.h"
#include "Knob.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


class LFOGUI : public juce::Component
{
private:
	//int id;
public:
	LFOGUI(Synth3AudioProcessor& p)
		: processor(p),
		amountPanel(p, juce::Colours::transparentBlack,
			0.0f, 1.0f, 0.01, 0.2f,
			"Amount", PARAMS_LFO_PHASE_AMOUNT
		),
		freqPanel(p, juce::Colours::transparentBlack,
			0.1f, 20.0f, 0.01, 0.6f,
			"Freq.", PARAMS_LFO_PHASE_FREQUENCY
		)
	{
		setSize(150, 150);
		
		titleLabel.setText(labelText, juce::dontSendNotification);
		addAndMakeVisible(&titleLabel);

		addAndMakeVisible(&amountPanel);
		addAndMakeVisible(&freqPanel);
	}

	void resized() override
	{
		auto area = getLocalBounds();
		titleLabel.setBounds(area.removeFromTop(20));
		amountPanel.setBounds(area.removeFromLeft(80));
		freqPanel.setBounds(area.removeFromLeft(80));
	}

private:

	Synth3AudioProcessor& processor;

	juce::String labelText = "Pitch LFO";
	juce::Label titleLabel;

	Knob amountPanel;
	Knob freqPanel; 
};
