#include "Windmills.h"
#include "constants.h"
#include "ColorPicker.h"
#include "Settings.h"

//--------------------------------------------------------------
void Windmills::setup(){

	windmillsX = 30;
	windmillsY = 25;

	
	float w = WIDTH;
	float h = HEIGHT;
	
	
	for(int x = 0; x < windmillsX; x++) {
		for(int y = 0; y < windmillsY; y++) {
			windmills.push_back(Windmill());
			ofVec2f pos = ofVec2f((float)(x+1)*w/(float)(windmillsX+1), (float)(y+1)*h/(float)(windmillsY+1));
			if(y%2==0) {
				pos.x -= (float)w/((float)(windmillsX+1)*4.f);
			} else {
				pos.x += (float)w/((float)(windmillsX+1)*4.f);
			}
			windmills.back().pos = pos;
		}
	}
	
#ifndef TARGET_OF_IPHONE
	opticalFlow.allocate(VISION_WIDTH/2, VISION_HEIGHT/2);
	grey.allocate(VISION_WIDTH, VISION_HEIGHT);
	curr.allocate(VISION_WIDTH/2, VISION_HEIGHT/2);
	prev.allocate(VISION_WIDTH/2, VISION_HEIGHT/2);
#endif
	
}
int Windmills::toWindmillIndex(int x, int y) {
	return x*windmillsX + y;
}
//--------------------------------------------------------------
void Windmills::update(){
	//flowField.update();
	/*for(int x = 1; x < windmillsX-1; x++) {
		for(int y = 1; y < windmillsY-1; y++) {
			
			windmills[toWindmillIndex(x, y)].rotationSpeed = (windmills[toWindmillIndex(x-1, y)].rotationSpeed
																	 + windmills[toWindmillIndex(x, y)].rotationSpeed 
																	 + windmills[toWindmillIndex(x+1, y)].rotationSpeed
																	 + windmills[toWindmillIndex(x, y-1)].rotationSpeed 
																	 + windmills[toWindmillIndex(x, y+1)].rotationSpeed)/5;
		}
	}*/
	
#ifndef TARGET_OF_IPHONE
	
	if(colorImg!=NULL) {
		grey = *colorImg;
		curr.scaleIntoMe(grey);
	}
	opticalFlow.calc(prev, curr, 3);
	prev = curr;
	opticalFlow.blur(4);
	for(int i = 0; i < windmills.size(); i++) {

		float cvX = ofMap(windmills[i].pos.x, 0, WIDTH, 0, VISION_WIDTH/2);
		float cvY = ofMap(windmills[i].pos.y, 0, HEIGHT, 0, VISION_HEIGHT/2);
		ofVec2f force;
		opticalFlow.forceAtPos(cvX, cvY, &force.x, &force.y);
		//force = ofVec2f();
		if(force.length()>1) {
			windmills[i].applyForce(force);
		}
		
	}
#endif
}

//--------------------------------------------------------------
void Windmills::draw(){
	ofBackground(255);
	int color = ColorPicker::colors[(int)(Settings::getInstance()->settings["fgColor"])];
	ofColor c = ofColor::fromHex(color);
	for(int i = 0; i < windmills.size(); i++) {
		windmills[i].draw(c);
	}
	//opticalFlow.draw(0, 0, WIDTH, HEIGHT);
}

bool Windmills::touchDown(float x, float y, int touchId) {
	touches[touchId] = ofVec2f(x, y);
	return true;
}

bool Windmills::touchUp(float x, float y, int touchId) {
	touches.erase(touchId);
	return true;
}

bool Windmills::touchMoved(float x, float y, int touchId) {
	ofVec2f oldPos = touches[touchId];
	ofVec2f newPos = ofVec2f(x, y);
	ofVec2f force = newPos-oldPos;
	for(int i = 0; i < windmills.size(); i++) {
		windmills[i].applyForce(newPos, force);
	}
	touches[touchId] = newPos;
	return true;
}

