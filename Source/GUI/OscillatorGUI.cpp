#include "OscillatorGUI.h"

OscillatorGUI::OscillatorGUI(Synth2AudioProcessor& p)
	: processor(p)
{
	setSize(200, 200);

	//levelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	//levelSlider.setRange(0.0f, 1.0f);
	//levelSlider.setValue(0.5f);
	//addAndMakeVisible(&levelSlider);
    levelSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    levelSlider.setRange (0.0, 127.0, 1.0);
    levelSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    levelSlider.setPopupDisplayEnabled (true, false, this);
    levelSlider.setTextValueSuffix (" Volume");
    levelSlider.setValue(1.0);
    addAndMakeVisible(&levelSlider);

	levelAttachment.reset(new SliderAttachment(processor.parameters, "level", levelSlider));
}

void OscillatorGUI::paint(juce::Graphics& g)
{
    //juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);

    //g.fillAll(juce::Colours::black);
    //g.setColour(juce::Colours::white);
    //g.drawText("Filter", titleArea, juce::Justification::centredTop);

    //juce::Rectangle<float> area (25, 25, 150, 150);

    //g.setColour(juce::Colours::yellow);
    //g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void OscillatorGUI::resized()
{
    levelSlider.setBounds(40, 30, 20, getHeight() - 60);

}
