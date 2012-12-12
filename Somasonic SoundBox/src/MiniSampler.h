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