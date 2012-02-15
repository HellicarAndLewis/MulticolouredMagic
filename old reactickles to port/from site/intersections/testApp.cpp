
#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	score.totalScore = 0;
	
	// Work out the size of the array sizeof() returns size in 
	// bytes, not it's length so result needs to be divided by 
	// size of the array item type...
	//ballArrayLength = sizeof(ballArray) / sizeof(Ball); 
	
	sound.loadSound("Pop1.wav");
	sound.setMultiPlay(false);
	
	myFont.loadFont("vag.ttf", 256);
	mySmallFont.loadFont("vag.ttf", 32);
	
	ofEnableSmoothing();
	ofBackground(150, 150, 150);
	
	// Start Timer object
	timer.start();
	
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
	catcher.setLocation(mouseX, mouseY);
	catcher.display();
	
	/*
	// Calculate time since app started
	passedTime = ofGetElapsedTimeMillis() - startTime;
	
	// Every two seconds set background to a random colour
	// and set new start time.
	if(passedTime > 2000) {
		ofBackground(ofRandom(0, 255),ofRandom(0, 255),ofRandom(0, 255));
		startTime = ofGetElapsedTimeMillis();
	}*/
	
	// Test to see if catcher intersects with any of the balls
	for(int i = 0; i < ARRAYLENGTH; i++) {
		if(catcher.intersect(ballArray[i])) {
			
			ballArray[i].color.r = catcher.catcherColor.r;
			ballArray[i].color.g = catcher.catcherColor.g;
			ballArray[i].color.b = catcher.catcherColor.b;
			//ballArray[i].end();
			sound.play();
			
			//score.increase();
		}
	}
	
	// Using Timer class to change background colour
	/*
	if(timer.finished()) {
		ofBackground(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
		timer.start();
	}
	*/
	
	// Draw white lines connecting each element of array
	/*
	for(int i = 0; i < 49; i++) {
		ofSetColor(255, 255, 255);
		ofLine(ballArray[i].x, ballArray[i].y, ballArray[i+1].x, ballArray[i+1].y);
	}*/
	
	// Check if each ball intersects with every other ball,
	// if so, highlight both intersecting balls
	for(int i = 0; i < ARRAYLENGTH; i++) {
		for(int j = 0; j < i; j++) {
			if(ballArray[i].intersect(ballArray[j])) {
				// Intersecting balls inherit colour from one another
				ballArray[i].color.r = ballArray[j].color.r;
				ballArray[i].color.g = ballArray[j].color.g;
				ballArray[i].color.b = ballArray[j].color.b;
				//ballArray[i].intersecting = ballArray[j].intersecting = true;
			}
			
		}
		ballArray[i].move();
		ballArray[i].display();
	}
	
	// Display some text
	/*
	ofSetColor(255,255,255, 50);	
	scoreString = ofToString(score.returnScore());
	myFont.drawString(scoreString, ofGetWidth()/2 - 300, ofGetHeight()/2);
	
	
	if(score.returnScore() == 50) {
		string resetMessage = "Press 'P' to play again";
		mySmallFont.drawString(resetMessage, ofGetWidth()/2 - 300, ofGetHeight()/2 + mySmallFont.stringHeight(resetMessage)*2);
	}*/
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if(key == 's') {
		ofSaveScreen(ofToString(count++) + ".png");
	}
	
	// Reset all balls and speeds to random positions
	if(key == 'p' || key == 'P') {
		
		score.reset();
		
		for(int i = 0; i < ARRAYLENGTH; i++) {
			// Reset everything
			ballArray[i].position.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
			ballArray[i].xspeed = ofRandom(0.01, 0.1);
			ballArray[i].yspeed = ofRandom(0.01, 0.1);
			ballArray[i].color.r = ofRandom(0,255); 
			ballArray[i].color.g = ofRandom(0,255); 
			ballArray[i].color.b = ofRandom(0,255);
			
			
		}
	}
	
	if(key == 'f') {
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

