//
//  Mirror.cpp
//  SomanticsMac
//
//  Created by Marek Bereza on 11/07/2011.
//  Copyright 2011 MAZBOX LTD. All rights reserved.
//

#include "Mirror.h"
#include "constants.h"
#include <Accelerate/Accelerate.h>

#define VISION_WIDTH  640
#define VISION_HEIGHT 480



Mirror::Mirror(int type) {
	this->type = type;
	buffer = NULL;
}

Mirror::~Mirror() {
	if(buffer!=NULL) delete [] buffer;
}


void Mirror::setup() {
	
	star = 2;
	offset = 0.5;
	slitScanPos = 0;
	
	if(buffer==NULL) {
		buffer = new unsigned char[VISION_WIDTH*VISION_HEIGHT*3];
		memset(buffer, 0, VISION_WIDTH*VISION_HEIGHT*3);
	}
	image.allocate(VISION_WIDTH, VISION_HEIGHT);
	
	image.set(0);
	
}



int Mirror::ratio(int l, int r, float ratio) {
	float f = ((float)l)*ratio + ((float)r)*(1.f - ratio);
	return (int) f;
}

int slitScanPos = 0;


void Mirror::update() {
	if(colorImg!=NULL) {

		image.scaleIntoMe(*colorImg);
		
		int numPixels = image.getWidth()*image.getHeight()*3;
		unsigned char *pixels = image.getPixels();
		if(type==MIRROR_AMBIENT_LAPSE) {
			
			// blend previous frames
			float feedback = 0.05;
			float ff = 0.03*255;
			int f = ff;
			int mf = 255 - f;
			for (int i = 0; i < numPixels; i++) { // For each pixel in the video frame...
				buffer[i] = (pixels[i]*f + buffer[i]*mf)/256;
//				pixels[i] = ratio(pixels[i], buffer[i], feedback);
				//buffer[i] = pixels[i];
			}
			//memcpy(buffer, pixels, numPixels);
		} else if(type==MIRROR_SLITSCAN) {
			
			for(int i = 0; i < 2; i++) {
				// only copy one row of pixels
				int pixelsStart = slitScanPos*image.getWidth()*3;
				int numPixToCopy = image.getWidth()*3;
				
				memcpy(buffer + pixelsStart, pixels+pixelsStart, numPixToCopy);
				
				
				// increment and wrap the position
				slitScanPos++;
				if(slitScanPos>=image.getHeight()) slitScanPos = 0;
			}
			// then copy the whole buffer over
			memcpy(pixels, buffer, numPixels);
				
		}
		
		if(type==MIRROR_AMBIENT_LAPSE) {
			image.setFromPixels(buffer, image.getWidth(), image.getHeight());
		} else {
		
			image.setFromPixels(pixels, image.getWidth(), image.getHeight());
		}
		
		// because we're not calling draw() on the camera's image
		// when doing mirror, we need to explicitly update the 
		// texture on the video card.
		if(type==MIRROR_KALEIDOSCOPE) {
			image.updateTexture();
		}
		
		
	}
}


	


bool Mirror::touchDown(float x, float y, int touchId) {
	star = 2*(int)ofMap(x, 0, WIDTH, 1, 10);
	offset = ofMap(y, 0, HEIGHT, 0, 1);
	return true;
}

bool Mirror::touchUp(float x, float y, int touchId) {
	return false;
}

bool Mirror::touchMoved(float x, float y, int touchId) {
	return touchDown(x, y, touchId);
}

void Mirror::draw() {
	ofSetHexColor(0xFFFFFF);
	bool usingNormTexCoords = ofGetUsingNormalizedTexCoords();
	
	//image.draw(0, 0, WIDTH, HEIGHT);
	if(type==MIRROR_KALEIDOSCOPE) {
		// push normalized tex coords
		if(!usingNormTexCoords) {
			ofEnableNormalizedTexCoords();
		}
		
		image.getTextureReference().bind();
		
		
		
		
		
		
		
		
		
		
		
		
		
		if(star<=2) {
			ofMesh mesh;
			mesh.clear();
			mesh.addVertex(ofVec3f(0, 0));
			mesh.addVertex(ofVec3f(0, HEIGHT));
			mesh.addVertex(ofVec3f(WIDTH/2, 0));
			mesh.addVertex(ofVec3f(WIDTH/2, HEIGHT));
			mesh.addVertex(ofVec3f(WIDTH, 0));
			mesh.addVertex(ofVec3f(WIDTH, HEIGHT));
			
			
			mesh.addTexCoord(ofVec2f(0.25, 0.0));
			mesh.addTexCoord(ofVec2f(0.25, 1.0));
			mesh.addTexCoord(ofVec2f(0.75, 0.0));
			mesh.addTexCoord(ofVec2f(0.75, 1.0));
			mesh.addTexCoord(ofVec2f(0.25, 0.0));
			mesh.addTexCoord(ofVec2f(0.25, 1.0));
			
			mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
			mesh.draw();
		} else {
			
			float angle = 360.f/(float)star;
			
			
			
			ofMesh mesh;
			
			ofVec3f vec(0,0,0);
			mesh.addVertex(vec);
			vec.x += HEIGHT/2;
			
			for(int i = 0; i < star; i++) {
				mesh.addVertex(vec);
				vec.rotate(angle, ofVec3f(0,0,1));
			}
			
			// close the loop
			mesh.addVertex(vec);
			
			
			
			// now work out the texcoords
			/*			
			 __________________
			 |   \        /   |
			 |    \      /    |
			 |     \    /     |
			 |      \  /      |
			 |       \/       |
			 +----------------+
			 
			 A v shape out of the centre of the camera texture
			 */
			
			
			
			float realOffset = 0.5;
			// normalized distance from the centre (half the width of the above 'V')
			float dist = ABS((float)image.getHeight()*tan(ofDegToRad(angle)*0.5))/(float)image.getHeight();
			
			
			// the realOffset is where the (normalized) middle of the 'V' is on the x-axis
			realOffset = ofMap(offset, 0, 1, dist, 1-dist);
			
			
			// this is the point at the bottom of the triangle - our centre for the triangle fan
			mesh.addTexCoord(ofVec2f(realOffset, 1));
			
			
			ofVec2f ta(realOffset-dist, 0);
			ofVec2f tb(realOffset+dist, 0);
			for(int i = 0; i <= star; i++) {
				if(i%2==0) {
					mesh.addTexCoord(ta);
				} else {
					mesh.addTexCoord(tb);
				}
			}
			
			
			glPushMatrix();
			glTranslatef(WIDTH/2, HEIGHT/2, 0);
			mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
			mesh.draw();
			glPopMatrix();
		}
		
		
		
		
		
		image.getTextureReference().unbind();
		
		
		// pop normalized tex coords
		if(!usingNormTexCoords) {
			ofDisableNormalizedTexCoords();
		}
	} else {
		image.draw(0, 0, WIDTH, HEIGHT);
	}
}