/**
 * AboutPage.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "Reactickle.h"
#include "ImageCache.h"
#include "constants.h"
#include "ImageObject.h"
#include "SimpleButton.h"

class AboutPage: public Reactickle, public SimpleButtonListener {
public:
	void start() ;
	
	void buttonPressed(string name) ;
	
	ImageObject bgImage;
	ImageObject logo;
	ImageObject aboutContent;
	SimpleButton youtubeButton;
};
