/**
 * MagicAppEvents.cpp
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */

#include "MagicApp.h"

/***************************************************************
 
 [ left/right] arrow keys move between the apps
 [   0 - 9   ] pressing the number keys jumps to a different app
 [   q/w/e   ] switch between different modes of an app
 [     f     ] toggle fullscreen
 [    ' '    ] toggle gui
 [     p     ] takes a picture of the screen and puts it on the desktop
 
 All keys are propagated to the individual apps
 
 ***************************************************************/

//--------------------------------------------------------------
void MagicApp::keyPressed  (int key){ 
	
	// do switching
	if(key==356) {
		appIndex--;
		if(appIndex<0) appIndex = apps.size()-1;
		//		apps[appIndex]->init();
	} else if(key==358) {
		appIndex++;
		if(appIndex>=apps.size()) appIndex = 0;
		//		apps[appIndex]->init();
	} else if(key>='0' && key<='9') {
		int index = key - '1';
		if(key==-1) key = 9; // take care of wrapping zero
		if(index>=0 && index<apps.size()) {
			appIndex = index;
            
			//			apps[appIndex]->init();
		}
    } else if(key=='q' || key=='w' || key=='e' || key=='Q' || key=='W' || key=='E') {
        
        if(key=='q' || key=='Q') {
			
            apps[appIndex]->setMode(0);
            
        } else if(key=='w' || key=='W') {
            apps[appIndex]->setMode(1);
        } else if(key=='e' || key=='E') {
            apps[appIndex]->setMode(2);
        }
        
	} else if(key=='f') {
		ofToggleFullscreen();
	} else if(key==' ') {
		gui.toggleDraw();
	} else if(key=='p' || key=='P') {
		mustTakeScreenshot = true;
	}
	
	apps[appIndex]->keyPressed(key);
}

//--------------------------------------------------------------
void MagicApp::keyReleased(int key){ 
	apps[appIndex]->keyReleased(key);
}


/***************************************************************
 ALL MOUSE EVENTS PROPAGATE TO TOUCH EVENTS
 ***************************************************************/
 
//--------------------------------------------------------------
void MagicApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void MagicApp::mouseDragged(int x, int y, int button){
	apps[appIndex]->touchMoved(x, y, button);
}

//--------------------------------------------------------------
void MagicApp::mousePressed(int x, int y, int button){
	apps[appIndex]->touchDown(x, y, button);
}

//--------------------------------------------------------------
void MagicApp::mouseReleased(int x, int y, int button){
	apps[appIndex]->touchUp(x, y, button);
}

//--------------------------------------------------------------
void MagicApp::windowResized(int w, int h){
	apps[appIndex]->windowResized(w, h);
}


/***************************************************************
 TOUCH EVENTS COME FROM TUIO, KINECT OR MOUSE
 ***************************************************************/


void MagicApp::touchDown(ofTouchEventArgs &touch) {
	ofVec2f pos(touch.x, touch.y);
	
	// now scaled for screen coords
	pos *= ofGetWindowSize();
	apps[appIndex]->touchDown(pos.x, pos.y, touch.id);
}

void MagicApp::touchMoved(ofTouchEventArgs &touch) {
	// touches are normalized
	ofVec2f pos(touch.x, touch.y);
	
	// now scaled for screen coords
	pos *= ofGetWindowSize();
	apps[appIndex]->touchMoved(pos.x, pos.y, touch.id);
}

void MagicApp::touchUp(ofTouchEventArgs &touch) {
	ofVec2f pos(touch.x, touch.y);
	
	// now scaled for screen coords
	pos *= ofGetWindowSize();
	apps[appIndex]->touchUp(pos.x, pos.y, touch.id);	
}



