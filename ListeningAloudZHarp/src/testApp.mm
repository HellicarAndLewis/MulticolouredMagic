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

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofBackground(255, 255, 255);
	
	centerer.setup(WIDTH, HEIGHT);
	setupGraphics();
	
	ofSetFrameRate(60);
	sampler.init();
	

	ofSoundStreamSetup(2, 1, this, 44100, 512, 4);
    
    //jgl z harp after
    
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	// enable depth->video image calibration
	kinect.setRegistration(true);
    
	kinect.init();
	
	kinect.open();
	
	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
    maskImage.allocate(kinect.width, kinect.height);
    
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
    panel.setup("Listening Aloud Z Harp", 0, 0, 1024/2, ofGetHeight());
	panel.addPanel("Kinect", 4, false);
	panel.setWhichPanel("Kinect");
	panel.setWhichColumn(0);
    //panel.addSlider("Brightness", "BRIGHTNESS", 255,0,255,true); //true means this is an int
    //panel.addSlider(string name, string xmlName, float value, float low, float high. bool isanint)
    panel.addSlider("near", "NEAR", 255, 0, 255, true);
    panel.addSlider("far", "FAR", 0, 0, 255, true);
    panel.addToggle("horizontalFlip", "HORIZONTALFLIP", false);
    panel.addSlider("minArea", "MINAREA", 100,1,10000, true);
    panel.addSlider("maxArea", "MAXAREA", 10000,1,10000, true);
    panel.addSlider("nConsidered", "NCONSIDERED", 10,1,50, true);
    panel.addToggle("findHoles", "FINDHOLES", false);
    panel.addSlider("leftCrop", "LEFTCROP", 0.f, 0.f,1.f, false);
    panel.addSlider("rightCrop", "RIGHTCROP", 1.f, 0.f,1.f, false);
    panel.addSlider("topCrop", "TOPCROP", 0.f, 0.f,1.f, false);
    panel.addSlider("bottomCrop", "BOTTOMCROP", 1.f,0.f,1.f, false);
    panel.loadSettings("settings.xml");
    
    ofAddListener(blobTracker.blobAdded, this, &testApp::blobAdded);
    ofAddListener(blobTracker.blobMoved, this, &testApp::blobMoved);
    ofAddListener(blobTracker.blobDeleted, this, &testApp::blobDeleted);
	 
}


void testApp::setupGraphics() {
}

//--------------------------------------------------------------
void testApp::update(){
    sampler.update();
    
    kinect.update();
    
    panel.update();
	
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
		
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        if(panel.getValueB("HORIZONTALFLIP")){
            grayImage.mirror(false, true/*bool bFlipVertically, bool bFlipHorizontally*/);
        }
        
        maskGrayImage();
        
        grayImage.flagImageChanged();
		
        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold(panel.getValueI("NEAR"), true);
        grayThreshFar.threshold(panel.getValueI("FAR"));
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		
		// update the cv images
		grayImage.flagImageChanged();
		
		// find contours
        //contourFinder.findContours(ofxCvGrayscaleImage &input, int minArea, int maxArea, int nConsidered, bool bFindHoles)
        
        /*update( ofxCvGrayscaleImage& input, int _threshold = -1,
         int minArea = 20 ,int maxArea = (340*240)/3, int nConsidered = 10,
         double hullPress = 20, bool bFindHoles = false, bool bUseApproximation = true);*/
        
        blobTracker.update(grayImage, -1, panel.getValueI("MINAREA"), panel.getValueI("MAXAREA"), panel.getValueI("NCONSIDERED"), 20, panel.getValueB("FINDHOLES"), true);
        //contourFinder.findContours(grayImage, _("minArea"), _("maxArea"), _("nConsidered"), _("findHoles"));
	}
}

