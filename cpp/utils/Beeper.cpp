// Beeper.cpp: implementation of the Beeper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Beeper.h"

const DWORD LOW_FREQ   = 40;
const DWORD HIGH_FREQ  = 5000;
	// Denotes a pseudo - frequency for the rests
const DWORD REST = 1;

// I use five octaves with C_0, C, C_1, C_2 and C_3.
// C_1 is the C note written on the first ledger line below the treble clef. 
// That is the C in the middle of a piano keyboard,  where the commercial sign usualle appears
const DWORD C_0 = 65;                 
const DWORD C = 131;               
const DWORD C_1 = 261;                  
const DWORD C_2 = 523;                  
const DWORD C_3 = 1046;
             
const DWORD Cp_0 = 69;                
const DWORD Cp = 138;                
const DWORD Cp_1 = 277;                 
const DWORD Cp_2 = 554;                 
const DWORD Cp_3 = 1109;
             
//Db_0 = Cp_0;              Db = Cp;                 Db_1 = Cp_1;                Db_2 = Cp_2;                Db_3 = Cp_3;
 
const DWORD D_0 = 73;                 
const DWORD D = 149;               
const DWORD D_1 = 293;                  
const DWORD D_2 = 587;                  
const DWORD D_3 = 1174;
             
const DWORD Dp_0 =78 ;                
const DWORD Dp = 155;                
const DWORD Dp_1 = 311;                 
const DWORD Dp_2 = 622;                 
const DWORD Dp_3 = 1244;
             
//Eb_0 = Dp_0;              Eb = Dp;                 Eb_1 = Dp_1;                Eb_2 = Dp_2;                Eb_3 = Dp_3;
 
const DWORD E_0 = 82;                 
const DWORD E = 165;               
const DWORD E_1 = 329;                  
const DWORD E_2 = 659;                  
const DWORD E_3 = 1318;
 
const DWORD F_0 = 87;                 
const DWORD F = 174;               
const DWORD F_1 = 349;                  
const DWORD F_2 = 698;                  
const DWORD F_3 = 1397;
             
const DWORD Fp_0 = 92;                
const DWORD Fp = 189;                
const DWORD Fp_1 = 370;                 
const DWORD Fp_2 = 740;                 
const DWORD Fp_3 = 1480;
             
//Gb_0 = Fp_0;              Gb = Fp;                 Gb_1 = Fp_1;                Gb_2 = Fp_2;                Gb_3 = Fp_3;
 
const DWORD G_0 = 98;                 
const DWORD G = 196;               
const DWORD G_1 = 392;                  
const DWORD G_2 = 784;                  
const DWORD G_3 = 1568;
             
const DWORD Gp_0 = 104;               
const DWORD Gp = 207;                
const DWORD Gp_1 = 415;                 
const DWORD Gp_2 = 830;                 
const DWORD Gp_3 = 1661;
             
//Ab_0 = Fp_0;              Ab = Gp;                 Ab_1 = Gp_1;                Ab_2 = Gp_2;                Ab_3 = Gp_3;
 
const DWORD A_0 = 110;                
const DWORD A = 220;               
const DWORD A_1 = 440;                  
const DWORD A_2 = 880;                  
const DWORD A_3 = 1760;
             
const DWORD Ap_0 = 116;               
const DWORD Ap = 233;                
const DWORD Ap_1 = 466;                 
const DWORD Ap_2 = 932;                 
const DWORD Ap_3 = 1864;
             
//Bb_0 = Ap_0;              Bb = Ap;                 Bb_1 = Ap_1;                Bb_2 = Ap_2;                Bb_3 = Ap_3;
 
const DWORD B_0 = 123;                
const DWORD B = 247;               
const DWORD B_1 = 494;                  
const DWORD B_2 = 988;                  
const DWORD B_3 = 1975;

const int aFreqs[61] = {  
	65,    69,    73,     78,    82,     87,    92,    98,    104,   110,   116,    123,
    131,   138,   149,    155,   165,    174,   189,   196,    207,   220,   233,    247,
    261,   277,   293,    311,   329,    349,   370,   392,    415,   440,   466,    494,
    523,   554,   587,    622,   659,    698,   740,   784,    830,   880,   932,    988,
    1046,  1109,  1174,   1244,  1318,   1397,  1480,   1568,   1661,  1760,  1864,  1975,
    1
};

const char * Tones[61] = {
	"C_0", "Cp_0", "D_0", "Dp_0", "E_0", "F_0", "Fp_0", "G_0", "Gp_0", "A_0", "Ap_0", "B_0",
    "C",   "Cp",   "D",   "Dp",   "E",   "F",   "Fp",   "G",   "Gp",   "A",   "Ap",   "B",
    "C_1", "Cp_1", "D_1", "Dp_1", "E_1", "F_1", "Fp_1", "G_1", "Gp_1", "A_1", "Ap_1", "B_1",
    "C_2", "Cp_2", "D_2", "Dp_2", "E_2", "F_2", "Fp_2", "G_2", "Gp_2", "A_2", "Ap_2", "B_2",
    "C_3", "Cp_3", "D_3", "Dp_3", "E_3", "F_3", "Fp_3", "G_3", "Gp_3", "A_3", "Ap_3", "B_3",
    "REST"
};

const char * THE_END = "FINE";

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

Beeper * Beeper::beeper = new Beeper();

void Beeper::PlayDefaultSound()
{
   PlayPresetSound( defaultSound );
}

