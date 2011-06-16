#include "Windmills.h"
#include "constants.h"
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
}

//--------------------------------------------------------------
void Windmills::draw(){
	ofBackground(255);
	for(int i = 0; i < windmills.size(); i++) {
		windmills[i].draw();
	}
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

