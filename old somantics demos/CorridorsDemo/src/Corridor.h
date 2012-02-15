/**
 * Corridor.h
 * CorridorsDemo
 *
 * Created by Marek Bereza on 10/05/2011.
 *
 */

class Corridor {
public:
	Corridor() {
		curtainSpeed = 0.4; // 0 is forever, 1 is instantaneous
		
		fingerWidth = 40;
		minTouchDistance = 60;
		startX = 0;
		endX = ofGetWidth();
	}
	
	bool touchDown(float x, float y, int touchId) {
		if(touches.size()==0) {
			touches[touchId] = ofVec2f(x,y);
			return true;
		} else {
			map<int,ofVec2f>::iterator it;
			for(it = touches.begin(); it != touches.end(); it++) {
				if(ABS(x-(*it).second.x)<minTouchDistance) {
					touches[touchId] = ofVec2f(x,y);
					return true;
				}
			}
			
		}
		return false;
	}
	
	
	bool touchMoved(float x, float y, int touchId) {
		if(touches.find(touchId)!=touches.end()) {
			touches[touchId].x = x;
			touches[touchId].y = y;
			return true;
		}
		return false;
	}
	
	bool touchUp(int touchId) {
		if(touches.find(touchId)!=touches.end()) {
			touches.erase(touchId);
			return true;
		} else {
			return false;
		}
	}
	
	bool dead() {
		return touches.size()==0 && startX<fingerWidth/2 + 1 && endX>ofGetWidth()-fingerWidth/2 - 1;
	}
	
	void draw() {
		map<int,ofVec2f>::iterator it;
		float targetStartX = ofGetWidth();
		float targetEndX = 0;
		for(it = touches.begin(); it != touches.end(); it++) {
			ofVec2f t = (*it).second;
			if(t.x>targetEndX) targetEndX = t.x;
			if(t.x<targetStartX) targetStartX = t.x;
		}
		
		if(targetEndX==0) targetEndX = ofGetWidth();
		if(targetStartX==ofGetWidth()) targetStartX = 0;
		
		targetStartX -= fingerWidth/2;
		targetEndX += fingerWidth/2;
		
		startX = ofLerp(startX, targetStartX, curtainSpeed);
		endX = ofLerp(endX, targetEndX, curtainSpeed);
		ofRect(0, 0, startX, ofGetHeight());
		ofRect(endX, 0, ofGetWidth()-endX, ofGetHeight());
	}
	
	float curtainSpeed;
	float minTouchDistance;
	float fingerWidth;
	float startX, endX;
	map<int,ofVec2f> touches;
};