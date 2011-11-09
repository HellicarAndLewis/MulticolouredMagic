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
	
	aboutContent.setup(ofVec2f(20, 50), IMAGE_ROOT + "aboutContent.png");
	videoButton.setup("video", ofVec2f(787, 241), IMAGE_ROOT + "video.png");
	videoButton.y = 201;
	videoButton.setListener(this);
	
	
	twitterButton.setup("twitter",ofVec2f(32+45+59, 32+473+16+65), IMAGE_ROOT+"twitter.png");
	vimeoButton.setup("vimeo",ofVec2f(119+32+89, 473+32+16+65), IMAGE_ROOT+"vimeo.png");
	flickrButton.setup("flickr",ofVec2f(195+32+117, 32+473+16+65), IMAGE_ROOT+"flickr.png");
	reacticklesLink.setup("reactickles", ofVec2f(), "");
	reacticklesLink.x = 99;
	reacticklesLink.y = 448+72;
	reacticklesLink.width = 112;
	reacticklesLink.height = 20;
	
	
	add(bgImage);
	add(logo);
	add(videoButton);		videoButton.setListener(this); 
	add(aboutContent);		
	add(vimeoButton);		vimeoButton.setListener(this);
	add(twitterButton);		twitterButton.setListener(this);
	add(flickrButton);		flickrButton.setListener(this);
	add(reacticklesLink);	reacticklesLink.setListener(this);
	
}
#ifdef TARGET_OF_IPHONE
void ofxiPhoneLaunchBrowser(string url) {
	
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:ofxStringToNSString(url)]];
}
#endif
void AboutPage::buttonPressed(string name) {
	if(name=="video") {
		launchUrl("http://vimeo.com/user1978699");
	} else if(name=="vimeo") {
		launchUrl("http://vimeo.com/user1978699");
	} else if(name=="reactickles") {
		launchUrl("http://reactickles.org/");
	} else if(name=="flickr") {
		launchUrl("http://www.flickr.com/photos/reactickles/");
	} else if(name=="twitter") {
		launchUrl("http://twitter.com/reactickle");
	}
	

}


void AboutPage::draw() {
	Reactickle::draw();
//	ofNoFill();
//	ofSetHexColor(0xFFFFFF);
//	ofRect(reacticklesLink);
//	ofFill();
}