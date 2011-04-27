/*
 *  ExampleApp.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"

//#include "ofxFft.h"

class CircleBiggerApp: public Reactickle {
	
	void start(){
		ofSetCircleResolution(64);
	}
	
	void setup(){
		smoothedVolume = 0.f;
		
		bands.resize(1);
		
		//fftBufferSize = 512;
		
		//fft = ofxFft::create(fftBufferSize, OF_FFT_WINDOW_BARTLETT);
			// To use with FFTW, try:
			// fft = ofxFft::create(fftBufferSize, OF_FFT_WINDOW_BARTLETT, OF_FFT_FFTW);
		
		//audioInput = new float[fftBufferSize];
		//fftOutput = new float[fft->getBinSize()];
		//eqFunction = new float[fft->getBinSize()];
		//eqOutput = new float[fft->getBinSize()];
		//ifftOutput = new float[fftBufferSize];
		
			// 0 output channels,
			// 1 input channel
			// 44100 samples per second
			// [bins] samples per buffer
			// 4 num buffers (latency)
		
			// this describes a linear low pass filter
		//for(int i = 0; i < fft->getBinSize(); i++)
		//	eqFunction[i] = (float) (fft->getBinSize() - i) / (float) fft->getBinSize();
		
			//ofSoundStreamSetup(0, 1, this, 44100, fftBufferSize, 4); // already done
		
			//a bit of amping
		
		amplification = 1.f; //nothing to start with....
		
		//gui->saveToXML();
		//gui->addPage("CircleGetsBigger");
		//gui->addSlider("Amplification", amplification, 1.f, 30.f);
		//gui->loadFromXML();
	}
	

	void update(){
			// smooth volume
		if(volume > smoothedVolume) smoothedVolume = volume;
		else smoothedVolume *= 0.97f;
		
		int numberOfBands = bands.size();
		//int widthOfBand = fft->getBinSize()/numberOfBands;
		int currentBin = 0;
		/*
		for(int i = 0; i < numberOfBands; i++){
			float tempValue;
			
			tempValue = 0.f;
			
			for(int j = 0; j < widthOfBand; j++){
				tempValue += fftOutput[currentBin];
				currentBin++;
			}
			
			tempValue = tempValue/widthOfBand;
			
			tempValue *= amplification;
			
			if(tempValue > bands[i]){
				bands[i] = tempValue;
			}else{
				bands[i] *= 0.97f;
			}
		}
		*/
			//normalise to get the result.....
		
//		float maxValue = 0.f;
//		
//		for(int i = 0; i < numberOfBands; i++){
//			if(bands[i] > maxValue){
//				maxValue = bands[i];
//			}
//		}
//		
//		for(int i = 0; i < numberOfBands; i++){
//			bands[i] = maxValue/bands[i];
//		}		
	}
	
	void audioReceived(float* input, int bufferSize, int nChannels){
		
		/*
		 // store input in audioInput buffer
		memcpy(audioInput, input, sizeof(float) * bufferSize);
		
		fft->setSignal(audioInput);
		memcpy(fftOutput, fft->getAmplitude(), sizeof(float) * fft->getBinSize());
		
		for(int i = 0; i < fft->getBinSize(); i++)
			eqOutput[i] = fftOutput[i] * eqFunction[i];
		
		fft->setPolar(eqOutput, fft->getPhase());
		
		fft->clampSignal();
		memcpy(ifftOutput, fft->getSignal(), sizeof(float) * fft->getSignalSize());	
		 */
	}
	
	void draw() {
		ofSetColor(255, 0, 0);
		
			//ofCircle(ofGetWidth()/2.f, ofGetHeight()/2.f, smoothedVolume * ofGetHeight());
		
		int numberOfBands = bands.size();
		float maximumDiameter = ofGetWidth()/numberOfBands;
		float maximumRadius = maximumDiameter/2.f;
		
		for(int i = 0; i < numberOfBands; i++){
			ofCircle((maximumDiameter*i)+maximumRadius, ofGetHeight()/2.f, bands[i] * maximumRadius);
			//ofRect(maximumDiameter*i, ofGetHeight()-ofGetHeight()*bands[i], maximumDiameter, ofGetHeight()*bands[i]);
		}
	}
	
	void keyPressed(int key){
		switch (key) {
			case OF_KEY_UP:
				bands.resize(bands.size()+1);
				break;
			case OF_KEY_DOWN:
				if(bands.size() > 1){
					bands.resize(bands.size()-1);
				}
				break;
		}		
	}
	
	float smoothedVolume;
	
	int fftBufferSize;
	
	//ofxFft* fft;
	
	float* audioInput;
	//float* fftOutput;
	float* eqFunction;
	float* eqOutput;
	//float* ifftOutput;
	
	vector <float> bands;
	
	float amplification;
};