#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	
	ofSetFrameRate(120);
	
	
	
	ofBackground(0,0,0);

	for(int i = 0; i < 200; i++) {
		pa.push_back(Star());
		pa[i].setup();
		pa[i].reset();
	
	}
	
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	for(int i = 0; i < pa.size(); i++) {

		
		if(attracting) {
			pa[i].attract(p.x,p.y);
		}
		

		
		
		
	}
	
	
	
	
	for(int i = 0; i < pa.size(); i++) {
		pa[i].update();
		
	}
	
	
}


//--------------------------------------------------------------
void testApp::draw(){

	ofEnableAlphaBlending();
	
	// draw the stars
	for(int i = 0; i < pa.size(); i++) {
		
		ofPushMatrix();

		pa[i].draw(255, 0, 0, 255);
		ofPopMatrix();

	}
	ofDisableAlphaBlending();
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
	attracting = 1;
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



