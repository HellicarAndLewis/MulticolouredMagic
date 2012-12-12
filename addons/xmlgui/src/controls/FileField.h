/**
 * FileField.h
 * emptyExample
 *
 * Created by Marek Bereza on 04/07/2011.
 *
 */


#include "LabeledControl.h"
#define FILE_ICON_WIDTH 20
class FileField: public LabeledControl {
public:
	
	FileField(): LabeledControl() {
		
		height = 20;
		width = 70;
		value = new string;
	}
	
		// round() not supported in vs2010
	float __round(float number) {
		return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
	}
	void draw() {
		
		ofSetColor(50, 50, 50);
		ofRect(x, y, width - FILE_ICON_WIDTH - 5, height);
		ofNoFill();
		ofRect(x, y, width - FILE_ICON_WIDTH - 5, height);
		ofFill();
		ofSetColor(255, 255, 255);
		ofRect(x + width - FILE_ICON_WIDTH, y+2, FILE_ICON_WIDTH/3, 2);
		ofRect(x + width - FILE_ICON_WIDTH, y+5, FILE_ICON_WIDTH, 12);
		
		
		if(focus && ((int)__round(ofGetElapsedTimef()*2.5))%2==0) {
			xmlgui::Resources::drawString(sval(value) + "|", x+3, y+14);
		} else {
			xmlgui::Resources::drawString(sval(value), x+3, y+14);
		}
		drawLabel(x+3, y);
		
		
	}
	bool touchDown(int x, int y, int id) {
		
		if(inside(x, y)) {
			
			if(x>width-FILE_ICON_WIDTH) { // this hit the file button
				ofFileDialogResult result = ofSystemLoadDialog();
				if(result.bSuccess) {
					sval(value) = result.filePath;
				}
			} else {
				parent->setKeyboardFocus(this);
			}
			
			return true;
		} else {
			return false;
		}
	}
	
	bool keyPressed(int key) {
		if(key>=32 && key<=126) { // if it's a printable char
			sval(value) += (char*)&key;
			return true;
		} else if((key==8 || key==127) && sval(value).size()>0) { // delete
			sval(value) = sval(value).erase(sval(value).size()-1);
			return true;
		} else if(key==10 || key==13) {
			// this is a return
			return true;
		}
		return false;
	}
	
	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Value", "value","textfield",value));
	}
	string valueToString() { return sval(value); }
	void valueFromString(string inp) { sval(value) = inp; }
};