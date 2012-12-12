#pragma once

#include "ofMain.h"
#ifdef TARGET_OF_IPHONE
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#endif
#include "constants.h"
#include "Centerer.h"
#include "Sampler.h"

class testApp :

#ifdef TARGET_OF_IPHONE
public ofxiPhoneApp
#else 
public ofBaseApp
#endif
{
	
	public:
		void setup();
		void update();
		void draw();
    
        void exit();
    
        void audioOut(float * output, int bufferSize, int nChannels);
	 void audioIn(float * output, int bufferSize, int nChannels);
		
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);



#ifndef TARGET_OF_IPHONE
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
#endif
	
	
        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);

private:
	void setupGraphics();
	void setupOrientation();
	int currOrientation;
	void updateOrientation();
	
	Centerer centerer;
	Sampler sampler;
};

