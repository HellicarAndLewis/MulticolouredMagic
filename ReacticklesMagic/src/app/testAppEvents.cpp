/**
 * testAppEvents.cpp
 * ReacticklesMagicMac
 *
 * Created by Marek Bereza on 14/06/2011.
 *
 */


#include "testApp.h"
void testApp::buttonDown(float x, float y, int id) {

#ifndef TARGET_OF_IPHONE
	if(!gui.isOn())
#endif
	{
		if(currentApp!=mainMenu) {
			if(backButton.touchDown(x, y, id)) {
				return;
				
			} else {
			    printf("touch down\n");
				if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
                    printf("reactickle!?\n");
					if(modeUpButton.touchDown(x, y, id)) {
						return;
					} else if(modeDownButton.touchDown(x, y, id)) {
						return;
					} else {
                        printf("no hits\n");
					}
					
				}
			}
		}
		//currentApp->touchDown(touch.x, touch.y, touch.id);
		
	}

}
void testApp::buttonMoved(float x, float y, int id) {
#ifndef TARGET_OF_IPHONE
	if(!gui.isOn())
#endif
	{
		if(currentApp!=mainMenu) {
			if(backButton.touchMoved(x, y, id)) {
				return;
			} else {
				if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
					if(modeUpButton.touchMoved(x, y, id)) {
						return;
					} else if(modeDownButton.touchMoved(x, y, id)) {
						return;
					}
				}
			}
		}
		//currentApp->touchMoved(touch.x, touch.y, touch.id);
	}
}

void testApp::buttonUp(float x, float y, int id) {
#ifndef TARGET_OF_IPHONE
	if(!gui.isOn())
#endif
	{

		if(currentApp!=mainMenu) {
			if(backButton.touchUp(x, y, id)) {
				return;
			}  else {
				if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
					if(modeUpButton.touchUp(x, y, id)) {
						return;
					} else if(modeDownButton.touchUp(x, y, id)) {
						return;
					}
				}
			}
		}

	}
}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
	
#ifndef TARGET_OF_IPHONE
	if(!gui.isOn())
#endif
	{
		#ifdef TARGET_OF_IPHONE
		if(currentApp!=mainMenu) {
			if(backButton.touchDown(touch.x, touch.y, touch.id)) {
				return;

			} else {

				if(currentApp!=&aboutPage && currentApp!=&settingsPage) {

					if(modeUpButton.touchDown(touch.x, touch.y, touch.id)) {
						return;
					} else if(modeDownButton.touchDown(touch.x, touch.y, touch.id)) {
						return;
					} else {

					}

				}
			}
		}
		#endif
		currentApp->touchDown(touch.x, touch.y, touch.id);

	}
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
#ifndef TARGET_OF_IPHONE
	if(!gui.isOn())
#endif
	{
		#ifdef TARGET_OF_IPHONE
		if(currentApp!=mainMenu) {
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
		#endif
		currentApp->touchMoved(touch.x, touch.y, touch.id);
	}
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){
#ifndef TARGET_OF_IPHONE
	if(!gui.isOn())
#endif
	{
		#ifdef TARGET_OF_IPHONE
		if(currentApp!=mainMenu) {
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
		#endif
		currentApp->touchUp(touch.x, touch.y, touch.id);
	}
}



///////////////////////////////////////////////////////////////////////
// MAC SPECIFIC EVENTS
#ifndef TARGET_OF_IPHONE
void testApp::keyPressed(int key) {
	if(key==' ') {
		gui.toggleDraw();
	} else if(key=='p' || key=='P') {
		mustTakeScreenshot = true;
	} else if(key=='q' || key=='w' || key=='e' || key=='Q' || key=='W' || key=='E') {

        if(key=='q' || key=='Q') {

			if(isReactickle(currentApp)) {
				currentApp->setMode(0);
				modeDisplay.setMode(0);
			}
//            ofxOscMessage m;
 //           m.setAddress( "/modechange" );
//            m.addIntArg(0);
//            sender.sendMessage(m);

        } else if(key=='w' || key=='W') {
            if(isReactickle(currentApp)) {
				currentApp->setMode(1);
				modeDisplay.setMode(1);
			}

//            ofxOscMessage m;
//            m.setAddress( "/modechange" );
//            m.addIntArg(1);
//            sender.sendMessage(m);

        } else if(key=='e' || key=='E') {
            if(isReactickle(currentApp)) {
				currentApp->setMode(2);
				modeDisplay.setMode(2);
			}

//            ofxOscMessage m;
//            m.setAddress( "/modechange" );
//            m.addIntArg(2);
//            sender.sendMessage(m);
        }

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

#endif
