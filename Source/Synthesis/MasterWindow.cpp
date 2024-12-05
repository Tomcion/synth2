#include "MasterWindow.h"

// jazz whatever
//MasterWindow::MasterWindow()
//{
//    this->name = "Master Window";
//
//    PhaseLFO* lfo1 = new PhaseLFO("LFO Phase", 0.3f, 6.0f);
//    lfosWindow.AddLFO(lfo1);
//
//    LFO* lfo2 = new LFO("LFO Volume", SINE, 0.5f, 1.0f);
//    lfosWindow.AddLFO(lfo2);
//
//    Oscillator* osc1 = new Oscillator(1, SINE, 0.5f, 3);
//    oscillatorsWindow.AddOscillator(osc1);
//
//    Oscillator* osc2 = new Oscillator(2, SQUARE, 0.1f, 1);
//    oscillatorsWindow.AddOscillator(osc2);
//
//    Oscillator* osc3 = new Oscillator(3, NOISE, 0.04f, 3);
//    oscillatorsWindow.AddOscillator(osc3);
//
//    masterEnvelope = new Envelope(0.0f, 0.5f, 0.3f, 3.0f);
//    envelopesWindow.AddEnvelope(masterEnvelope);
//
//    saturator = new Saturator(10.0f, 0.36f, true);
//
//    filter = new Biquad();
//    filter->setBiquad(bq_type_lowpass, 0.06, 3.60, 0);
//
//    osc1->SetPhaseModulator(lfo1);
//    osc2->SetPhaseModulator(lfo1);
//}

// resonant bass
MasterWindow::MasterWindow()
{
    this->name = "Master Window";

    PhaseLFO* lfo1 = new PhaseLFO("LFO Phase", 0.3f, 6.0f);
    lfosWindow.AddLFO(lfo1);

    LFO* lfo2 = new LFO("LFO Volume", SINE, 0.5f, 1.0f);
    lfosWindow.AddLFO(lfo2);

    Oscillator* osc1 = new Oscillator(1, SAWTOOTH, 0.31f, 1);
    oscillatorsWindow.AddOscillator(osc1);

    Oscillator* osc2 = new Oscillator(2, SQUARE, 0.21f, 0);
    oscillatorsWindow.AddOscillator(osc2);

    Oscillator* osc3 = new Oscillator(3, NOISE, 0.03f, 3);
    oscillatorsWindow.AddOscillator(osc3);

    masterEnvelope = new Envelope(0.0f, 0.5f, 0.3f, 3.0f);
    envelopesWindow.AddEnvelope(masterEnvelope);

    saturator = new Saturator(10.0f, 0.36f, true);

    filter = new Biquad();
    filter->setBiquad(bq_type_lowpass, 0.04, 3.55, 0);

    osc1->SetPhaseModulator(lfo1);
    osc2->SetPhaseModulator(lfo1);
}

// sad pads
//MasterWindow::MasterWindow()
//{
//    this->name = "Master Window";
//
//    PhaseLFO* lfo1 = new PhaseLFO("LFO Phase", 0.14f, 0.5f);
//    lfosWindow.AddLFO(lfo1);
//
//    LFO* lfo2 = new LFO("LFO Volume", SINE, 0.5f, 1.0f);
//    lfosWindow.AddLFO(lfo2);
//
//    Oscillator* osc1 = new Oscillator(1, SAWTOOTH, 0.26f, 2);
//    oscillatorsWindow.AddOscillator(osc1);
//
//    Oscillator* osc2 = new Oscillator(2, SQUARE, 0.1f, 0);
//    oscillatorsWindow.AddOscillator(osc2);
//
//    Oscillator* osc3 = new Oscillator(3, NOISE, 0.20f, 3);
//    oscillatorsWindow.AddOscillator(osc3);
//
//    masterEnvelope = new Envelope(1.65f, 1.55f, 0.3f, 1.6f);
//    envelopesWindow.AddEnvelope(masterEnvelope);
//
//    saturator = new Saturator(4.2f, 0.36f, true);
//
//    filter = new Biquad();
//    filter->setBiquad(bq_type_lowpass, 0.06f, 0.85f, 0);
//
//    osc1->SetPhaseModulator(lfo1);
//    osc2->SetPhaseModulator(lfo1);
//}
