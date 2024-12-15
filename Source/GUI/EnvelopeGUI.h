 #include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "Knob.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


class EnvelopeGUI : public juce::Component
{
private:
	//int id;
public:
	EnvelopeGUI(Synth2AudioProcessor& p)
		: processor(p), 
		attackPanel(p, juce::Colours::transparentBlack,
			0.0f, 7.0f, 0.01, 0.3f,
			"Attack", "master_env_attack"
		),
		decayPanel(p, juce::Colours::transparentBlack,
			0.0f, 7.0f, 0.01, 0.3f,
			"Decay", "master_env_decay"
		),
		sustainPanel(p, juce::Colours::transparentBlack,
			0.0f, 7.0f, 0.01, 0.3f,
			"Sustain", "master_env_sustain"
		),
		releasePanel(p, juce::Colours::transparentBlack,
			0.0f, 1.0f, 0.01, 0.7f,
			"Release", "master_env_release"
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
	struct DecayPanel : public juce::Component
	{
		DecayPanel(Synth2AudioProcessor& p, juce::Colour c)
			: processor(p)
		{ 
			decaySlider.setSliderStyle (juce::Slider::LinearBarVertical);
			decaySlider.setRange (0.0, 7.0, 0.05);
			decaySlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
			decaySlider.setPopupDisplayEnabled (true, false, this);
			decaySlider.setTextValueSuffix (" Decay");
			decaySlider.setValue(0.3);
			addAndMakeVisible(&decaySlider);

			decayLabel.setText("Decay:", juce::dontSendNotification);
			//levelLabel.attachToComponent(&levelSlider, false);
			addAndMakeVisible(&decayLabel);

			juce::String paramId = "master_env_decay";
			decayAttachment.reset(new SliderAttachment(processor.parameters, paramId, decaySlider));
		}

		void paint(juce::Graphics& g) override
		{
		}

		void resized() override
		{
			//auto bounds = getLocalBounds();
			decayLabel.setBounds(20, 20, 75, 20);
			decaySlider.setBounds(20, 40, 20, 70);
		}
 
		Synth2AudioProcessor& processor;

		juce::Slider decaySlider;
		juce::Label decayLabel;
		std::unique_ptr<SliderAttachment> decayAttachment;
	};

	Synth2AudioProcessor& processor; 

	Knob attackPanel;
	Knob decayPanel;
	Knob sustainPanel;
	Knob releasePanel;

};
