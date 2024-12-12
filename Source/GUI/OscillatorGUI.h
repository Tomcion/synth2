#include <JuceHeader.h>
#include "../PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;


class OscillatorGUI : public juce::Component
{
public:
	OscillatorGUI(Synth2AudioProcessor& p)
		: processor(p),
		waveformPanel(p, juce::Colours::transparentBlack),
		detunePanel(p, juce::Colours::transparentBlack),
		octavePanel(p, juce::Colours::transparentBlack),
		levelPanel(p, juce::Colours::transparentBlack)
	{
		setSize(400, 300);

		addAndMakeVisible(waveformPanel);
		addAndMakeVisible(levelPanel); 
		addAndMakeVisible(octavePanel); 
		addAndMakeVisible(detunePanel); 
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
		WaveformPanel(Synth2AudioProcessor& p, juce::Colour c) : backgroundColour(c), processor(p)
		{
			waveformLabel.setText("Waveform: ", juce::dontSendNotification);
			waveformLabel.attachToComponent(&waveformComboBox, false);
			addAndMakeVisible(&waveformLabel);

			waveformComboBox.addItem("Sine", 1);
			waveformComboBox.addItem("Triangle", 2);
			waveformComboBox.addItem("Square", 3);
			waveformComboBox.addItem("Sawtooth", 4);
			waveformComboBox.addItem("White Noise", 5);
			addAndMakeVisible(&waveformComboBox); 
		}

		void paint(juce::Graphics& g) override
		{
			g.fillAll(backgroundColour);
		}

		void resized() override
		{
			//auto bounds = getLocalBounds();
			waveformLabel.setBounds(20, 20, 150, 20);
			waveformComboBox.setBounds(20, 40, 150, 20);
		}

		Synth2AudioProcessor& processor;

		juce::Colour backgroundColour;
		juce::ComboBox waveformComboBox;
		juce::Label waveformLabel; 
		std::unique_ptr<ComboBoxAttachment> waveformAttachment; 
	};

	struct DetunePanel : public juce::Component
	{
		DetunePanel(Synth2AudioProcessor& p, juce::Colour c) : backgroundColour(c), processor(p)
		{ 
			detuneLabel.setText("Detune: ", juce::dontSendNotification);
			//detuneLabel.attachToComponent(&detuneSlider, false);
			addAndMakeVisible(&detuneLabel);

			detuneSlider.setSliderStyle (juce::Slider::LinearBarVertical);
			detuneSlider.setRange (-1.0, 1.0, 0.05);
			detuneSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
			detuneSlider.setPopupDisplayEnabled (true, false, this);
			detuneSlider.setTextValueSuffix (" Detune");
			detuneSlider.setValue(1.0);
			addAndMakeVisible(&detuneSlider); 
		}

		void paint(juce::Graphics& g) override
		{
			g.fillAll(backgroundColour);
		}

		void resized() override
		{
			//auto bounds = getLocalBounds();
			detuneLabel.setBounds(20, 20, 75, 20);
			detuneSlider.setBounds(20, 40, 20, 70);
		}

		Synth2AudioProcessor& processor;

		juce::Colour backgroundColour;
		juce::Slider detuneSlider;
		juce::Label detuneLabel;
		std::unique_ptr<SliderAttachment> detuneAttachment;
	};

	struct LevelPanel : public juce::Component
	{
		LevelPanel(Synth2AudioProcessor& p, juce::Colour c) : backgroundColour(c), processor(p)
		{ 
			levelSlider.setSliderStyle (juce::Slider::LinearBarVertical);
			levelSlider.setRange (0.0, 1.0, 0.05);
			levelSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
			levelSlider.setPopupDisplayEnabled (true, false, this);
			levelSlider.setTextValueSuffix (" Volume");
			levelSlider.setValue(1.0);
			addAndMakeVisible(&levelSlider);

			levelLabel.setText("Volume: ", juce::dontSendNotification);
			//levelLabel.attachToComponent(&levelSlider, false);
			addAndMakeVisible(&levelLabel);

			levelAttachment.reset(new SliderAttachment(processor.parameters, "level", levelSlider));
		}

		void paint(juce::Graphics& g) override
		{
			g.fillAll(backgroundColour);
		}

		void resized() override
		{
			//auto bounds = getLocalBounds();
			levelLabel.setBounds(20, 20, 75, 20);
			levelSlider.setBounds(20, 40, 20, 70);
		}

		Synth2AudioProcessor& processor;

		juce::Colour backgroundColour;
		juce::Slider levelSlider;
		juce::Label levelLabel;
		std::unique_ptr<SliderAttachment> levelAttachment;
	};

	struct OctavePanel : public juce::Component
	{
		OctavePanel(Synth2AudioProcessor& p, juce::Colour c) : backgroundColour(c), processor(p)
		{ 
			octaveSlider.setSliderStyle (juce::Slider::LinearBarVertical);
			octaveSlider.setRange (0, 5, 1);
			octaveSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
			octaveSlider.setPopupDisplayEnabled (true, false, this);
			octaveSlider.setTextValueSuffix (" Octave");
			octaveSlider.setValue(3);
			addAndMakeVisible(&octaveSlider);

			octaveLabel.setText("Octave: ", juce::dontSendNotification);
			//levelLabel.attachToComponent(&levelSlider, false);
			addAndMakeVisible(&octaveLabel);

		}

		void paint(juce::Graphics& g) override
		{
			g.fillAll(backgroundColour);
		}

		void resized() override
		{
			//auto bounds = getLocalBounds();
			octaveLabel.setBounds(20, 20, 75, 20);
			octaveSlider.setBounds(20, 40, 20, 70);
		}

		Synth2AudioProcessor& processor;

		juce::Colour backgroundColour;
		juce::Slider octaveSlider;
		juce::Label octaveLabel;
		std::unique_ptr<SliderAttachment> octaveAttachment;
	};

	Synth2AudioProcessor& processor;

	WaveformPanel waveformPanel;
	DetunePanel detunePanel; 
	LevelPanel levelPanel; 
	OctavePanel octavePanel; 
 
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorGUI);
};
