#pragma once

#include <JuceHeader.h>

#define PARAMS_OSC_WAVETYPE(id) ("osc" + juce::String(id) + "_wavetype")
#define PARAMS_OSC_LEVEL(id) ("osc" + juce::String(id) + "_level") 
#define PARAMS_OSC_OCTAVE(id) ("osc" + juce::String(id) + "_octave")
#define PARAMS_OSC_DETUNE(id) ("osc" + juce::String(id) + "_detune")
 
#define PARAMS_MASTER_ENV_ATTACK "master_env_attack"
#define PARAMS_MASTER_ENV_DECAY "master_env_decay"
#define PARAMS_MASTER_ENV_SUSTAIN "master_env_sustain"
#define PARAMS_MASTER_ENV_RELEASE "master_env_release"

#define PARAMS_LOWPASS_CUTOFF "lowpass_cutoff"
#define PARAMS_LOWPASS_RESONANCE "lowpass_resonance"

#define PARAMS_SATURATOR_DRIVE "saturator_drive"
#define PARAMS_SATURATOR_OUTPUT "saturator_output"
#define PARAMS_SATURATOR_ENABLED "saturator_enabled"

#define PARAMS_LFO_PHASE_AMOUNT "lfo_phase_amount"
#define PARAMS_LFO_PHASE_FREQUENCY "lfo_phase_frequency"
