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
#include "ofxBox2d.h"

class Pendule {
public:
	ofVec2f target;
	Pendule(float x = 0, float y = 0) {		
		target = ofVec2f(x, y);
	}
	void setup(ofxBox2d *box2d) {
		anchor.setup(box2d->getWorld(), target.x,target.y, 4);
		
		// first we add just a few circles
		for (int i=0; i<10; i++) {
			ofxBox2dCircle circle;
			circle.setPhysics(3.0, 0.53, 0.1);
			circle.setup(box2d->getWorld(), ofGetWidth()/2, 100+(i*20), 8);
			circles.push_back(circle);
		}
		
		// now connect each circle with a joint
		for (int i=0; i<circles.size(); i++) {
			
			ofxBox2dJoint joint;
			
			// if this is the first point connect to the top anchor.
			if(i == 0) {
				joint.setup(box2d->getWorld(), anchor.body, circles[i].body);		
			}
			else {
				joint.setup(box2d->getWorld(), circles[i-1].body, circles[i].body);
			}
			
			joint.setLength(20);
			joints.push_back(joint);
		}
		
		
	}
	void destroy() {
		anchor.destroy();
		
		
		for(int i = 0; i < joints.size(); i++) {
		//	joints[i].destroy();
		}
		for(int i = 0; i < circles.size(); i++) {
			circles[i].destroy();
		}
	}
	
	void setTarget(ofVec2f target) {
		anchor.setPosition(target);
		this->target = target;
	}
	
	ofVec2f getTarget() {
		return this->target;
	}
	
	void draw() {
		ofSetHexColor(0xf2ab01);
		anchor.draw();
		
		
		for(int i=0; i<circles.size(); i++) {
			ofFill();
			ofSetHexColor(0x01b1f2);
			circles[i].draw();
		}
		
		for(int i=0; i<joints.size(); i++) {
			ofSetHexColor(0x444342);
			joints[i].draw();
		}
	}
	
	ofxBox2dCircle					anchor;			  //	fixed anchor
	vector		<ofxBox2dCircle>	circles;		  //	default box2d circles
	vector		<ofxBox2dJoint>		joints;			  //	joints

};