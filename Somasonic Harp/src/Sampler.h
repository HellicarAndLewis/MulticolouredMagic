#pragma once


#include "ofMain.h"
#include "Sample.h"
#include "Vision.h"

#define MAX_RECORD_SECONDS 10
#define SAMPLERATE 44100
#include "Particle.h"
#include "SamplerGui.h"



class Sampler: public RecordButtonListener {
	
public:
	
	void recordingStarted();
	void recordingEnded();
	void init();
	void update();
	void draw();

	void soundChanged();

	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void audioRequested (float * output, int bufferSize, int nChannels); 		
	void audioReceived 	(float * input, int bufferSize, int nChannels);
	
	ofVideoGrabber video;
	Sample sample;
	float *recordBuffer;
	int recordBufferSize;
	int recordPos;
	
	bool recording;
	
	float playbackSpeed;
	
	// how loud the microphone is.
	float inputLevel;
	
	// give this function a normalized
	// value, and it gives back a note number
	int valueToNote(float y);
	
	// converts a note number to sample playback speed
	float noteToSpeed(int note);
	
	// both volume and pitch go from 0 to 1
	void playSound(float volume, float pitch);

	
	void spawnParticle(ofPoint pos, float volume);
	vector<Particle> particles;
	// takes care of all the vision
	Vision vision;
	
	float noteLastTime;
	int lastNote;
	vector<string> sounds;
	vector<string> scales;
	int lastSound;
	float movementThreshold;
	SamplerGui gui;
	int currTouchId;
};


