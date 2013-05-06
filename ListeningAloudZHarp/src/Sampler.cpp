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

#include "Sampler.h"
#include "stdio.h"
#ifdef TARGET_OF_IPHONE
#include "ofxAccelerometer.h"
#endif


//pthread_mutex_t         controlMutex = PTHREAD_MUTEX_INITIALIZER;
Poco::Mutex controlMutex;


#define PENTATONIC "pentatonic"
#define MAJOR "major"
#define MINOR "minor"
#define CHROMATIC "chromatic"

ofImage Particle::particle;


ofColor Particle::color;

int noteOffset = 0;
//--------------------------------------------------------------
void Sampler::init(){
	
	currTouchId = -1;
	//AppSettings::addListener(this);
	movementThreshold = 0.02;
	//Particle::color = &AppSettings::color3;

	recordBufferSize = SAMPLERATE*MAX_RECORD_SECONDS;
	recordBuffer = new float[recordBufferSize];
	recordPos = 0;
	recording = false;
	inputLevel = 0;
	playbackSpeed = 1;
	lastSound = -1;


	ofDirectory DIR;

	int numFiles = DIR.listDir("sounds");
	for(int i = 0; i < numFiles; i++) {
		sounds.push_back(DIR.getName(i));
	}


	// this is the last time that there was a note
	noteLastTime = -10;
	lastNote = 0;


	scales.push_back(PENTATONIC);
	scales.push_back(MAJOR);
	scales.push_back(MINOR);
	scales.push_back(CHROMATIC);


	memset(recordBuffer, 0, recordBufferSize*sizeof(float));
	// 1 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 1 num buffers (latency)


 
	controlMutex.lock();
	sample.loadFromFile(ofToDataPath("sounds/harp.wav"));
	controlMutex.unlock();


	//--------- PANEL 1

	video.listDevices();
	#ifdef TARGET_OF_IPHONE
	video.setDeviceID(1);
	#endif
	video.initGrabber(VISION_WIDTH, VISION_HEIGHT, OF_PIXELS_BGRA);
	vision.setup();
	gui.setup();
	
	gui.recordButton->recListener = this;
}


bool wasRecording = false;

