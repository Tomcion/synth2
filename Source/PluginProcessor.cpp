/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth2AudioProcessor::Synth2AudioProcessor()
	: AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
    parameters(*this, nullptr, juce::Identifier("Synth2"),
        {
            std::make_unique<juce::AudioParameterFloat> ("level", "Level", 0.0f, 1.0f, 0.5f)
        })
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

//==============================================================================
const juce::String Synth2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Synth2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Synth2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Synth2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Synth2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Synth2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
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
bool Synth2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Synth2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (voice = dynamic_cast<CustomSynthVoice*>(synth.getVoice(i)))
        {
            auto levelValue = parameters.getRawParameterValue("level");
            voice->SetOscillator(levelValue->load());
        }
    }
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Synth2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Synth2AudioProcessor::createEditor()
{
    return new Synth2AudioProcessorEditor (*this);
}

//==============================================================================
void Synth2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
	auto state = parameters.copyState();
	std::unique_ptr<juce::XmlElement> xml (state.createXml());
	copyXmlToBinary (*xml, destData);
}

void Synth2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName (parameters.state.getType()))
			parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Synth2AudioProcessor();
}
