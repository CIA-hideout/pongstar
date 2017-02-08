#ifndef _AUDIO_H                // Prevent multiple definitions if this 
#define _AUDIO_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Audio;

#include <iostream>
#include <xact3.h>
#include "constants.h"

#define XACT_CUE IXACT3Cue

class Audio {
	// properties
private:
	IXACT3Engine *xactEngine;   // pointer to XACT sound engine
	IXACT3WaveBank *waveBank;   // pointer to XACT wave bank
	IXACT3SoundBank *soundBank; // pointer to XACT sound bank
	IXACT3Wave *ppWave;         // pointer to XACT wave object
	XACTINDEX cueI;             // XACT sound index
	void *mapWaveBank;          // call UnmapViewOfFile() to release file
	void *soundBankData;
	bool coInitialized;         // set true if coInitialize is successful

public:
	// Constructor
	Audio();

	// Destructor
	virtual ~Audio();

	// member functions

	// Initialize Audio
	HRESULT initialize();

	// Perform periodic sound engine tasks.
	void run();

	// Play sound specified by cue from sound bank.
	// If cue does not exist no error occurs, there is simply no sound played.
	XACT_CUE* playCue(const char cue[]);

	// Stop a playing sound specified by cue from sound bank.
	// If cue does not exist no error occurs.
	void stopCue(const char cue[]);

	// Pause sound specified by category from sound bank.
	// If category does not exist no error occurs.
	void pauseCategory(const char category[]);

	// Resume playback of paused sound specified by category from sound bank.
	// If category does not exist no error occurs.
	void resumeCategory(const char category[]);

	void muteCategory(const char category[]);
	void unmuteCategory(const char category[]);
};

#endif