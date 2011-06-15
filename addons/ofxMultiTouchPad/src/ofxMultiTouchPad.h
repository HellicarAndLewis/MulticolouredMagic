/* ------------------------------------------------------------------------- */
/*  ofxMultiTouchPad.h                                                       */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/*  Created by jens a. ewald on 26.10.09.                                    */
/*                                                                           */
/*  http://www.openFrameworks.cc                                             */
/*                                                                           */
/*  access the data from the multitouchtrackpad sensor as addon for OF       */
/*                                                                           */
/*  based on the code at http://steike.com/code/multitouch                   */
/*  & the puredata external by Hans-Christoph Steiner                        */
/*                                                                           */
/*                                                                           */
/*  Copyright (c) 2009 jens alexander ewald http://www.520at.net             */
/*  Copyright (c) 2009 Hans-Christoph Steiner                                */
/*  Copyright (c) 2008 Steike                                                */
/*                                                                           */
/*                                                                           */
/* This program is free software; you can redistribute it and/or             */
/* modify it under the terms of the GNU General Public License               */
/* as published by the Free Software Foundation; either version 3            */
/* of the License, or (at your option) any later version.                    */
/*                                                                           */
/* See file LICENSE for further informations on licensing terms.             */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with this program; if not, write to the Free Software Foundation,   */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA */
/*                                                                           */
/* ------------------------------------------------------------------------- */


/* IMPORTANT!
   You must include the MultitouchSupport.framework from:
   /System/Library/PrivateFrameworks/MultitouchSupport.framework
   in order to compile.
 */

#pragma once

#ifndef _OFX_MULTITOUCHPAD_
#define _OFX_MULTITOUCHPAD_

#include "ofMain.h"

/*
 * Check for Apple system & valid version
 */

#ifndef __APPLE_CC__
    #error -- THIS ONLY WORKS ON OSX & THE LATEST MACBOOKS WITH MULTITOUCHPAD!
#else
    #if (MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_5)
        #error -- This needs OS X 10.5 (Leopard) or higher!\n\t\tCheck SDK ... \
and add the MultitouchSupport.framework from the PrivateFrameworks folder
    #endif
#endif

/*
 FIXME: really needed?
 */
#define DEF_SINGLETON( NAME )    \
public:                        \
static NAME& instance()      \
{                            \
static NAME _instance;    \
return _instance;         \
}                            \
private:                       \
NAME();               \
NAME( const NAME& );

/*
 * the multitouch is global & unique, so we do it static.
 */

#include "MTTypes.h"

#define _NUM_TOUCH_FINGERS 16 // who has more then 16 fingers?

static Finger _touches[_NUM_TOUCH_FINGERS];
static int fingerCount;

static MTDeviceRef _mt_device;
static int _mt_callback(int device, Finger *data, int nFingers,
                        double timestamp, int frame);

/*
 define event types // simplified Finger type
 */
typedef struct MTouch {
    int ID,frame;
    float angle,size,x,y;
    MTouch(): ID(-1),frame(0),x(0),y(0),angle(0.f),size(0.f){}
} MTouch;

/*
 TODO: optimize the container to store timestamps, when a touch is added
 */
typedef struct TouchFrame {
    Finger touches[_NUM_TOUCH_FINGERS];
    int device,count,frame;
    double timestamp;
    TouchFrame(): count(0){};
} TouchFrame;

static TouchFrame touchEvent;
static ofEvent<TouchFrame> MTUpdateBlock;



/*
 The actual class
 
 maybe it's better to implement this as a singleton
 using the DEF_SINGLETON macro...
 
 TODO: implement method to return scaled (ofGetWidth/Height) result. Listener?
 */

class ofxMultiTouchPad {
    
public:
    ofEvent<int> update; // occurs each callback call and sends the touchCount
    ofEvent<MTouch> touchAdded; // if the number of touches increased
    ofEvent<int> touchRemoved;  // less touches as before
    
    static const int maxTouches;
    ofxMultiTouchPad();  // initialize and create a link to the device
    ~ofxMultiTouchPad(); // unlink the device
    
    bool getTouchAt(int pos, MTouch * touch);
    bool getTouchAsOfPointAt(int pos, ofPoint * p);
    int  getTouchCount();
    void getTouchesAsOfPoints(std::vector<ofPoint> * pointv);
    
protected:
    TouchFrame _touchData;
    static int _guard;
    void callBackTriggered(TouchFrame & _t); // callback callback
    
    /*
     deprecated ?
     */
    Finger (*fingers)[_NUM_TOUCH_FINGERS];
    int * _fingerCount;
};


#endif