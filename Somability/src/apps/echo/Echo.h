//
//  Echo.h
//  Somability
//
//  Created by Marek Bereza on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_Echo_h
#define Somability_Echo_h


#include "ofMain.h"
#include "Reactickle.h"

class Echo: public Reactickle {
public:
	~Echo();
	virtual void start();
	virtual void stop();


	virtual void update();
	void draw();
	virtual bool needsKinect() { return true; }
private:
	vector<unsigned char*> frames;
	int					DELAY_SIZE;
	int					currFrame;
	unsigned char *		output;
	ofImage				display;

};


#endif
