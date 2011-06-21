#include "Silhouettes.h"
#include "constants.h"



//--------------------------------------------------------------
void Silhouettes::setup(){
	//ofSetDataPathRoot(ofToDataPath("../SilhouetteDemo.app/Contents/"));

	Silhouette::setup();
	ofEnableNormalizedTexCoords();

	colors[0].setHex(0xFF0000);
	colors[1].setHex(0xFFFF00);
	colors[2].setHex(0xFF00FF);
	colors[3].setHex(0x0000FF);
	
	float w = WIDTH;
	float h = HEIGHT;

	
#ifdef USE_FBO
	currFrame = new ofFbo();
	histFrame = new ofFbo();
	currFrame->setup(256, 256);//w, h, GL_RGB);
	histFrame->setup(256, 256);//w, h, GL_RGB);
#endif
}

Silhouettes::~Silhouettes() {
#ifdef USE_FBO
	delete currFrame;
	delete histFrame;
#endif
}

//--------------------------------------------------------------
void Silhouettes::update(){
}

bool histFrameCleared = false;
//--------------------------------------------------------------
void Silhouettes::draw(){
//	ofBackground(255);
	ofSetBackgroundAuto(false);
	ofSetColor(255, 255, 255, 20);
	ofRect(0, 0, WIDTH, HEIGHT);
#ifdef USE_FBO	
	currFrame->begin();
	ofClear(0, 0, 0, 0);
#endif
	
	for(int i = 0; i < silhouettes.size(); i++) {
		ofSetColor(colors[i%NUM_COLORS]);
		silhouettes[i].draw();
		if(silhouettes[i].dead()) {
			silhouettes.erase(silhouettes.begin()+i);
			i--;
		}
	}
#ifdef USE_FBO
	currFrame->end();
	histFrame->begin();
	if(!histFrameCleared) {
		ofClear(0,0,0,0);
		histFrameCleared = true;
	}
	glColor4f(1,1,1, 0.02);
	
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	
	glColor4ub(255, 255, 255, 200);
	currFrame->draw(0, 0);
	histFrame->end();
	glColor4f(1, 1, 1, 1);
	histFrame->draw(0, 0);
#endif
	
}


bool Silhouettes::touchDown(float x, float y, int touchId) {
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchDown(x,y,touchId)) {
			return true;
		}
	}
	silhouettes.push_back(Silhouette());
	silhouettes.back().touchDown(x, y, touchId);
	touches[touchId] = ofVec2f(x, y);
	return true;	
}

bool Silhouettes::touchUp(float x, float y, int touchId) {
	touches.erase(touchId);
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchUp(touchId)) {
			
			return true;
		}
	}
	return true;
//	printf("Touch Deleted: %d\n", touchId);
}

bool Silhouettes::touchMoved(float x, float y, int touchId) {
	touches[touchId].x = x;
	touches[touchId].y = y;
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchMoved(x, y, touchId)) {
			return true;
		}
	}
	return true;
}

