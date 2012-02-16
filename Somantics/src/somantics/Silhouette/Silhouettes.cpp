#include "Silhouettes.h"
#include "constants.h"

#ifndef TARGET_OF_IPHONE
#include "contourutils.h"
#endif
#include "Settings.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif


//--------------------------------------------------------------
void Silhouettes::setup(){
	//ofSetDataPathRoot(ofToDataPath("../SilhouetteDemo.app/Contents/"));

	Silhouette::setup();
	ofEnableNormalizedTexCoords();






	float w = WIDTH;
	float h = HEIGHT;




#ifdef USE_FBO
	currFrame = new ofFbo();
	histFrame = new ofFbo();
	currFrame->allocate(w, h, GL_RGBA);
	histFrame->allocate(w, h, GL_RGBA);
#else
	ofSetBackgroundAuto(false);
#endif
}

Silhouettes::~Silhouettes() {
#ifdef USE_FBO
	delete currFrame;
	delete histFrame;
#endif
}

void Silhouettes::stop() {
#ifndef USE_FBO
	ofSetBackgroundAuto(true);
#endif
}
//--------------------------------------------------------------
void Silhouettes::update(){
#ifndef TARGET_OF_IPHONE
	if(threshImg!=NULL) {
		contourFinder.findContours(*threshImg, 20*20, VISION_WIDTH*VISION_HEIGHT, 20, false);
	}

#endif
}

bool histFrameCleared = false;
//--------------------------------------------------------------
void Silhouettes::draw(){
//	ofBackground(255);


#ifdef USE_FBO

	ofBackground(255);
	currFrame->begin();
	ofClear(0, 0, 0, 0);

#else
	ofSetColor(255, 255, 255, 20);
	ofRect(0, 0, WIDTH, HEIGHT);
#endif

#ifdef TARGET_OF_IPHONE
	int colorIndex = Settings::getInstance()->settings["fgColor"];
	for(int i = 0; i < silhouettes.size(); i++) {

		if(colorIndex==20) {
			ofSetColor(255, 0, 0);
		} else {
			ofSetHexColor(ColorPicker::colors[colorIndex]);
		}
		silhouettes[i].draw();
		if(silhouettes[i].dead()) {
			silhouettes.erase(silhouettes.begin()+i);
			i--;
		}
	}
#else
	Silhouette s;
	int colorIndex = Settings::getInstance()->settings["fgColor"];

	for(int i = 0; i < contourFinder.blobs.size(); i++) {
		if(colorIndex==20) {
			ofSetColor(255, 0, 0);
		} else {
			ofSetHexColor(ColorPicker::colors[colorIndex]);
		}
		vector<ofVec2f> points, hull;

		for(int j = 0; j < contourFinder.blobs[i].pts.size(); j++) {
			ofVec2f point;
			point.x = contourFinder.blobs[i].pts[j].x*WIDTH/VISION_WIDTH;
			point.y = contourFinder.blobs[i].pts[j].y*HEIGHT/VISION_HEIGHT;
			points.push_back(point);
		}


		tricks::math::calcConvexHull(points, hull);


		ofVec2f *p = new ofVec2f[hull.size()];
		for(int j = 0; j < hull.size(); j++) {
			p[j] = hull[j];
		}

		s.draw(p, hull.size());
		delete [] p;
	}
#endif

#ifdef USE_FBO
	currFrame->end();
/*
	histFrame->begin();
	if(!histFrameCleared) {
		ofClear(0,0,0,0);
		histFrameCleared = true;
	}
	glColor4f(1,1,1, 0.02);

	ofRect(0, 0, WIDTH, HEIGHT);

	glColor4ub(255, 255, 255, 200);
	currFrame->draw(0, 0);
	histFrame->end();
	glColor4f(1, 1, 1, 1);
	histFrame->draw(0, 0);
*/
	currFrame->draw(0, 0, WIDTH, HEIGHT);
#endif

}


bool Silhouettes::touchDown(float x, float y, int touchId) {
#ifdef TARGET_OF_IPHONE
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchDown(x,y,touchId)) {
			return true;
		}
	}
	silhouettes.push_back(Silhouette());
	silhouettes.back().touchDown(x, y, touchId);
	touches[touchId] = ofVec2f(x, y);
#endif
	return true;
}

bool Silhouettes::touchUp(float x, float y, int touchId) {
#ifdef TARGET_OF_IPHONE
	touches.erase(touchId);
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchUp(touchId)) {

			return true;
		}
	}
#endif
	return true;
//	printf("Touch Deleted: %d\n", touchId);
}

bool Silhouettes::touchMoved(float x, float y, int touchId) {
#ifdef TARGET_OF_IPHONE
	touches[touchId].x = x;
	touches[touchId].y = y;
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchMoved(x, y, touchId)) {
			return true;
		}
	}
#endif
	return true;
}

