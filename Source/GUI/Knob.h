#pragma once
#include "../PluginProcessor.h"
#include <JuceHeader.h>

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


struct Knob : public juce::Component
{
private:
	juce::String displayName;	// parameter name to display
	juce::String parameterName;	// for the value tree parameter id
 
	Synth3AudioProcessor& processor;

	juce::Colour backgroundColour;
	juce::Slider slider;
	juce::Label label;
	std::unique_ptr<SliderAttachment> attachment;

public:
	Knob(Synth3AudioProcessor& p, juce::Colour c,
		float minVal, float maxVal, float interval, float defaultValue,
		juce::String displayName, juce::String parameterName)
		: backgroundColour(c), processor(p),
		displayName(displayName), parameterName(parameterName)
	{ 
		slider.setSliderStyle (juce::Slider::LinearBarVertical);
		//slider.setSliderStyle (juce::Slider::Rotary);
		slider.setRange (minVal, maxVal, interval);
		slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
		slider.setPopupDisplayEnabled (true, false, this);
		slider.setTextValueSuffix (" " + displayName);
		slider.setValue(defaultValue);
		addAndMakeVisible(&slider);

		label.setText(displayName + ":", juce::dontSendNotification);
		//levelLabel.attachToComponent(&levelSlider, false);
		addAndMakeVisible(&label);

		attachment.reset(new SliderAttachment(processor.parameters, parameterName, slider));
	}

	void paint(juce::Graphics& g) override
	{
		g.fillAll(backgroundColour);
	}

	void resized() override
	{
		//auto bounds = getLocalBounds();
		label.setBounds(20, 20, 75, 20);
		slider.setBounds(20, 40, 20, 70);
	} 
};
