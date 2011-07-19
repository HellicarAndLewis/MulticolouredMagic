/**
 * Centerer.h
 *
 * Centers and scales opengl content within an area to fill
 * the screen.
 *
 * You set this up with your desired resolution, then you 
 * do your drawing between begin() and end(). You also send 
 * all your 
 *
 * Created by Marek Bereza on 19/07/2011.
 *
 */
#include "ofMain.h"

class Centerer {
public:
	
	void setup(float width, float height) {
		
		this->width = width;
		this->height = height;
		fakeGameModeScale = (float)ofGetScreenHeight()/height;
		resizedScreenWidth = (float)ofGetScreenWidth()/fakeGameModeScale;
		moveRightBy = (resizedScreenWidth - width)/2;
		printf("Scale %f\nScreen Width: %f\nmoveRightBy: %f\n", fakeGameModeScale, resizedScreenWidth, moveRightBy);
	}
	
	void begin() {
		// do a fake OF_GAME_MODE - the real one locks up the computer when it crashes
		glPushMatrix();
		glScalef(fakeGameModeScale, fakeGameModeScale, fakeGameModeScale);
		glTranslatef(moveRightBy, 0, 0);
	}
	
	void end() {
		ofSetHexColor(0);
		// letterbox
		ofRect(-1000, 0, 1000, height);
		ofRect(width, 0, 1000, height);
		glPopMatrix();
	}
	
	
	void transformMouse(float &x, float &y) {
		x /= fakeGameModeScale;
		y /= fakeGameModeScale;
		x -= moveRightBy;
	}

	
	
	
private:
	float fakeGameModeScale;
	float resizedScreenWidth;
	float moveRightBy;
	
	float width;
	float height;
};