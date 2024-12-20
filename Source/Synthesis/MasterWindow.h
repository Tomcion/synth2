#pragma once
#include <Windows.h>
#include <iostream>
#include "Envelope.h"
#include "Oscillator.h"
#include "LFO.h"
#include "Saturator.h"
#include "Filter.h"

class MasterWindow : public WindowSection {
private:
    OscillatorsWindow oscillatorsWindow;
    EnvelopesWindow envelopesWindow;
    LFOsWindow lfosWindow;

    Envelope* masterEnvelope;
    Saturator* saturator;
    Biquad* filter;
public:
    MasterWindow();

    virtual void RenderWindow()
    {
        oscillatorsWindow.RenderWindow();
        envelopesWindow.RenderWindow();
        lfosWindow.RenderWindow();
        saturator->Render();
        filter->RenderFilter();
    }

    void SetNoteFreq(float freq)
    {
        oscillatorsWindow.SetNoteFrequency(freq);
    }
    
    void SetNoteOnTime(double time)
    {
        envelopesWindow.SetNoteOnTime(time);
    }

    void SetNoteOffTime(double time)
    {
        envelopesWindow.SetNoteOffTime(time);
    } 

    double MixSound(double time)
    {
        double output = oscillatorsWindow.MixOscillators(time);
        output *= masterEnvelope->CalcAutomation(time);
        output = filter->process(output);
        output = saturator->Saturate(output);
        return output;
    }
 
  //  void ProcessNotes(bool& notePressed, int& currentNote, double time)
  //  {
		//notePressed = false;
		//for (int k = 0; k < 16; k++)
		//{
		//	if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe\xbf"[k])) & 0x8000)
		//	{
		//		if (currentNote != k)
		//		{					
  //                  //std::cout << "key down " << k << std::endl;
  //                  oscillatorsWindow.SetNoteFrequency(k);
  //                  envelopesWindow.SetNoteOnTime(time);
		//			currentNote = k;
		//		}

		//		notePressed = true;
		//	}
		//}

		//if (!notePressed)
		//{	
		//	if (currentNote != -1)
		//	{
  //              //std::cout << "note released\n";
  //              envelopesWindow.SetNoteOffTime(time);
		//		currentNote = -1;
		//	}

  //          //oscillatorsWindow.SetNoteFrequency(-1);
		//}
  //  }
};

