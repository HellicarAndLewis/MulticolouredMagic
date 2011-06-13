/**
 * AboutPage.mm
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "AboutPage.h"
#ifdef TARGET_OF_IPHONE
#include "ofxiPhoneExtras.h"
#endif
void AboutPage::start() {
	if(IPAD) {
		bgImage.setup(ofVec2f(), "img/bgIPad.png");
	} else if(HI_RES) {
		bgImage.setup(ofVec2f(), "img/bgIPhone4.png");
	} else {
		bgImage.setup(ofVec2f(), "img/bgIPhone.png");
	}
	
	
	logo.setup(ofVec2f(), IMAGE_ROOT + "logo.png");
	logo.x = WIDTH/2 - logo.width/2;
	logo.y = 35;
	
	aboutContent.setup(ofVec2f(0, 200), IMAGE_ROOT + "aboutContent.png");
	youtubeButton.setup("youtube", ofVec2f(587, 441), IMAGE_ROOT + "youtube.png", "youtubeDown.png");
	youtubeButton.y = 441;
	youtubeButton.setListener(this);
	add(bgImage);
	add(logo);
	add(aboutContent);
	add(youtubeButton);
	
}
#ifdef TARGET_OF_IPHONE
void ofxiPhoneLaunchBrowser(string url) {
	
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:ofxStringToNSString(url)]];
}
#endif
void AboutPage::buttonPressed(string name) {
	if(name=="youtube") {
#ifdef TARGET_OF_IPHONE
		ofxiPhoneLaunchBrowser("http://www.youtube.com/watch?v=nKfj7SfV9sI");
#else
		ofLaunchBrowser("http://www.youtube.com/watch?v=nKfj7SfV9sI");
#endif
	}
}
