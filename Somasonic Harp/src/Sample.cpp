/*
 *  Sample.cpp
 *  openFrameworks
 *
 *  Created by Marek Bereza on 17/01/2009.
 *  Copyright 2009 Royal College of Art. All rights reserved.
 *
 */
#ifndef ABS
#define ABS(A) (A>0?A:-A)
#endif

#include "Sample.h"
#include "WavFile.h"
#include "ofMain.h"

Sample::Sample() {
	
	data = NULL;
}

void Sample::loadFromFile(string path) {
	if(data!=NULL) delete [] data;
	WavFile wf;
	if(wf.load((char*)ofToDataPath(path, true).c_str())) {
		
		length = wf.getNumFrames();
		
		if(wf.channels==1) {
			// straight copy
			data = wf.getData();
		} else {
			// copy only the first channel
			float *d = wf.getData();
			data = new float[length];
			for(int i = 0; i < length; i++) {
				data[i] = d[i*wf.channels];
			}
			delete [] d;
			
		}
		printf("Loaded audio file %d samples\n", wf.getNumFrames());
	} else {
		

	}
}
void Sample::load(float* _data, int _length) {

	pos = 0;
	playing = false;
	length = _length;
	volume = 1.f;
#ifdef SHALLOWCOPY
	data = _data;
#else
	if(data!=NULL) delete data;
	data = new float[length];
	for(int i = 0; i < length; i++) {
		data[i] = _data[i];
	}
	
#endif
}

void Sample::trigger(float vel) {
	volume = vel;
	pos = 0;
	playing = true;
}

float Sample::getSample() {
	if(data==NULL) return 0;
	if(playing && pos<length && pos>=0) {
		return volume*data[(int)pos++];
	} else {
		playing = false;
		return 0;
	}

}

float Sample::getSample(float speed) {
	if(data==NULL) return 0;
	if(playing && pos+speed<length && pos>=0) {
		pos += speed;
		return volume*data[(int)pos];
	} else {
		playing = false;
		return 0;
	}
}

void Sample::getSamples(float* out, int _length) {
	if(data==NULL) return;
	int count = 0;
	for(int i = pos; i < _length+pos && i < length; i++) {
		if(i<3) {
			out[(int)(i-pos)] = ((float)(i+1.f)/3.f)*volume*data[i];
		} else if(i+3>length) {
			out[(int)(i-pos)] = ((float)(length - i)/3.f)*volume*data[i];
		} else {
			out[(int)(i-pos)] = volume*data[i];
		}
		count++;
	}
	pos += count;
	// if we've reached the end
	if(pos>=length-1) {
		playing = false;
		for(int i = count; i < _length; i++) {
			out[i] = 0.f;
		}
	}
}

void Sample::normalize(float amount) {
	if(data==NULL) return;
	float max = 0;
	for(int i = 0; i < length; i++) {
		if(ABS(data[i])>max) max = ABS(data[i]);
	}
	
	// don't want a divide by zero or any extra work
	if(max==0 || max==1) {
		return ;
	}
	
	// if max is 1 then gain is 1 regardless of amount
	// if max is 0 then gain is infinity regardless of amount
	// if max is 0.5 and amount is 0.5 then gain should be 0.75
	float newMaxVolume = (1.f - max)*amount;
	// what do we need to multiply max by to make it 1?
	float gain = newMaxVolume/max;
	for(int i = 0; i < length; i++) {
		data[i] *= gain;
	}
	
}
void Sample::addSamples(float* out, int _length) {
	int count = 0;

	for(int i = pos; i < _length+pos && i < length; i++) {
		if(i<3) {
			out[(int)(i-pos)] += ((float)(i+1.f)/3.f)*volume*data[i];
		} else if(i+3>length) {
			out[(int)(i-pos)] += ((float)(length - i)/3.f)*volume*data[i];
		} else {
			out[(int)(i-pos)] += volume*data[i];
		}
		count++;
	}
	pos += count;
}

void Sample::stop() {
	playing = false;
	pos = 0;
}