int lastMaxLevel = -1;
void Sampler::update() {

	if(!wasRecording && gui.recording) {
		// recording just started.
		//ofSoundStreamStop();
		//ofSoundStreamSetup(0, 1, ofGetAppPtr(), 44100, 512, 4);

	}
	
	wasRecording = gui.recording;
	if(gui.input==INPUT_ACCELEROMETER) {
		#ifdef TARGET_OF_IPHONE
		ofPoint a = ofxAccelerometer.getOrientation();
		float ax = a.x;// + a.y;
	//	printf("%f\n", ax);
		float pitch = ofMap(ax, -45, 45, 1, 0);
		float vol = 0.8;
		if(gui.useYAxisAsVolume) {
			vol = ofMap(a.y, -45, 45, 1, 0);
		}
		
		if(ax<-45) pitch = 1;
		else if(ax>45) {
			pitch = 0;
//			pitch = ofMap(ax, 45, 135, 0, 1, true);
		}
		int currNote = pitch*vision.levels.size();
		if(currNote!=lastNote) {
			
			playSound(vol, pitch);
		}
		#endif
	}
	ofBackground(0,0,0);
	vision.numLevels = gui.noteRange;
	vision.video = &video;
	// the vision code works out how much average change there is in each of
	// either vertical or horizontal strips across the screen.
	// this bit of code finds out if the strip with the most change
	// is a different strip from the last strip, and then triggers that note.
	float max = 0;
	int currMaxLevel = -1;
	for(int i = 0; i < vision.levels.size(); i++) {

		if(max<vision.levels[i].second) {
			max = vision.levels[i].second;
			currMaxLevel = i;
		}
	}

	if(lastMaxLevel!=currMaxLevel) {
		//printf("Playing note %d %f\n", currMaxLevel, max);
		float volume = ofMap(max, 0, 0.5, 0, 1);
		if(volume>1) volume = 1;
		if(volume>movementThreshold) { // some threshold
			lastMaxLevel = currMaxLevel;
			if(gui.input==INPUT_CAMERA) playSound(volume, 1.f - (float)currMaxLevel/vision.levels.size());
		} else {
			currMaxLevel = -1;
		}
	}

	lastMaxLevel = currMaxLevel;



	vision.update();
	
	
	if(gui.mustLoadSound) {
		controlMutex.lock();
		sample.loadFromFile(gui.soundFile);

		controlMutex.unlock();
		gui.mustLoadSound = false;
		noteOffset = 0;
	}
	
	
	/*for(int i = 0; i < particles.size(); i++) {
		particles[i].update();
		if(!particles[i].alive) {
			particles.erase(particles.begin()+i);
			i--;
		}
	}*/
}
void Sampler::recordingStarted() {
	printf("Record start\n");
	controlMutex.lock();
	recording = true;
	recordPos = 0;
	controlMutex.unlock();
}
void Sampler::recordingEnded() {
	printf("Record end\n");
	controlMutex.lock();
	recording = false;
	sample.load(recordBuffer, recordPos);
	printf("Loaded sample of %d length\n", recordPos);
	controlMutex.unlock();
	noteOffset = -12;
}
//--------------------------------------------------------------
void Sampler::draw(){
	
	ofSetHexColor(0xFFFFFF);
	
	if(gui.showCamera) {
		vision.draw();
	}
	
	
	// fade out a note
	if(ofGetElapsedTimef() - noteLastTime < 1.5f) {
		float alpha = 0.5*ofMap(ofGetElapsedTimef() - noteLastTime, 0, 1.5, 255, 0);

		ofSetColor(255, 0, 0, alpha);
		float width = (float) ofGetWidth()/vision.levels.size();
		
		ofRect(ofGetWidth() - width*(lastNote+1), 0, width, ofGetHeight());
	}




	ofSetHexColor(0xFFFFFF);

//	for(int i = 0; i < particles.size(); i++) {
//		particles[i].draw();
//	}
	
	if(gui.showGridLines) {
		glColor4f(1,1,1,0.4);
		for(int i = 0; i <vision.levels.size(); i++) {
			float x = ofMap(i, 0, vision.levels.size(), 0, ofGetWidth());
			ofLine(x, 0, x, ofGetHeight());
		}
	}
	//gui.draw();
}






void Sampler::audioRequested (float * output, int bufferSize, int nChannels) {
	controlMutex.lock();
	// if we're recording, we want silence!!
	if(recording) {
		memset(output, 0, bufferSize*nChannels*sizeof(float));
	} else {
	//	printf("Sound %f\n", playbackSpeed);
		// otherwise, maybe we want playback
		for(int i = 0; i < bufferSize; i++) {
			float s = sample.getSample(playbackSpeed);
			for(int channel = 0; channel < nChannels; channel++) {
				output[i*nChannels + channel] = s;
			}
		}
	}
	controlMutex.unlock();
}
//--------------------------------------------------------------
void Sampler::audioReceived 	(float * input, int bufferSize, int nChannels){

	//if(recording) printf("We're recording\n");
	//else printf("Not record\n");
	controlMutex.lock();
	for(int i = 0; i < bufferSize; i++) {

		float inp = input[i*nChannels];

		// do the recording
		if(recording && recordPos<recordBufferSize) {
			recordBuffer[recordPos++] = inp;
		}
		// do a level meter
		if(inputLevel<inp) {
			inputLevel = inp;
		} else {
			inputLevel *= 0.99995;
		}
	}
	controlMutex.unlock();

}


//--------------------------------------------------------------
void Sampler::mouseMoved(int x, int y ) {
}


//--------------------------------------------------------------
void Sampler::mousePressed(int x, int y, int button){
	if(gui.input==INPUT_TOUCH && !gui.gui.isEnabled()) {
		float pitch = ofMap(x, 0, ofGetWidth(), 1, 0);
		currTouchId = button;
		float vol = 0.8;
		if(gui.useYAxisAsVolume) {
			vol = ofMap(y, ofGetHeight(), 0, 0.0, 1, true);
		}
		playSound(vol, pitch);
	}
	/*int note = valueToNote(1.f-((float)y/ofGetHeight()));
	 playbackSpeed = noteToSpeed(note);
	 sample.trigger(1);
	 */
}
//--------------------------------------------------------------
void Sampler::mouseDragged(int x, int y, int button){
	if(gui.input==INPUT_TOUCH && !gui.gui.isEnabled()) {
		float pitch = ofMap(x, 0, ofGetWidth(), 1, 0);
		int currNote = pitch*vision.levels.size();
		
		if(currTouchId==-1) currTouchId = button;
		
		if(currNote!=lastNote && currTouchId==button) {
			float vol = 0.6;
			if(gui.useYAxisAsVolume) {
				vol = ofMap(y, ofGetHeight(), 0, 0.0, 1, true);
			}
			playSound(vol, pitch);
		}
	}

}
//--------------------------------------------------------------
void Sampler::mouseReleased(int x, int y, int button){
	// let the program know the currTouchId is up for grabs.
	if(button==currTouchId) {
		currTouchId = -1;
	}
}

