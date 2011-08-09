////////////////////////////////////////////////////////////////////////////////
// Company:    AQIS                                                           //
// Author:     Valeri CHIBAEV (0412 586 556)                                  //
// Purpose:    for non-visual debug (e.g.dll) for sound effects				  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// Beeper.h: interface for the Beeper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEEPER_H__551F999F_3659_44AD_BA3A_E304E88A7CF2__INCLUDED_)
#define AFX_BEEPER_H__551F999F_3659_44AD_BA3A_E304E88A7CF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

enum PresetSound { 
	psOK,
	psError,
	psWelcome,
	psEmergency,
	psWrong,
	psCall,
	psOfficial,
	psDaze,
	psFall,
	psChord,
	psWhisle,
	psHanging,
	psClimb 
};

enum BeatDuration {
	bd_500, 
	bd_1000, 
	bd_1500, 
	bd_2000
};

class Beeper  
{
private:
    bool beeping;
    BeatDuration beatDuration;
    DWORD duration;
    PresetSound defaultSound;

	static Beeper * beeper;

	Beeper()
		: beeping(false), beatDuration(bd_1000), duration(1000), defaultSound(psOK) {}

	~Beeper()
		{}

public:
	static Beeper * GetInstance() { return beeper; }

	void PlayDefaultSound();
	void PlayPresetSound( PresetSound Sound );

	void Beep( DWORD Tone );
	void BeepFor( DWORD Tone, DWORD MSecs );
};

#endif // !defined(AFX_BEEPER_H__551F999F_3659_44AD_BA3A_E304E88A7CF2__INCLUDED_)
