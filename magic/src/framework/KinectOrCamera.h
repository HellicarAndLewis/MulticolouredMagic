/**
 * KinectOrCamera.h
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */
#include "ofMain.h"
#include "ofxKinect.h"

class KinectOrCamera {
public:
	void setup();
	void update();
	void close();
	
	int width;
	int height;
	
	unsigned char *getPixels();
	unsigned char *getDepthPixels();
private:
	ofVideoGrabber camera;
	unsigned char *greyscaleBuffer;
	ofxKinect kinect;
	bool usingKinect;
};