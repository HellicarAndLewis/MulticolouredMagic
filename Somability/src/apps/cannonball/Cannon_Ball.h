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
 *  Cannon_Ball.h, created by Marek Bereza on 11/06/2012.
 */




namespace cannon {
	
	class Ball: public ofVec2f {
	public:
		
		ofVec2f vel;
		float radius;
		bool colliding;
		
		void setup() {
			colliding = false;
			radius = ofRandom(10, 25);
			x = ofGetWidth()/2 + ofRandom(-ofGetWidth()/4, ofGetWidth()/4);
			y = ofGetHeight()/2 + ofRandom(-ofGetHeight()/4, ofGetHeight()/4);
			vel = ofVec2f(15, 0);
		}
		
		void update() {
			*this += vel;
			if(x>ofGetWidth()-radius && vel.x>0) {
				vel.x *= -1;
			} else if(x<radius && vel.x<0) {
				vel.x *= -1;
			}
			
			if(y>ofGetHeight()-radius && vel.y>0) {
				vel.y *= -1;
			} else if(y<radius && vel.y<0) {
				vel.y *= -1;
			}		
		}
		
		bool doCollision(ofPoint &a, ofPoint &b) {
			//	if(y<a.y) return;
			float d = pointLineDistance(a,b, *this);
			if(d<radius) {
				
				
				
				// wall normal
				ofVec2f wallNormal = a - b;
				wallNormal.set(-wallNormal.y, wallNormal.x);
				
				resolveFixedCollision(wallNormal);
				colliding = true;
			} else {
				colliding = false;
			}
			return colliding;
		}
		
		void resolveFixedCollision(ofVec2f &wallNormal) {
			ofVec2f c = componentVector(vel, wallNormal) * 2;
			ofVec2f v = vel - c;
			vel.x = v.x;
			vel.y = v.y;
		}
		
		
		ofVec2f componentVector(ofVec2f &vec, ofVec2f &dir) {
			ofVec2f v(dir.x, dir.y);
			v.normalize();
			v *= vec.dot(v);
			return v;
		}
		
		float pointLineDistance(ofVec2f a, ofVec2f b, ofVec2f p) {
			
			// from http://www.softsurfer.com/Archive/algorithm_0102/algorithm_0102.htm#Distance to 2-Point Line
			return abs(((a.y - b.y)*p.x + (b.x - a.x)*p.y + (a.x*b.y - b.x*a.y))/
					   sqrt((b.x-a.x)*(b.x-a.x) + (b.y - a.y)*(b.y - a.y))
					   );
		}
		
		
		void draw() {
			ofFill();
			if(colliding) {
				glColor4f(1, 0, 0, 1);
			} else {
				ofSetColor(200, 200, 255);
			}
			
			ofEllipse(x, y, radius*2, radius*2);
		}
	};
	
};