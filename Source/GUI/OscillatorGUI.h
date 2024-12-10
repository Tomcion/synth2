#include <JuceHeader.h>
#include "../PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


class OscillatorGUI : public juce::Component
{
public:
	OscillatorGUI(Synth2AudioProcessor&);
	//~OscillatorGUI();

	void paint(juce::Graphics& g) override;
	void resized() override;

private:
	Synth2AudioProcessor& processor;

	juce::Slider levelSlider;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> levelAttachment;

	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorGUI);
};
