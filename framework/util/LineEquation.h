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
 *  LineEquation.h, created by Marek Bereza on 11/06/2012.
 */

class LineEquation {
public:
	
	float m;
	float c;
	
	
	void setFrom2Points(ofPoint a, ofPoint b) {
		ofPoint g = b - a;
		float m = g.y / g.x;
		
		// y = mx + c		
		// so c = y - mx
		float c = a.y - m*a.x;
		
		
		set(m, c);
	}
	
	void setFrom2Points(ofVec2f a, ofVec2f b) {
		ofVec2f g = b - a;
		float m = g.y / g.x;
		
		// y = mx + c		
		// so c = y - mx
		float c = a.y - m*a.x;
		
		
		set(m, c);
	}
	
	
	void set(float m, float c) {
		this->m = m;
		this->c = c;
	}
	
	float getY(float x) {
		return m*x + c;
	}
	
	float getX(float y) {
		return (y-c)/m;
	}
};


