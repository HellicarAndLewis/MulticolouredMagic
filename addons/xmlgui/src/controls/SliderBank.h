/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  SliderArray.h, created by Marek Bereza on 06/06/2012.
 */


#include "Control.h"

class SliderBank: public xmlgui::Control {
public:
	int numSliders;
	int bgColor;
	int fgColor;
	int borderColor;
	float min;
	float max;
	int lastSliderTouched;
	SliderBank(): Control() {
		lastSliderTouched = -1;
		numSliders = 1;
		value = new float[1];
		fgColor = 0xFF0000;
		bgColor = 0x555555;
		borderColor = 0xFFFFFF;
		width = 100;
		height = 20;
		min = 0;
		max = 1;
	}
	
	void draw() {
		setRGBA(bgColor);
		ofRect(x, y, width, height);
		
		float w = (float) width / (float) numSliders;
		
		setRGBA(fgColor);
		
		for(int i = 0; i < numSliders; i++) {
			float xx = x + w*i;
			float yy = ofMap(((float*)value)[i], min, max, height, 0);
			ofRect(xx, yy+y, w, height-yy);
		}
		
		setRGBA(borderColor);
		
		for(int i = 1; i < numSliders; i++) {
			float xx = x + w*i;
			ofLine(xx, y, xx, y+height);
		}
		ofNoFill();
		ofRect(*this);
		ofFill();
	}
	
	bool touchMoved(int _x, int _y, int touchId) {
		touchDown(_x, _y, touchId);
		return true;
	}
	bool touchDown(int _x, int _y, int touchId) {
		

		float val = 1 - (_y-y)/height;
		
		float w = width/ (float) numSliders;
		
		int offset = (int)((_x - x)/w);
		lastSliderTouched = offset;
		if(offset>=0 && offset<numSliders) {
			((float*)value)[offset] = val*(max-min) + min;
		}

		return true;
	}
	
	
};