void Sampler::playSound(float volume, float pitch) {
    
	volume = volume * volume;
	int note = valueToNote(pitch);
	if(vision.levels.size()>5) {
		note += noteOffset;
	}
	playbackSpeed = noteToSpeed(note);
	sample.trigger(volume);
	noteLastTime = ofGetElapsedTimef();
	lastNote = pitch*vision.levels.size();
    
    
}

void Sampler::triggerSound(float volume) {
    
	volume = volume * volume;
	
	playbackSpeed = 1.f;;
	sample.trigger(volume);
	noteLastTime = ofGetElapsedTimef();
	//lastNote = pitch*vision.levels.size();
    
    
}

void Sampler::spawnParticle(ofPoint pos, float volume) {
	int star = 3;
	for(int i = 0; i < star; i++) {
		float angle = (float)i/star;
		angle *= 2*PI;
		particles.push_back(Particle(pos.x*ofGetWidth(), pos.y*ofGetHeight(), volume, angle));
	}
}






float Sampler::noteToSpeed(int note) {
	return pow(2, (float)note/12.f);
}

int Sampler::valueToNote(float value) {
	int scale = gui.scale;
	int notesInScale = 5;
	if(scales[scale]==PENTATONIC) {
		notesInScale = 5;
	} else if(scales[scale]==MAJOR) {
		notesInScale = 7;
	} else if(scales[scale]==MINOR) {
		notesInScale = 7;
	} else if(scales[scale]==CHROMATIC) {
		notesInScale = 12;
	}
	int maxOctaves = 2;

	// how many octaves we want
	/*value *= maxOctaves;

	// how many notes in the scale
	value *= notesInScale;
*/

	value *= gui.noteRange;
		// this is the position in the scale
	int noteInScale = floor(value);

	// this is the chromatic position
	int noteNum = 0;

	// work out the octave offset
	noteNum = floor(noteInScale/notesInScale)*12;

	// add the note offset



	if(scales[scale]==PENTATONIC) {
		switch(noteInScale%notesInScale) {
			case 0: noteNum += 0;  break;
			case 1: noteNum += 3;  break;
			case 2: noteNum += 5;  break;
			case 3: noteNum += 7;  break;
			case 4: noteNum += 10; break;
		}
	} else if(scales[scale]==MAJOR) {
		switch(noteInScale%notesInScale) {
			case 0: noteNum += 0;  break;
			case 1: noteNum += 2;  break;
			case 2: noteNum += 4;  break;
			case 3: noteNum += 5;  break;
			case 4: noteNum += 7; break;
			case 5: noteNum += 9;  break;
			case 6: noteNum += 11;  break;

		}
	} else if(scales[scale]==MINOR) {
		switch(noteInScale%notesInScale) {
			case 0: noteNum += 0;  break;
			case 1: noteNum += 2;  break;
			case 2: noteNum += 3;  break;
			case 3: noteNum += 5;  break;
			case 4: noteNum += 7;  break;
			case 5: noteNum += 8;  break;
			case 6: noteNum += 11; break;
		}
	} else if(scales[scale]==CHROMATIC) {
		noteNum += noteInScale%notesInScale;
	}


	return noteNum + 4 + gui.key; // set the pitch here

}


void Sampler::soundChanged() {

	controlMutex.lock();
	string sndUrl = "";//AppSettings::soundFile;
	if(sndUrl=="") {
		sndUrl = ofToDataPath("sounds/harp.wav");
	}
	sample.loadFromFile(sndUrl);
	controlMutex.unlock();
}