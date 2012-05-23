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
 *  Pendule.h, created by Marek Bereza on 23/05/2012.
 */


#include "Spring.h"

class Pendule {
public:
	vector<Spring> springs;
	Pendule(float x = 0, float y = 0) {
		
		for(int i = 0; i < 5; i++) {
			springs.push_back(Spring(x, y));
		}
	}
	
	void setTarget(ofVec2f target) {
		this->target = target;
	}
	void draw() {
		ofSetHexColor(0xFF00FF);
		glLineWidth(20);
		ofNoFill();
		ofBeginShape();
		for(int i = 0; i < springs.size(); i++) {
			//springs.get(i).draw();
			if(i==0||i==springs.size()-1) ofCurveVertex(springs[i].p.x, springs[i].p.y);
				ofCurveVertex(springs[i].p.x, springs[i].p.y);
				
				}
		ofEndShape();
		glLineWidth(1);
		ofFill();
	}
	void update() {
		for(int i = 0; i < springs.size(); i++) {
			if(i==0) {
				springs[i].p = target;
			} else {
				springs[i].p = springs[i-1].r;
			}
			
			springs[i].update(); 
		}
	}
	ofVec2f target;
};