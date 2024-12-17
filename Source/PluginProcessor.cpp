#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "paramNames.h"


Synth2AudioProcessor::Synth2AudioProcessor()
	: AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
    parameters(*this, nullptr, juce::Identifier("Synth2"), createParameterLayout())
{
    synth.clearVoices();
    for (int i = 0; i < 8; ++i)
    {
        synth.addVoice(new CustomSynthVoice());
    }
    synth.clearSounds();
    synth.addSound(new CustomSynthSound());
} 

Synth2AudioProcessor::~Synth2AudioProcessor()
{ 
}

void Synth2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (voice = dynamic_cast<CustomSynthVoice*>(synth.getVoice(i)))
        {
            for (int j = 1; j <= numberOfOscs; j++)
            {
				auto levelValue = parameters.getRawParameterValue(PARAMS_OSC_LEVEL(j));
				auto detuneValue = parameters.getRawParameterValue(PARAMS_OSC_DETUNE(j));
				auto waveformValue = parameters.getRawParameterValue(PARAMS_OSC_WAVETYPE(j));
				auto octaveValue = parameters.getRawParameterValue(PARAMS_OSC_OCTAVE(j));
				voice->SetOscillatorWithIndex(j - 1,
                    waveformValue->load(),
                    levelValue->load(),
                    octaveValue->load(),
                    detuneValue->load()
                );
            }

			auto masterAttackValue = parameters.getRawParameterValue(PARAMS_MASTER_ENV_ATTACK);
			auto masterDecayValue = parameters.getRawParameterValue(PARAMS_MASTER_ENV_DECAY);
			auto masterSustainValue = parameters.getRawParameterValue(PARAMS_MASTER_ENV_SUSTAIN);
			auto masterReleaseValue = parameters.getRawParameterValue(PARAMS_MASTER_ENV_RELEASE);
			voice->SetMasterEnvelope(
				masterAttackValue->load(),
				masterDecayValue->load(),
				masterSustainValue->load(),
				masterReleaseValue->load()
			);

			auto lowpassCutoffValue = parameters.getRawParameterValue(PARAMS_LOWPASS_CUTOFF);
			auto lowpassResValue = parameters.getRawParameterValue(PARAMS_LOWPASS_RESONANCE);
			voice->SetLowPassFilter(
				lowpassCutoffValue->load(),
				lowpassResValue->load()
			);
            
			auto saturatorDriveValue = parameters.getRawParameterValue(PARAMS_SATURATOR_DRIVE);
			auto saturatorOutputValue = parameters.getRawParameterValue(PARAMS_SATURATOR_OUTPUT);
			auto saturatorEnabledValue = parameters.getRawParameterValue(PARAMS_SATURATOR_ENABLED);
			voice->SetSaturator(
				saturatorEnabledValue->load(),
				saturatorDriveValue->load(),
				saturatorOutputValue->load()
			);
        }
    }

    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

juce::AudioProcessorValueTreeState::ParameterLayout Synth2AudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;

    for (int i = 1; i <= numberOfOscs; i++)
    {
        params.add(std::make_unique<juce::AudioParameterFloat>(
            PARAMS_OSC_LEVEL(i),
            "Oscillator " + juce::String(i) + " Level",
            0.0f, 1.0f, 0.5f
        ));

        params.add(std::make_unique<juce::AudioParameterFloat>(
            PARAMS_OSC_DETUNE(i),
            "Oscillator " + juce::String(i) + " Detune",
            -1.0f, 1.0f, 0.0f
        ));

        params.add(std::make_unique<juce::AudioParameterInt>(
            PARAMS_OSC_OCTAVE(i),
            "Oscillator " + juce::String(i) + " Octave",
            -3, 3, 0
        ));

        params.add(std::make_unique<juce::AudioParameterInt>(
            PARAMS_OSC_WAVETYPE(i),
            "Oscillator " + juce::String(i) + " Waveform",
            1, 5, 1
        ));
    }

	params.add(std::make_unique<juce::AudioParameterFloat>(
		PARAMS_MASTER_ENV_ATTACK,
        "Master Envelope Attack",
		0.0f, 7.0f, 0.3f
	));

	params.add(std::make_unique<juce::AudioParameterFloat>(
		PARAMS_MASTER_ENV_DECAY,
        "Master Envelope Decay",
		0.0f, 7.0f, 0.3f
	));

	params.add(std::make_unique<juce::AudioParameterFloat>(
        PARAMS_MASTER_ENV_SUSTAIN,
        "Master Envelope Sustain",
		0.0f, 1.0f, 0.5f
	));

	params.add(std::make_unique<juce::AudioParameterFloat>(
		PARAMS_MASTER_ENV_RELEASE,
        "Master Envelope release",
		0.0f, 7.0f, 0.3f
	));

	params.add(std::make_unique<juce::AudioParameterFloat>(
        PARAMS_LOWPASS_CUTOFF,
        "Low Pass Cutoff",
		0.0f, 1.0f, 0.3f
	));

	params.add(std::make_unique<juce::AudioParameterFloat>(
        PARAMS_LOWPASS_RESONANCE,
        "Low Pass Resonance",
		0.0f, 5.0f, 0.3f
	));

	params.add(std::make_unique<juce::AudioParameterBool>(
        PARAMS_SATURATOR_ENABLED,
        "Saturator Enabled",
        true
	));

	params.add(std::make_unique<juce::AudioParameterFloat>(
        PARAMS_SATURATOR_DRIVE,
        "Saturator Drive",
		0.0f, 30.0f, 10.0f
	));

	params.add(std::make_unique<juce::AudioParameterFloat>(
        PARAMS_SATURATOR_OUTPUT, 
        "Saturator Output",
		0.0f, 1.0f, 0.5f
	));

    return params;
}

const juce::String Synth2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Synth2AudioProcessor::acceptsMidi() const
{
    return true;
}

bool Synth2AudioProcessor::producesMidi() const
{
    return false;
}

bool Synth2AudioProcessor::isMidiEffect() const
{
    return false;
}

double Synth2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Synth2AudioProcessor::getNumPrograms()
{
    return 1;
}

int Synth2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Synth2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Synth2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Synth2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void Synth2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	synth.setCurrentPlaybackSampleRate (sampleRate);
}

void Synth2AudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth2AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif
 
bool Synth2AudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* Synth2AudioProcessor::createEditor()
{
    return new Synth2AudioProcessorEditor (*this);
}

void Synth2AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	auto state = parameters.copyState();
	std::unique_ptr<juce::XmlElement> xml(state.createXml());

	//juce::File file = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("state1.xml");
	//file.replaceWithText(xml->toString());

	copyXmlToBinary (*xml, destData);
}

void Synth2AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Synth2AudioProcessor();
}
