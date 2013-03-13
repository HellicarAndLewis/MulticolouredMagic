#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	Pad::circle.loadImage("circle.png");
	Pad::circle.setAnchorPercent(0.5, 0.5);
	ofSetLogLevel(OF_LOG_VERBOSE);

	ofEnableAlphaBlending();
	ofBackground(0,0,0);
	
	centerer.setup(WIDTH, HEIGHT);
	setupGraphics();
	setupOrientation();
	
#ifdef TARGET_OF_IPHONE
	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	// register touch events
	ofAddListener(ofEvents().touchDown, this, &testApp::touchDown);
	ofAddListener(ofEvents().touchMoved, this, &testApp::touchMoved);
	ofAddListener(ofEvents().touchUp, this, &testApp::touchUp);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);

	gui.setup();
#else
//	setDataPathRootToAppContents(appName);

#endif
	recMode.set(20, ofGetHeight()-40, 120, 30);
	recMode.setup("PLAY MODE|REC MODE", Pad::recMode);
	
	ofSetFrameRate(60);
	
	

	ofSoundStreamSetup(0, 1, this, 44100, 512, 4);
	setNumPads(3);
	
	Pad::unitCircle.push_back(ofVec2f());
	for(int i = 0; i <= 360; i++) {
		float angle = ofMap(i, 0, 360, 0, PI*2);
		Pad::unitCircle.push_back(ofVec2f(cos(angle), sin(angle)));
	}

}


void testApp::setNumPads(int numPads) {
	if(numPads>11) numPads = 11;
	mutex.lock();
	gui.numPads = numPads;
	

	
	ofVec2f centre(ofGetWidth()/2, ofGetHeight()/2);
	
	float radius = ofGetHeight()/2;
	float dist = radius * 1.5;
	switch(numPads) {
		case 1:
			dist = 0;
			break;
		case 2:
			dist = ofGetWidth()/4;
			radius /= 1.6;
			break;
		case 3:
			dist = ofGetHeight()/3.5;
			radius /= 2.2;
			break;
		case 4:
			dist = ofGetHeight()/3.6;
			radius /= 3;
			break;
		case 5:
			dist = ofGetHeight()/3.2;
			radius /= 2.8;
			break;
		case 6:
			dist = ofGetHeight()/3;
			radius /= 2.9;
			break;
		case 7:
			dist = ofGetHeight()/3;
			radius /= 3.2;
			break;
		case 8:
			dist = ofGetHeight()/3;
			radius /= 3.3;
			break;
		case 9:
			dist = ofGetHeight()/3;
			radius /= 3.5;
			break;
		case 10:
			dist = ofGetHeight()/3;
			radius /= 3.7;
			break;
		case 11:
			dist = ofGetHeight()/3;
			radius /= 4;
			break;
	}
	
	
	// if there aren't enough, add here
	for(int i = pads.size(); i < numPads; i++) {
		pads.push_back(new Pad);
	}
	
	// if there's too many, remove
	while(pads.size()>numPads) {
		delete pads[pads.size()-1];
		pads.erase(pads.begin()+pads.size()-1);
	}
	
	
	for(int i = 0; i < pads.size(); i++) {
		float angle = ofMap(i, 0, numPads, 0, PI*2);
		ofVec2f offset(dist*cos(angle), dist*sin(angle));
		pads[i]->set(i, centre+offset,radius);
	}
	mutex.unlock();
}



void testApp::setupGraphics() {
}

void testApp::setupOrientation() {
}

void testApp::updateOrientation() {
}

bool lastMode = false;
//--------------------------------------------------------------
void testApp::update(){
	if(gui.numPads!=pads.size()) {
		setNumPads(gui.numPads);
	}
	
	if(lastMode!=Pad::recMode) {
		if(Pad::recMode) {
			ofSoundStreamStop();
			ofSoundStreamSetup(0, 1, this, 44100, 512, 4);
		} else {
			ofSoundStreamStop();
			ofSoundStreamSetup(2, 0, this, 44100, 512, 4);
		}
		if(Pad::recMode) {
			Pad::currRecId = -1;
		}
	}
	lastMode = Pad::recMode;
	
}

//--------------------------------------------------------------
void testApp::draw(){
	if(Pad::recMode) {
		ofClear(100,0,0,0);
	} else {
		ofClear(0, 0, 0, 0);
	}
	for(int i = 0; i < pads.size(); i++) {
		pads[i]->draw();
	}
	recMode.draw();
	gui.draw();

}

//--------------------------------------------------------------
void testApp::exit(){
    
}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
	memset(output, 0, bufferSize*nChannels*sizeof(float));
	mutex.lock();
	for(int i = 0; i < pads.size(); i++) {
		pads[i]->addSamples(output, bufferSize, nChannels);
	}

	mutex.unlock();
	
	
	// quieten
	int n = bufferSize * nChannels;
	float v = 1.f/pads.size();
	for(int i = 0; i < n; i++) {
		output[i] *= v;
	}
	//sampler.audioRequested (output,bufferSize,nChannels);
	
}
void testApp::audioIn(float * output, int bufferSize, int nChannels){
	if(Pad::recMode && Pad::currRecId!=-1) {
		mutex.lock();
		pads[Pad::currRecId]->recordSamples(output, bufferSize);
		mutex.unlock();
	}
	//sampler.audioReceived(output,bufferSize,nChannels);
	
}


//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
	gui.touchDown(touch.id, touch.x, touch.y);
	if(!gui.gui.isEnabled()) {
		for(int i = 0; i < pads.size(); i++) {
			pads[i]->touchDown(touch.x, touch.y, touch.id);
		}
		recMode.touchDown(touch.x, touch.y, touch.id);
	}
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
	gui.touchMoved(touch.id, touch.x, touch.y);
	if(!gui.gui.isEnabled()) {
		for(int i = 0; i < pads.size(); i++) {
			pads[i]->touchMoved(touch.x, touch.y, touch.id);
		}
	
		recMode.touchMoved(touch.x, touch.y, touch.id);
	}
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
	gui.touchUp(touch.id, touch.x, touch.y);
	
	if(!gui.gui.isEnabled()) {
		for(int i = 0; i < pads.size(); i++) {
			pads[i]->touchUp(touch.x, touch.y, touch.id);
		}
		
		recMode.touchUp(touch.x, touch.y, touch.id);
	}
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
	touchUp(touch);
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
	touchUp(touch);
}

//--------------------------------------------------------------
void testApp::lostFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    
}



#ifndef TARGET_OF_IPHONE


void testApp::mouseDragged(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchMoved(touch);
}
void testApp::mousePressed(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchDown(touch);
}
void testApp::mouseReleased(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchUp(touch);
}




#endif
