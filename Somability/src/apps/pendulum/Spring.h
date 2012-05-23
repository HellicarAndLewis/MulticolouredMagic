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
 *  Spring.h, created by Marek Bereza on 23/05/2012.
 */



class Spring {
public:
	float restLength;
	ofVec2f p;
	ofVec2f r;
	ofVec2f g;
	ofVec2f f;
	ofVec2f d;
	
	Spring(float x = 0, float y = 0) {
		p.set(x, y);
		r.set(x, y);
		restLength = 1;
		g.set(0, 0.4);
		d.set(0.93, 0.9);
	}
	void draw() {
		ofFill();
		ofSetHexColor(0xFFFFFF);
		ofLine(p, r);
		ofCircle(p.x, p.y, 4);
		ofCircle(r.x, r.y, 4);
	}
	void update() {
		ofVec2f springForce = r - p;
		
		float len = springForce.length() - restLength;

		springForce.normalize();
		springForce *= len*0.01;
		
		f -= springForce;

		f += g;

		
		f *= d;
		r += f;
	}
};