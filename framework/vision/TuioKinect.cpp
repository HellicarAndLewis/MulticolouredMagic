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


#include "TuioKinect.h"

ofxCvKalman *tuioPointSmoothed[32];
#include "TuioPoint.h"

using namespace TUIO;
TuioPoint updateKalman(int id, TuioPoint tp) {
	if (id>=16) return NULL;
	if(tuioPointSmoothed[id*2] == NULL) {
		tuioPointSmoothed[id*2] = new ofxCvKalman(tp.getX());
		tuioPointSmoothed[id*2+1] = new ofxCvKalman(tp.getY());
	} else {
		tp.update(tuioPointSmoothed[id*2]->correct(tp.getX()),tuioPointSmoothed[id*2+1]->correct(tp.getY()));
	}

	return tp;
}

void clearKalman(int id) {
	if (id>=16) return;
	if(tuioPointSmoothed[id*2]) {
		delete tuioPointSmoothed[id*2];
		tuioPointSmoothed[id*2] = NULL;
		delete tuioPointSmoothed[id*2+1];
		tuioPointSmoothed[id*2+1] = NULL;
	}
}


//--------------------------------------------------------------
void TuioKinect::setup() {

	kinect.setup();

	depthImage.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	colorImage.allocate(kinect.width, kinect.height);
	bgImage.allocate(kinect.width, kinect.height);
	mixImage.allocate(kinect.width, kinect.height);

	//threshold = 60;
	flipX = true;
	flipY = false;
	blendAmount = 0.1;

	TuioTime::initSession();
	tuioServer = new TUIO::TuioServer();
	tuioServer->setVerbose(false);
//	tuioServer->setSourceName("TuioKinect");
//	tuioServer->enableObjectProfile(false);
//	tuioServer->enableBlobProfile(false);

	for (int i=0;i<32;i++)
		tuioPointSmoothed[i] = NULL;
}

//--------------------------------------------------------------
void TuioKinect::update(bool sendTuio) {

	kinect.update();

	unsigned char *colorPix = kinect.getPixels();
	unsigned char *depthPix = kinect.getDepthPixels();

	if(colorPix) { // only load if not null
		colorImage.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
	}

	if(depthPix) { // only load if not null

		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
	}

	// flip the image accordingly - mirror does nothing if both are false
	grayImage.mirror(flipY, flipX);

	// block out any images that are further away than a certain distance (farClip)
	cvMaxS(grayImage.getCvImage(), farClip, grayImage.getCvImage());

	// do we need a flagImageChanged() here?

	// blend the current frame with the background
	mixImage = grayImage;
	mixImage.convertToRange(0, 255*blendAmount);
	bgImage.convertToRange(0, 255*(1.f - blendAmount));
	bgImage += mixImage;





	// do we need this line?
	grayImage.flagImageChanged();

	// subtract the main image from the background
	grayImage.absDiff(bgImage);

	// how about this line? Do we need it too?
	grayImage.flagImageChanged();

	// threshold it with our threshold value
	grayImage.threshold(threshold);

	contourFinder.findContours(grayImage, 900, (kinect.width*kinect.height)/8, 20, false);


	// only send tuio if it's required.
	if(sendTuio) {
		updateTuio();
	}
}

void TuioKinect::updateTuio() {
	TuioTime frameTime = TuioTime::getSessionTime();
	tuioServer->initFrame(frameTime);

	std::vector<ofxCvBlob>::iterator blob;
//	printf("Blobs: %d\n", contourFinder.blobs.size());
	for (blob=contourFinder.blobs.begin(); blob!= contourFinder.blobs.end(); blob++) {
		float xpos = (*blob).centroid.x;
		float ypos = (*blob).centroid.y;

		TuioPoint tp(xpos/kinect.width,ypos/kinect.height);

		//if ((tp.getY() > 0.8) && (tp.getX()>0.25) && (tp.getX()<0.75)) continue;

		TuioCursor *tcur = tuioServer->getClosestTuioCursor(tp.getX(),tp.getY());
		if ((tcur==NULL) || (tcur->getDistance(&tp)>0.2)) {
			tcur = tuioServer->addTuioCursor(tp.getX(), tp.getY());
			updateKalman(tcur->getCursorID(),tcur);

		} else {
			TuioPoint kp = updateKalman(tcur->getCursorID(),tp);
			tuioServer->updateTuioCursor(tcur, kp.getX(), kp.getY());

		}
	}

	tuioServer->stopUntouchedMovingCursors();

	std::list<TuioCursor*> dead_cursor_list = tuioServer->getUntouchedCursors();
	std::list<TuioCursor*>::iterator dead_cursor;
	for (dead_cursor=dead_cursor_list.begin(); dead_cursor!= dead_cursor_list.end(); dead_cursor++) {
		clearKalman((*dead_cursor)->getCursorID());

	}

	tuioServer->removeUntouchedStoppedCursors();
	tuioServer->commitFrame();
}


//--------------------------------------------------------------
void TuioKinect::exit(){
	kinect.close();
}

//--------------------------------------------------------------
void TuioKinect::mouseMoved(int x, int y)
{}

//--------------------------------------------------------------
void TuioKinect::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void TuioKinect::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void TuioKinect::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void TuioKinect::windowResized(int w, int h)
{}

