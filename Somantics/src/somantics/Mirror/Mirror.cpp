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
	if(buffer==NULL) {
		buffer = new unsigned char[VISION_WIDTH*VISION_HEIGHT*3];
	}
	image.allocate(VISION_WIDTH, VISION_HEIGHT);
	
	slitScanPos = 0;
	
	// draw a triangle strip
	// 
	//			+--------+--------+
	//			|        |        |
	//			|        |        |
	//			|        |        |
	//			|        |        |
	//          +--------+--------+
	//
	mirror.clear();
	mirror.addVertex(ofVec3f(0, 0));
	mirror.addVertex(ofVec3f(0, HEIGHT));
	mirror.addVertex(ofVec3f(WIDTH/2, 0));
	mirror.addVertex(ofVec3f(WIDTH/2, HEIGHT));
	mirror.addVertex(ofVec3f(WIDTH, 0));
	mirror.addVertex(ofVec3f(WIDTH, HEIGHT));
	
	
	mirror.addTexCoord(ofVec2f(0.25, 0.0));
	mirror.addTexCoord(ofVec2f(0.25, 1.0));
	mirror.addTexCoord(ofVec2f(0.75, 0.0));
	mirror.addTexCoord(ofVec2f(0.75, 1.0));
	mirror.addTexCoord(ofVec2f(0.25, 0.0));
	mirror.addTexCoord(ofVec2f(0.25, 1.0));
	
	mirror.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	
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
			
			for(int i = 0; i < 3; i++) {
				// only copy one row of pixels
				int pixelsStart = slitScanPos*image.getWidth()*3;
				int numPixToCopy = image.getWidth()*3;
				
				memcpy(buffer + pixelsStart, pixels+pixelsStart, numPixToCopy);
				
				// then copy the whole buffer over
				memcpy(pixels, buffer, numPixels);
				
				// increment and wrap the position
				slitScanPos++;
				if(slitScanPos>=image.getHeight()) slitScanPos = 0;
			}
		}
		
		if(type==MIRROR_AMBIENT_LAPSE) {
			image.setFromPixels(buffer, image.getWidth(), image.getHeight());
		} else {
		
			image.setFromPixels(pixels, image.getWidth(), image.getHeight());
		}
		
		// because we're not calling draw() on the camera's image
		// when doing mirror, we need to explicitly update the 
		// texture on the video card.
		if(type==MIRROR_MIRROR) {
			image.updateTexture();
		}
		
		
	}
}

void Mirror::draw() {
	ofSetHexColor(0xFFFFFF);
	bool usingNormTexCoords = ofGetUsingNormalizedTexCoords();
	
	image.draw(0, 0, WIDTH, HEIGHT);
	if(type==MIRROR_MIRROR) {
		// push normalized tex coords
		if(!usingNormTexCoords) {
			ofEnableNormalizedTexCoords();
		}
		
		image.getTextureReference().bind();
		mirror.draw();
		image.getTextureReference().unbind();
		
		
		// pop normalized tex coords
		if(!usingNormTexCoords) {
			ofDisableNormalizedTexCoords();
		}
	} else {
		image.draw(0, 0, WIDTH, HEIGHT);
	}
}