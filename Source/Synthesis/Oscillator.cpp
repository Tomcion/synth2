#include "Oscillator.h"

#include <JuceHeader.h>

void  Oscillator::AddAutomatorDetune(ParameterAutomator* aut)
{
    (this->detune).SetAutomator(aut);
}

Oscillator::Oscillator(char id, WaveType type, float amplitude, int octave)
    : WaveGenerator(type, amplitude, 0.0f), octave(octave),
      detune("Detune", 0.0f, -1.0f, 1.0f)
{
    mod_fields.AddField(&detune);
    this->SetId(id);
}

void Oscillator::SetState(int wf, float level, int octave, float detune)
{
	this->type = (WaveType)wf;
	this->amplitude = level;
	this->octave = octave;
	//this->detune = detune;
}

void Oscillator::SetId(char num)
{
    this->id = num;
    windowName = "Oscillator " + std::to_string(num);
}

const int Oscillator::GetNumber()
{
    return this->id;
}

void Oscillator::SetOscFrequencyRad(double frequency)
{
    //this->raw_freq_rad = ToRad(frequency * pow(2, octave));
    this->raw_freq_rad = ToRad(frequency);
}

void Oscillator::UpdateFields(double time)
{
    mod_fields.UpdateFields(time);
}

void Oscillator::UpdateParameters(double time)
{
    float detuneValue = (this->detune).GetValue();
    this->freq_rad = this->raw_freq_rad * pow(2.0f, detuneValue / 12.0f);
}

void Oscillator::RenderOsc()
{
} 

void OscillatorsWindow::SetStateWithIndex(int i, int wf, float level, int octave, float detune)
{
	oscs[i]->SetState(wf, level, octave, detune);
}

void OscillatorsWindow::RenderWindow()
{
    for (int i = 0; i < oscs.size(); i++)
        oscs[i]->RenderOsc();
}

OscillatorsWindow::OscillatorsWindow()
{ 
    this->name = "Oscillators";
    this->note_freq = 0.0f; 
}

OscillatorsWindow::~OscillatorsWindow()
{ 
    for (int i = 0; i < oscs.size(); i++)
        delete[] oscs[i];
} 

void OscillatorsWindow::AddOscillator(Oscillator* osc)
{
    oscs.push_back(osc);
}

void OscillatorsWindow::SetNoteFrequency(float note_freq)
{ 
    for (int i = 0; i < oscs.size(); i++)
    {
        oscs[i]->SetOscFrequencyRad(note_freq);
    }
}

//void OscillatorsWindow::SetNoteFrequency(int note)
//{
//    if (note == -1)
//        note_freq = 0.0;
//    else
//    {
//        note_freq = lowest_octave * pow(halfToneRatio, note);
//        note_freq = pow(halfToneRatio, note);
//    }
//
//    for (int i = 0; i < oscs.size(); i++)
//    {
//        oscs[i]->SetOscFrequencyRad(note_freq);
//    }
//}

double OscillatorsWindow::MixOscillators(double time)
{
    double output = 0.0;
    for (int i = 0; i < oscs.size(); i++)
    {
        oscs[i]->UpdateFields(time); 
        output += (this->oscs[i])->ProduceWave(time);
    }
    return output;
}
