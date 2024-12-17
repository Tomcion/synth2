#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../paramNames.h"
#include "Knob.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;


class OscillatorGUI : public juce::Component
{
private:
	int id;

public:
	OscillatorGUI(Synth2AudioProcessor& p, int id)
		: processor(p), id(id),
		waveformPanel(p, juce::Colours::transparentBlack, id),
		detunePanel(p, juce::Colours::transparentBlack,
			-1.0f, 1.0f, 0.01f, 0.0f,
			"Detune", "osc" + juce::String(id) + "_detune"
		),
		octavePanel(p, juce::Colours::transparentBlack,
			-3, 3, 1, 0,
			"Octave", "osc" + juce::String(id) + "_octave"
		),
		levelPanel(p, juce::Colours::transparentBlack,
			0.0f, 1.0f, 0.01f, 0.5f,
			"Level", "osc" + juce::String(id) + "_level"
		)
	{
		setSize(250, 200);

		addAndMakeVisible(&waveformPanel);
		addAndMakeVisible(&levelPanel); 
		addAndMakeVisible(&octavePanel); 
		addAndMakeVisible(&detunePanel); 
	}

	void paint(juce::Graphics& g) override
	{
	}

	void resized() override
	{
		auto area = getLocalBounds();
		waveformPanel.setBounds(area.removeFromTop(60));
		levelPanel.setBounds(area.removeFromLeft(80));
		octavePanel.setBounds(area.removeFromLeft(80));
		detunePanel.setBounds(area);
	}

private:
	struct WaveformPanel : public juce::Component
	{
		WaveformPanel(Synth2AudioProcessor& p, juce::Colour c, int id)
			: backgroundColour(c), processor(p), oscId(id)
		{
			waveformLabel.setText("Waveform: ", juce::dontSendNotification);
			waveformLabel.attachToComponent(&waveformComboBox, false);
			addAndMakeVisible(&waveformLabel);

			waveformComboBox.addItem("Sine", 1);
			waveformComboBox.addItem("Triangle", 2);
			waveformComboBox.addItem("Square", 3);
			waveformComboBox.addItem("Sawtooth", 4);
			waveformComboBox.addItem("White Noise", 5);
			waveformComboBox.setSelectedItemIndex(1);
			addAndMakeVisible(&waveformComboBox); 

			juce::String paramId = PARAMS_OSC_WAVETYPE(id);
			waveformAttachment.reset(new ComboBoxAttachment(processor.parameters, paramId, waveformComboBox));
		}

		void paint(juce::Graphics& g) override
		{
			g.fillAll(backgroundColour);
		}

		void resized() override
		{
			//auto bounds = getLocalBounds();
			waveformLabel.setBounds(20, 10, 150, 20);
			waveformComboBox.setBounds(20, 30, 150, 20);
		}

		int oscId;

		Synth2AudioProcessor& processor;

		juce::Colour backgroundColour;
		juce::ComboBox waveformComboBox;
		juce::Label waveformLabel; 
		std::unique_ptr<ComboBoxAttachment> waveformAttachment; 
	}; 

	Synth2AudioProcessor& processor;

	WaveformPanel waveformPanel;
	Knob detunePanel; 
	Knob levelPanel; 
	Knob octavePanel; 
 
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorGUI);
};


class OscillatorsPanel : public juce::Component
{
public:
	OscillatorsPanel(Synth2AudioProcessor& p)
		: processor(p)
	{
		for (int i = 1; i <= p.numberOfOscs; i++)
			oscComponents.push_back(new OscillatorGUI(p, i)); 

		for (int i = 0; i < oscComponents.size(); i++)
			addAndMakeVisible(oscComponents[i]);
	}

	void resized() override
	{
		juce::FlexBox fb;
		fb.flexDirection = juce::FlexBox::Direction::column;
		fb.flexWrap = juce::FlexBox::Wrap::wrap;
		fb.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
		fb.alignContent = juce::FlexBox::AlignContent::center;

		for (auto* osc : oscComponents)
			fb.items.add(juce::FlexItem(*osc).withMinWidth(250).withMinHeight(200));
			//fb.items.add(juce::FlexItem(*osc));
		
		fb.performLayout(getLocalBounds());
	}

private: 
	std::vector<OscillatorGUI*> oscComponents;
	Synth2AudioProcessor& processor;
};

