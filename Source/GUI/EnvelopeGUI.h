 #include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../paramNames.h"
#include "Knob.h"


typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


class EnvelopeGUI : public juce::Component
{
private:
	//int id;
public:
	EnvelopeGUI(Synth3AudioProcessor& p)
		: processor(p), 
		attackPanel(p, juce::Colours::transparentBlack,
			0.0f, 7.0f, 0.01, 0.3f,
			"Attack", PARAMS_MASTER_ENV_ATTACK
		),
		decayPanel(p, juce::Colours::transparentBlack,
			0.0f, 7.0f, 0.01, 0.3f,
			"Decay", PARAMS_MASTER_ENV_DECAY
		),
		sustainPanel(p, juce::Colours::transparentBlack,
			0.0f, 7.0f, 0.01, 0.3f,
			"Sustain", PARAMS_MASTER_ENV_SUSTAIN
		),
		releasePanel(p, juce::Colours::transparentBlack,
			0.0f, 1.0f, 0.01, 0.7f,
			"Release", PARAMS_MASTER_ENV_RELEASE
		)
	{
		setSize(300, 150);

		addAndMakeVisible(&attackPanel);
		addAndMakeVisible(&decayPanel);
		addAndMakeVisible(&sustainPanel);
		addAndMakeVisible(&releasePanel);
	}

	void resized() override
	{
		auto area = getLocalBounds();
		attackPanel.setBounds(area.removeFromLeft(80));
		decayPanel.setBounds(area.removeFromLeft(80));
		sustainPanel.setBounds(area.removeFromLeft(80));
		releasePanel.setBounds(area.removeFromLeft(80));
	}

private: 

	Synth3AudioProcessor& processor; 

	Knob attackPanel;
	Knob decayPanel;
	Knob sustainPanel;
	Knob releasePanel;

};
