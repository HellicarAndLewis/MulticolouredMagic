#include "Painter.h"
#include "constants.h"

// increment and wrap the current colour
void Painter::nextColour() {
	colourIndex++;
	if(colourIndex>=NUM_PAINTER_COLOURS) colourIndex = 0;
}
//--------------------------------------------------------------
void Painter::setup(){
	
	// add all the colours to the list
	colourIndex = 0;
	colours[0] = ofColor(255, 0, 0);
	colours[1] = ofColor(255, 255, 0);
	colours[2] = ofColor(0, 255, 255);
	colours[3] = ofColor(0, 255, 0);
	colours[4] = ofColor(0, 0, 255);
	

	
	
#ifndef TARGET_IPHONE_SIMULATOR
	
	// set up the camera
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	
	// initialize all the cv images
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	canvas.allocate(320, 240);
	canvas.set(0);
#endif
	// set the vision parameters - we'll need to tweak these
	threshold = 80;
	amount = 0.5;
}

//--------------------------------------------------------------
void Painter::update(){

    bool bNewFrame = false;

#ifndef TARGET_IPHONE_SIMULATOR
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    
	if (bNewFrame){


		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	  
        grayImage = colorImg;
		

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
		
		
		
		
		// if there are no massive blobs, add the grayDiff to the canvas
		bool updateCanvas = true;
		/*for(int i = 0; i < contourFinder.nBlobs; i++) {
			if(contourFinder.blobs[i].boundingRect.width>colorImg.width/4) updateCanvas = false;
		}*/
		
		
		if(updateCanvas) {
			
			
			// loop through pixels 
			//  - add new colour pixels into canvas
			unsigned char *canvasPixels = canvas.getPixels();
			unsigned char *diffPixels = grayDiff.getPixels();
			int r = colours[colourIndex].r;
			int g = colours[colourIndex].g;
			int b = colours[colourIndex].b;
			int matchCount = 0;
			for(int i = 0; i < canvas.width*canvas.height; i++) {
				if(diffPixels[i]) {
					canvasPixels[i*3] = r;
					canvasPixels[i*3+1] = g;
					canvasPixels[i*3+2] = b;
				}
				if(canvasPixels[i*3]==r && canvasPixels[i*3+1]==g && canvasPixels[i*3+2]==b) {
					matchCount++;
				}
			}
			
			float totalCount = canvas.width*canvas.height;
			float proportionOfMatchedPixels = (float)matchCount/totalCount;
		//	printf("Match count: %f%%\n", proportionOfMatchedPixels*100.f);
			if(proportionOfMatchedPixels>.5) {
				// change colour
				nextColour();
			}
			//canvas += grayDiff;
			canvas.blur();
		}
		
		
		grayBg.convertToRange(0, 255.f*(1.f - amount));
		grayImage.convertToRange(0, 255.f*(amount));
		
		// grayBg = grayBg * 0.9 + grayImage * 0.1
		grayBg += grayImage;
	}
#endif
}

//--------------------------------------------------------------
void Painter::draw() {
#ifndef TARGET_IPHONE_SIMULATOR
	ofSetHexColor(0xFFFFFF);
	canvas.draw(0,0,WIDTH, HEIGHT);
#endif
}





bool Painter::touchDown(float x, float y, int touchId) {
	return false;
}


bool Painter::touchUp(float x, float y, int touchId) {
	return false;
}

bool Painter::touchMoved(float x, float y, int touchId) {
	return false;
}

