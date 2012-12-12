/**
 * GuiDrawable.h
 * KinectTracker
 *
 * Created by Marek Bereza on 08/02/2011.
 *
 */
#include "LabeledControl.h"
#pragma once
namespace xmlgui {
	class Drawable: public LabeledControl {
	public:
		ofBaseDraws *drawable;
		Drawable(): LabeledControl() {
			drawable = NULL;
		}
		
		void draw() {
			if(drawable!=NULL) {
				//ofVec2f p = getAbsolutePosition();
				//glPushMatrix();
				//glTranslatef(-p.x, -p.y, 0);
				drawable->draw(x, y, width, height);
				//glPopMatrix();
			} else {
				ofNoFill();
				ofSetHexColor(0xFFFFFF);
				ofRect(*this);
				ofFill();
			}
		}
	};
}