#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofEnableAlphaBlending();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	ofEnableSmoothing();
	ofSetCircleResolution(20);
	ofSetVerticalSync(true);


	// create 2000 stars - lower this number if it's too slow
	for(int i = 0; i < 1; i++) {
		pa.push_back(Star());
	//	pa[i].setup();
	//	pa[i].reset();
	
	}
	
	ofSetBackgroundAuto(false);
	
	ofBackground(0, 0, 0);
	
}

//--------------------------------------------------------------
void testApp::update(){	
	for(int i = 0; i < pa.size(); i++) {
		
		if(attracting) {
			pa[i].attract(p.x, p.y);
		}
	
	}
	
	for(int i = 0; i < pa.size(); i++) {
		pa[i].update();	
	}
	
}


//--------------------------------------------------------------
void testApp::draw(){
	for(int i = 0; i < pa.size(); i++) {	
		pa[i].draw(255, 0, 0, 255);
	}	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if(key=='f') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	p.x = x;
	p.y = y;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	attracting = 1;
	p.x = x;
	p.y = y;
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
		attracting = 0;
}


