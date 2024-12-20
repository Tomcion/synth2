#pragma once 
#include "WaveGenerator.h"
#include "ModulableField.h"
#include "LFO.h"
 

class Oscillator : public WaveGenerator {
private:
    char id;
    std::string windowName;
    int MAX_OCTAVE = 5;

    int octave;

    float raw_freq_rad;

    float detune;
    //ModulableField detune; 
    //ModFieldList mod_fields;
 
public:
    //void  AddAutomatorDetune(ParameterAutomator* aut);

    Oscillator(char id, WaveType type, float amplitude, int octave);

    void SetState(int wf, float level, int octave, float detune);

    void SetId(char num); 

    const int GetNumber(); 

    void SetOscFrequencyRad(double frequency); 

    void UpdateFields(double time);

    void UpdateParameters(double time) override;

    void RenderOsc();
};

class OscillatorsWindow : public WindowSection {
private:
    double lowest_octave = 55.0;
    std::vector<Oscillator*> oscs;
    double note_freq;
 
public:
    virtual void RenderWindow();

    void SetStateWithIndex(int i, int wf, float level, int octave, float detune);

    OscillatorsWindow();

    ~OscillatorsWindow();

    void AddOscillator(Oscillator* osc); 

    void SetNoteFrequency(float note_freq); 

    double MixOscillators(double time);
}; 
