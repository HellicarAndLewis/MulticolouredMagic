/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
	int valueToNote(int y);
	
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


