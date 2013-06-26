/**
 *  RingDrawer.cpp
 *
 *  Created by Marek Bereza on 26/06/2013.
 */

#include "RingDrawer.h"


vector<ofVec2f> RingDrawer::unitCircle;


void RingDrawer::drawRing(ofVec2f centre, float radius, float amount, float innerRadius, int bgColor) {
	createUnitCircleIfNecessary();
	glPushMatrix();
	glTranslatef(centre.x, centre.y, 0);
	glScalef(radius*0.98, radius*0.98, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(ofVec2f), &unitCircle[0].x);
	int num = ofMap(amount, 0, 1, 0, unitCircle.size(), true);
	glDrawArrays(GL_TRIANGLE_FAN, 0, num);
	ofSetHexColor(bgColor);
	ofCircle(0, 0, innerRadius*0.98/radius);
	glPopMatrix();
}


void RingDrawer::createUnitCircleIfNecessary() {
	if(unitCircle.size()>0) return;
	unitCircle.push_back(ofVec2f());
	for(int i = 0; i <= 360; i++) {
		float angle = ofMap(i, 0, 360, 0, PI*2);
		unitCircle.push_back(ofVec2f(cos(angle), sin(angle)));
	}
	
}