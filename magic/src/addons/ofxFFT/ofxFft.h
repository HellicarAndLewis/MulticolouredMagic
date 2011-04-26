#pragma once

// If FFTW is unavailable, comment out the following line.
	//#define USE_FFTW

#include "ofMain.h"

enum fftWindowType {
	OF_FFT_WINDOW_RECTANGULAR,
	OF_FFT_WINDOW_BARTLETT,
	OF_FFT_WINDOW_HANN,
	OF_FFT_WINDOW_HAMMING,
	OF_FFT_WINDOW_SINE};

enum fftImplementation {
	OF_FFT_BASIC,
	OF_FFT_FFTW};

class ofxFft : public ofBaseDraws {
public:
	// create and destroy fft
	static ofxFft* create(
		int signalSize = 512,
		fftWindowType windowType = OF_FFT_WINDOW_HAMMING,
		fftImplementation implementation = OF_FFT_BASIC);
	virtual ~ofxFft();

	void setSignal(float* signal);
	void setCartesian(float* real, float* imag = NULL);
	void setPolar(float* amplitude, float* phase = NULL);

	int getSignalSize();
	float* getSignal();
	void clampSignal();

	int getBinSize();
	float* getReal();
	float* getImaginary();
	float* getAmplitude();
	float* getPhase();

	// ofBaseDraws
	void draw(float x, float y);
	void draw(float x, float y, float width, float height);
	float getWidth();
	float getHeight();

protected:
	virtual void setup(int signalSize, fftWindowType windowType);
	virtual void executeFft() = 0;
	virtual void executeIfft() = 0;

	void clear();

	// time domain data and methods
	fftWindowType windowType;
	float windowSum;
	float *window, *inverseWindow;

	void setWindowType(fftWindowType windowType);

	inline void runWindow(float* signal) {
		if(windowType != OF_FFT_WINDOW_RECTANGULAR)
			for(int i = 0; i < signalSize; i++)
				signal[i] *= window[i];
	}

	inline void runInverseWindow(float* signal) {
		if(windowType != OF_FFT_WINDOW_RECTANGULAR)
			for(int i = 0; i < signalSize; i++)
				signal[i] *= inverseWindow[i];
	}

	float *signal;
	bool signalUpdated, signalNormalized;
	void prepareSignal();
	void updateSignal();
	void normalizeSignal();
	void copySignal(float* signal);

	// frequency domain data and methods
	int signalSize, binSize;

	float *real, *imag;
	bool cartesianUpdated, cartesianNormalized;
	void prepareCartesian();
	void updateCartesian();
	void normalizeCartesian();
	void copyReal(float* real);
	void copyImaginary(float* imag);

	float *amplitude, *phase;
	bool polarUpdated, polarNormalized;
	void preparePolar();
	void updatePolar();
	void normalizePolar();
	void copyAmplitude(float* amplitude);
	void copyPhase(float* phase);

	void clearUpdates();

	inline float cartesianToAmplitude(float x, float y) {
		return sqrtf(x * x + y * y);
	}

	inline float cartesianToPhase(float x, float y) {
		return atan2f(y, x);
	}
};
