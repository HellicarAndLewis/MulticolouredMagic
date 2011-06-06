/*
 TuioKinect - A simple TUIO hand tracker for the Kinect 
 Copyright (c) 2010 Martin Kaltenbrunner <martin@tuio.org>
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _TUIO_KINECT
#define _TUIO_KINECT

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxCvKalman.h"
#include "TuioServer.h"
#include "KinectOrCamera.h"

using namespace TUIO;

class TuioKinect {

public:

	void setup();
	void update(bool sendTuio);
	void exit();

	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	KinectOrCamera kinect;

	ofxCvGrayscaleImage	grayImage;
	ofxCvGrayscaleImage	depthImage;
	ofxCvGrayscaleImage mixImage;
	ofxCvGrayscaleImage bgImage;

	ofxCvColorImage		colorImage;
	
	ofxCvContourFinder 	contourFinder;
	TuioServer *tuioServer;


	int threshold;
	bool flipX, flipY;
	float blendAmount;
	int farClip;
private:
	void updateTuio();
};

#endif
