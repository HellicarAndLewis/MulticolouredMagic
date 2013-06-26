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

/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  MiniSampler.h, created by Marek Bereza on 12/12/2012.
 */

#pragma once
#define MAX_SAMPLE_SIZE 441000
#include "ofMain.h"

class MiniSampler {
public:
	
	float *sample;
	int sampleLength;
	bool playing;
	int playhead;
	int maxSampleSize;
	
	MiniSampler() {
		maxSampleSize = 44100;
		sampleLength = 0;
		playing = false;
		playhead = 0;
		sample = new float[maxSampleSize];
	}
	
	~MiniSampler() {
		delete [] sample;
	}
	
	void trigger() {
		playing = true;
		playhead = 0;
	}
	
	bool isPlaying() {
		return playing;
	}
	
	bool isEmpty() {
		return sampleLength==0;
	}
	
	void stop() {
		playing = false;
		playhead = 0;
	}
	void addSamples(float *out, int length, int nChannels) {
		if(!playing) return;


		for(int i = 0; i < length; i++) {
			if(playhead<sampleLength) {
				out[i*2+1] += sample[playhead];
				out[i*2] += sample[playhead];
				
				playhead++;
			} else {
				if(looping) {
					playhead = 0;
				} else {
					playing = false;
				}
			}

		}
	}
	
	void clear() {
		sampleLength = 0;
		playhead = 0;
	}
	
	float getPosition() {
		return (float) playhead / (float) sampleLength;
	}
	void recordSamples(float *in, int length) {
		
		if(length+sampleLength<MAX_SAMPLE_SIZE) {
			
			if(length+sampleLength>=maxSampleSize) {
				// need to make a new sample pointer
				int newMaxSampleSize = length+sampleLength+44100;
				float *f = new float[newMaxSampleSize];
				memcpy(f, sample, sampleLength*sizeof(float));
				delete [] sample;
				sample = f;
				printf("Resizing from %d to %d\n", maxSampleSize, newMaxSampleSize);
				maxSampleSize = newMaxSampleSize;
			
			}
			memcpy(&sample[sampleLength], in, length * sizeof(float));
			sampleLength += length;

		}
		
	}
	static bool looping;
};