/**
 * AboutPage.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "Reactickle.h"
#include "ofxiPhoneWebView.h"
class AboutPage: public Reactickle {
public:
	void start() {
		webView.show();
		printf("Shwoing web view\n");
	}
	ofxiPhoneWebView webView;
};