void testApp::maskGrayImage(){
    //make sure its black
    cvSet(maskImage.getCvImage(), cvScalar(0));
    //draw a white rectangle in the image, to the sizes of the left/right/up/down crop
    /*     panel.addSlider("leftCrop",0.f, 0.f,1.f);
     panel.addSlider("rightCrop",1.f, 0.f,1.f);
     panel.addSlider("topCrop",0.f,0.f,1.f);
     panel.addSlider("bottomCrop",1.f,0.f,1.f); */
    float leftCropInPixels = panel.getValueF("LEFTCROP") * kinect.getWidth();
    float rightCropInPixels = panel.getValueF("RIGHTCROP") * kinect.getWidth();
    float topCropInPixels = panel.getValueF("TOPCROP") * kinect.getHeight();
    float bottomCropInPixels = panel.getValueF("BOTTOMCROP") * kinect.getHeight();
    
    CvPoint topLeft = cvPoint(leftCropInPixels, topCropInPixels);
    CvPoint bottomRight = cvPoint(rightCropInPixels,bottomCropInPixels);
    
    cvRectangle(maskImage.getCvImage(), topLeft, bottomRight, cvScalar(255), CV_FILLED);
    maskImage.flagImageChanged();
    //and it with the grayImage from the kinect, to only get the pixels that you want to look at, and then do blobs on those
    cvAnd(maskImage.getCvImage(), grayImage.getCvImage(), grayImage.getCvImage()); //can this be done "in place"?
    grayImage.flagImageChanged();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	sampler.draw();
	sampler.gui.draw();
	
    ofSetColor(255, 255, 255);
	
    // draw from the live kinect
    kinect.drawDepth(10, 10, 400, 300);
    kinect.draw(420, 10, 400, 300);
    
    grayImage.draw(10, 320, 400, 300);
    blobTracker.draw(10, 320, 400, 300);
    //contourFinder.draw(10, 320, 400, 300);
    
    /*	// or, instead we can draw each blob individually,
     // this is how to get access to them:
     
     for (int i = 0; i < blobTracker.size(); i++){
     ofFill();
     ofSetColor(255,0,0);
     ofCircle(blobTracker[i].centroid.x * ofGetWidth(),
     blobTracker[i].centroid.y * ofGetHeight(),
     10);
     ofSetColor(0);
     ofDrawBitmapString(ofToString( blobTracker[i].id ),
     blobTracker[i].centroid.x * ofGetWidth(),
     blobTracker[i].centroid.y * ofGetHeight());
     }*/
    
    maskImage.draw(420, 320, 400,300);
    
	
	// draw instructions
	ofSetColor(255, 255, 255);
	stringstream reportStream;
	reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
	<< ofToString(kinect.getMksAccel().y, 2) << " / "
	<< ofToString(kinect.getMksAccel().z, 2) << endl
	<< "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
	<< "set near threshold " << panel.getValueF("NEAR") << endl
	<< "set far threshold " << panel.getValueF("FAR") << " num blobs found " << contourFinder.nBlobs
	<< ", fps: " << ofGetFrameRate() << endl
	<< "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl
	<< "press 1-5 & 0 to change the led mode (mac/linux only)" << endl;
	ofDrawBitmapString(reportStream.str(),20,652);
    
    panel.draw();
}

//--------------------------------------------------------------
void testApp::exit(){
   	kinect.close(); 
}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
//	printf(".\n");
	sampler.audioRequested (output,bufferSize,nChannels);
	
}
void testApp::audioIn(float * output, int bufferSize, int nChannels){
	sampler.audioReceived(output,bufferSize,nChannels);
	
}

void testApp::mouseDragged(int x, int y, int button) {
    sampler.mouseDragged(x, y, button);
	sampler.gui.touchMoved(button, x,y);
    
    panel.mouseDragged(x, y, button);
}
void testApp::mousePressed(int x, int y, int button) {
	sampler.mousePressed(x, y, button);
	sampler.gui.touchDown(button, x,y);
    
    panel.mousePressed(x, y, button);

}
void testApp::mouseReleased(int x, int y, int button) {
	sampler.mouseReleased(x, y, button);
	sampler.gui.touchUp(button, x,y);
    
    panel.mouseReleased();
}


void testApp::blobAdded(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " added" );
    sampler.triggerSound(1.f);
}

void testApp::blobMoved(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " moved" );
}

void testApp::blobDeleted(ofxBlob &_blob){
    ofLog(OF_LOG_NOTICE, "Blob ID " + ofToString(_blob.id) + " deleted" );
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'g':
            panel.toggleView();
            break;
		case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
			
		case '1':
			kinect.setLed(ofxKinect::LED_GREEN);
			break;
			
		case '2':
			kinect.setLed(ofxKinect::LED_YELLOW);
			break;
			
		case '3':
			kinect.setLed(ofxKinect::LED_RED);
			break;
			
		case '4':
			kinect.setLed(ofxKinect::LED_BLINK_GREEN);
			break;
			
		case '5':
			kinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
			break;
			
		case '0':
			kinect.setLed(ofxKinect::LED_OFF);
			break;
	}
}
