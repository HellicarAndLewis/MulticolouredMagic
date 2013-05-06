/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "Sparticles.h"
#include "Settings.h"

#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif

Sparticles::Sparticles(){

	pos = 0;
    maxAge = 50;
    numParticles = 500;
    positions = new ofVec2f[numParticles];
    velocities = new ofVec2f[numParticles];
    ages = new int[numParticles];
    sizes = new float[numParticles];

    for(int i = 0; i < numParticles; i++) {
        positions[i] = ofVec2f(-10, -10);
        velocities[i] = ofVec2f(0, 0);
        ages[i] = maxAge;
		sizes[i] = ofRandom(5, 26);
    }


}

void Sparticles::setup() {

	vector<string> imgs;
	imgs.push_back("img/particles/blob.png");
	imgs.push_back("img/particles/glitter.png");
	imgs.push_back("img/particles/sparkle.png");
	imgs.push_back("img/particles/star.png");
	for(int i = 0; i < imgs.size(); i++) {
		images.push_back(ofImage());
		images.back().loadImage(imgs[i]);
		images.back().setAnchorPercent(0.5, 0.5);
	}
}


Sparticles::~Sparticles(){
    delete [] positions;
    delete [] velocities;
    delete [] ages;
	delete [] sizes;
}


void Sparticles::update(){
    for(int i = 0; i < numParticles; i++) {
        ages[i]++;
        positions[i] += velocities[i];
    }
}

void Sparticles::draw(bool multicoloured){


	int colorIndex = Settings::getInstance()->settings["fgColor"];
	ofColor c;
	if(colorIndex!=20) {
		c = ofColor::fromHex(ColorPicker::colors[colorIndex]);
	}
    for(int i = 0; i < numParticles; i++) {
        if(ages[i]<maxAge) {
            float size = ofMap(ages[i], 0, maxAge, sizes[i], 0);

			//            if (particleDisplayMode == 2){
			//            ofTranslate(1, 1, -size);
			//            }
			//            else {
			//             ofTranslate(1, 1, 1);
			//            }
            //ofTranslate(1, 1, ages[i]/10); ///moves them in 3D
            if(colorIndex==20) {
				c.setHex(ColorPicker::colors[i%7]);
			}
				ofSetColor(c.r, c.g, c.b, ofMap(ages[i], 0, maxAge, 255, 0));

            //ofCircle(positions[i].x - size/2, positions[i].y - size/2, size);
			if(ofRandom(0, 1)>0.96) {
				int r = 1+rand()%(images.size()-1);
				images[r].draw(positions[i].x, positions[i].y, size, size);
			} else {
				images[0].draw(positions[i].x, positions[i].y, size, size);
			}
//            ofRect(positions[i].x - size/2, positions[i].y - size/2, size, size);
        }
    }

}

void Sparticles::spawn(float x, float y, float dx, float dy){
    ages[pos] = 0;
    positions[pos] = ofVec2f(x, y);
    velocities[pos] = ofVec2f(dx, dy);

    pos++;
    pos %= numParticles;
}
