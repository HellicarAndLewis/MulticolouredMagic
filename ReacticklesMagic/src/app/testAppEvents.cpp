/**
 * testAppEvents.cpp
 * ReacticklesMagicMac
 *
 * Created by Marek Bereza on 14/06/2011.
 *
 */


#include "testApp.h"
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
#ifndef TARGET_OF_IPHONE
	if(!gui.isOn()) 
#endif
	{
		if(currentApp!=&mainMenu) {
			if(backButton.touchDown(touch.x, touch.y, touch.id)) {
				return;
				
			} else {
				if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
					if(modeUpButton.touchDown(touch.x, touch.y, touch.id)) {
						return;
					} else if(modeDownButton.touchDown(touch.x, touch.y, touch.id)) {
						return;
					}
					
				}
			}
		}
		currentApp->touchDown(touch.x, touch.y, touch.id);
		
	}
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
#ifndef TARGET_OF_IPHONE
	if(!gui.isOn()) 
#endif
	{
		if(currentApp!=&mainMenu) {
			if(backButton.touchMoved(touch.x, touch.y, touch.id)) {
				return;
			} else {
				if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
					if(modeUpButton.touchMoved(touch.x, touch.y, touch.id)) {
						return;
					} else if(modeDownButton.touchMoved(touch.x, touch.y, touch.id)) {
						return;
					}
				}
			}
		}
		currentApp->touchMoved(touch.x, touch.y, touch.id);
	}
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){
#ifndef TARGET_OF_IPHONE
	if(!gui.isOn()) 
#endif
	{
		if(currentApp!=&mainMenu) {
			if(backButton.touchUp(touch.x, touch.y, touch.id)) {
				return;
			}  else {
				if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
					if(modeUpButton.touchUp(touch.x, touch.y, touch.id)) {
						return;
					} else if(modeDownButton.touchUp(touch.x, touch.y, touch.id)) {
						return;
					}
				}
			}
		}
		currentApp->touchUp(touch.x, touch.y, touch.id);
	}
}



//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){
	
}



//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
	
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
	
}


//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs& args){
	
}

#ifdef TARGET_OF_IPHONE	
void testApp::gotFocus() {
	//	ofSoundStreamStart();
}
void testApp::lostFocus() {
	//	ofSoundStreamStop();
}
#else

///////////////////////////////////////////////////////////////////////
// MAC SPECIFIC EVENTS

void testApp::keyPressed(int key) {
	if(key==' ') {
		gui.toggleDraw();
	} else if(key=='p' || key=='P') {
		mustTakeScreenshot = true;
	}
}

/////////////////////////////////////////////////////////////////////
// Passing TUIO stuff into the touch events
//
// tuio comes in normalized, so we need to scale it up to screen dimensions.
//
void testApp::tuioTouchDown(ofTouchEventArgs &touch) {	
	touch.x *= WIDTH;
	touch.y *= HEIGHT;
	touchDown(touch);
}
void testApp::tuioTouchMoved(ofTouchEventArgs &touch) {
	touch.x *= WIDTH;
	touch.y *= HEIGHT;
	touchMoved(touch);
}
void testApp::tuioTouchUp(ofTouchEventArgs &touch) {
	touch.x *= WIDTH;
	touch.y *= HEIGHT;
	touchUp(touch);
}

/////////////////////////////////////////////////////////////////////
// Passing mouse stuff into the touch events

void testApp::mousePressed(int x, int y, int button) {
	ofTouchEventArgs t;
	t.x = x;
	t.y = y;
	t.id = button;
	touchDown(t);
}

void testApp::mouseDragged(int x, int y, int button) {
	ofTouchEventArgs t;
	t.x = x;
	t.y = y;
	t.id = button;
	touchMoved(t);
}

void testApp::mouseReleased(int x, int y, int button) {
	ofTouchEventArgs t;
	t.x = x;
	t.y = y;
	t.id = button;
	touchUp(t);
}

#endif