void Beeper::PlayPresetSound( PresetSound Sound )
{

  if (beeping)
	  return;

  beeping = true;

  switch (Sound)
  {
    case psOK:
		{
           BeepFor (Ap_2,100);
           BeepFor (B_2, 100);
           BeepFor (C_3, 100);
		   break;
		}
    case psError:
         {
           BeepFor (Fp_0,150);
           BeepFor (REST,200);
           BeepFor (C_0,500);
		   break;
         }
    case psWelcome:
         {
           BeepFor (Ap_2,100);
           BeepFor (B_2, 100);
           BeepFor (C_3, 100);
           BeepFor (REST,100);
           BeepFor (C_3, 100);
           BeepFor (B_2, 100);
           BeepFor (Ap_2,100);
		   break;
         }
    case psEmergency:
         {
           BeepFor (F_2,200);
           BeepFor (B_1, 200);
           BeepFor (F_2,200);
           BeepFor (B_1, 200);
           BeepFor (F_2,200);
           BeepFor (B_1, 200);
           BeepFor (F_2,200);
           BeepFor (B_1, 200);
		   break;
         }
    case psWrong:
         {
           BeepFor (C_1,150);
           BeepFor (B,50);
           BeepFor (Ap,50);
           BeepFor (A,50);
           BeepFor (Gp,50);
           BeepFor (G,50);
           BeepFor (Fp,50);
           BeepFor (F,50);
           BeepFor (E,50);
           BeepFor (Dp,50);
           BeepFor (D,50);
           BeepFor (Cp,50);
           BeepFor (C,100);
           BeepFor (C_0,200);
		   break;
         }
    case psCall:
         {
           BeepFor (G,650);
           BeepFor (REST,100);
           BeepFor (E,500);
		   break;
         }
    case psOfficial:
         {
           BeepFor (G,200);
           BeepFor (REST,50);
           BeepFor (G,200);
           BeepFor (REST,50);
           BeepFor (G,200);
           BeepFor (REST,50);
           BeepFor (E,700);
           BeepFor (REST,100);
           BeepFor (C_1,200);
           BeepFor (REST,50);
           BeepFor (C_1,200);
           BeepFor (REST,50);
           BeepFor (C_1,200);
           BeepFor (REST,50);
           BeepFor (C,700);
		   break;
         }
    case psDaze:
		 { 
           BeepFor (E_1,100);
           BeepFor (Dp_1,100);
           BeepFor (D_1,100);
           BeepFor (Dp_1,100);
           BeepFor (E_1,100);
           BeepFor (Dp_1,100);
           BeepFor (D_1,100);
           BeepFor (Dp_1,100);
           BeepFor (E_1,100);
           BeepFor (Dp_1,100);
           BeepFor (D_1,100);
           BeepFor (Dp_1,100);
		   break;
         }
    case psFall:
         {
           BeepFor (E_1,100);
           BeepFor (Dp_1,100);
           BeepFor (D_1,100);
           BeepFor (Dp_1,100);

           BeepFor (F_1,100);
           BeepFor (E_1,100);
           BeepFor (Dp_1,100);
           BeepFor (E_1,100);

           BeepFor (Fp_1,100);
           BeepFor (F_1,100);
           BeepFor (E_1,100);
           BeepFor (F_1,100);
		   break;
         }
    case psChord:
         {
           BeepFor (B_1,80);
           BeepFor (Ap_1,80);
           BeepFor (A_1,80);
           BeepFor (Gp_1,80);
           BeepFor (G_1,80);
           BeepFor (Fp_1,80);
           BeepFor (F_1,80);
           BeepFor (E_1,80);
           BeepFor (Dp_1,80);
           BeepFor (D_1,80);
           BeepFor (Cp_1,80);
           BeepFor (C_1,80);
		   break;
         }
    case psWhisle:
         {
           BeepFor (C_2,80);
           BeepFor (F_2,80);
           BeepFor (G_2,80);
           BeepFor (C_3,80);
		   break;
         }
    case psHanging:
		{
           BeepFor (G_2,80);
           BeepFor (C_3,80);
           BeepFor (Gp_2,80);
           BeepFor (Cp_3,80);
           BeepFor (A_2,80);
           BeepFor (D_3,80);
           BeepFor (Ap_2,80);
           BeepFor (Dp_3,80);
           BeepFor (B_2,80);
           BeepFor (E_3,80);
           BeepFor (C_3,80);
           BeepFor (F_3,80);
		   break;
         }
    case psClimb:
         {
           BeepFor (C_1,80);
           BeepFor (Cp_1,80);
           BeepFor (D_1,80);
           BeepFor (Dp_1,80);
           BeepFor (E_1,80);
           BeepFor (F_1,80);
           BeepFor (Fp_1,80);
           BeepFor (G_1,80);
           BeepFor (Gp_1,80);
           BeepFor (A_1,80);
           BeepFor (Ap_1,80);
           BeepFor (B_1,80);
		   break;
         }
	default: break;
  }

  beeping = false;

}

void Beeper::Beep( DWORD Tone )
{
  BeepFor(Tone, duration);
}

DWORD ElapsedMillisecFrom( DWORD StartMillisec )
{
	const int Magic = 0x80000000;
	DWORD CurMS = GetTickCount();
	if ( CurMS >= StartMillisec )
		return CurMS - StartMillisec;
	return (CurMS + Magic) - (StartMillisec - Magic);
}

void Beeper::BeepFor( DWORD Tone, DWORD MSecs )
{
	DWORD StartTime;

	if ( Tone == REST )
	{
		StartTime = GetTickCount();
		while ( ElapsedMillisecFrom(StartTime) < MSecs )
			;
		return;
	}

	//if ( IsWin_NT )
		::Beep(Tone, MSecs);
	//else {
	//	StartBeep(Tone);
	//	StartTime:=GetTickCount;
	//	while ElapsedMillisecFrom(StartTime) < MSecs do ;
	//	StopBeep;
	//}

}
