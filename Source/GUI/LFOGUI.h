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

		addAndMakeVisible(&amountPanel);
		addAndMakeVisible(&freqPanel);
	}

	void resized() override
	{
		auto area = getLocalBounds();
		amountPanel.setBounds(area.removeFromLeft(80));
		freqPanel.setBounds(area.removeFromLeft(80));
	}

private:

	Synth3AudioProcessor& processor;

	Knob amountPanel;
	Knob freqPanel; 
};
