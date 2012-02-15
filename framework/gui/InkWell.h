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
 *  InkWell.h, created by Marek Bereza on 20/09/2011.
 */


#include "InteractiveObject.h"
#include "constants.h"

class InkWell: public InteractiveObject {
public:
	ofImage *multiColour;
	ofImage *flatColour;
	ofImage *border;
	int c;
	void setColor(int c) {
		this->c = c;
	}
	void setup() {
		multiColour = ImageCache::getImage(IMAGE_ROOT + "multicoloured.png");
		flatColour = ImageCache::getImage(IMAGE_ROOT + "flatColour.png");
		border = ImageCache::getImage(IMAGE_ROOT + "bigSelector.png");
	}
	void draw() {
		if(c==0) {
			ofSetHexColor(0xFFFFFF);
			multiColour->draw(x, y);
		} else {
			ofSetHexColor(c);
			flatColour->draw(x, y);
		}
		ofSetHexColor(0xFFFFFF);
		border->draw(x, y);
	}
};