#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../paramNames.h"
#include "Knob.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


class SaturatorGUI  : public juce::Component
{
private:
	//int id;
public:
	SaturatorGUI(Synth3AudioProcessor& p)
		: processor(p),
		drivePanel(p, juce::Colours::transparentBlack,
			0.0f, 30.0f, 0.05, 10.0f,
			"Drive", PARAMS_SATURATOR_DRIVE
		),
		outputPanel(p, juce::Colours::transparentBlack,
			0.0f, 1.0f, 0.01, 0.5f,
			"Output", PARAMS_SATURATOR_OUTPUT
		)
	{
		setSize(150, 150);

		titleLabel.setText(labelText, juce::dontSendNotification);
		addAndMakeVisible(&titleLabel);

		addAndMakeVisible(&drivePanel);
		addAndMakeVisible(&outputPanel);
	}

	void resized() override
	{
		auto area = getLocalBounds();
		titleLabel.setBounds(area.removeFromTop(20));
		drivePanel.setBounds(area.removeFromLeft(80));
		outputPanel.setBounds(area.removeFromLeft(80));
	}

private:

	Synth3AudioProcessor& processor;
	
	juce::String labelText = "Saturator";
	juce::Label titleLabel;

	Knob drivePanel;
	Knob outputPanel; 
};
