/* ------------------------------------------------------------------------- */
/*  ofxMultiTouchPad.cpp                                                     */
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

#include "ofxMultiTouchPad.h"

int ofxMultiTouchPad::_guard = 0;
const int ofxMultiTouchPad::maxTouches = _NUM_TOUCH_FINGERS;


static int _mt_callback(int device, Finger *data, int nFingers,
                        double timestamp, int frame)
{
    memcpy(_touches, data, nFingers * sizeof(Finger));
    fingerCount = nFingers;
    
    memcpy(touchEvent.touches, data, nFingers * sizeof(Finger));
    touchEvent.count = nFingers;
    touchEvent.timestamp = timestamp;
    touchEvent.frame = frame;
    touchEvent.device = device;
    ofNotifyEvent(MTUpdateBlock, touchEvent);
    
    return 0;
}


ofxMultiTouchPad::ofxMultiTouchPad()
{
    _guard++;
    if (_guard==1) {
        printf("Creating Multitouch device\n");
        _mt_device = MTDeviceCreateDefault();
        MTRegisterContactFrameCallback(_mt_device, _mt_callback);
        MTDeviceStart(_mt_device, 0);
    }
    else {
        printf("there's another instance already created,"
               "we must not init the device\n");
    }
    ofAddListener(MTUpdateBlock, this,
                  &ofxMultiTouchPad::callBackTriggered);
    MTUpdateBlock.enable();
    
    this->fingers = &_touches;
    this->_fingerCount = &fingerCount;
}

ofxMultiTouchPad::~ofxMultiTouchPad()
{
    _guard--;
    if (_guard==0) {
        printf("Multitouch device has been disconnected\n");
        MTDeviceStop(_mt_device);
        MTUnregisterContactFrameCallback(_mt_device, _mt_callback);
        MTDeviceRelease(_mt_device);
        _mt_device = NULL;
    }
    ofRemoveListener(MTUpdateBlock, this,
                     &ofxMultiTouchPad::callBackTriggered);
    
    this->fingers = NULL;
    this->_fingerCount = NULL;
}

bool ofxMultiTouchPad::getTouchAt(int pos, MTouch* touch)
{
    MTouch _t;
    if (pos < _touchData.count) {
        Finger f = _touchData.touches[pos];
        _t.ID = f.identifier;
        _t.frame = f.frame;
        _t.x = f.normalized.pos.x;
        _t.y = 1.f-f.normalized.pos.y;
        
        /*
         FIXME: this only makes sense, when the size is big enough,
                otherwise we have too much jitter...
         */
        _t.angle = 180 - (f.angle * 90 / atan2(1,0));
        
        _t.size = f.size;
        *touch = _t;
        return true;
    }
    else {
        *touch = _t;
        return false;
    }
}

bool ofxMultiTouchPad::getTouchAsOfPointAt(int pos, ofPoint* p)
{
    ofPoint _t(0,0,0);
    if (pos < _touchData.count) {
        Finger f = _touchData.touches[pos];
        _t.x = f.normalized.pos.x;
        _t.y = 1.f-f.normalized.pos.y;
        *p = _t;
        return true;
    }
    else {
        *p = _t;
        return false;
    }
}

int ofxMultiTouchPad::getTouchCount()
{
//    int e;
//    if (_fingerCount==NULL) {
//        e = -1;
//    } else {
//        e = *_fingerCount;
//    }
    return _touchData.count;
}

void ofxMultiTouchPad::getTouchesAsOfPoints(std::vector<ofPoint> * pointv){
    pointv->erase(pointv->begin(),pointv->begin()+pointv->size());
    TouchFrame _data = _touchData;
    for (int i=0; i<_data.count; i++)
        pointv->push_back(ofPoint(_data.touches[i].normalized.pos.x,
                                  1-_data.touches[i].normalized.pos.y, 0));
}



// ------------------------------------------------------------- protected
void ofxMultiTouchPad::callBackTriggered(TouchFrame  & _t)
{
	int oldTouchCount = _touchData.count;
	
	
    if (_touchData.count < _t.count) {
		
		int newTouchPos = -1;
		// loop through the new touches
		for(int i = 0; i < _t.count; i++) {
			// find each of them in the old touches
			bool foundTouch = false;
			for(int j = 0; j < _touchData.count; j++) {
				if(_touchData.touches[j].identifier==_t.touches[i].identifier) {
					foundTouch = true;
					break;
				}
			}
			if(!foundTouch) {
				newTouchPos = i;
			}
		}
		/*
         TODO: extract the new touch and pass its ID
         */
		_touchData = _t;
		MTouch touch;
		getTouchAt(newTouchPos, &touch);
        ofNotifyEvent(touchAdded, touch, this);
    } else if (_touchData.count > _t.count) {
		
		int removedTouchPos = -1;
		// loop through the old touches
		for(int i = 0; i < _touchData.count; i++) {
			// find each of them in the new touches
			bool foundTouch = false;
			for(int j = 0; j < _t.count; j++) {
				if(_touchData.touches[i].identifier==_t.touches[j].identifier) {
					foundTouch = true;
					break;
				}
			}
			if(!foundTouch) {
				
				removedTouchPos = i;
				int removedTouchId = _touchData.touches[removedTouchPos].identifier;
				ofNotifyEvent(touchRemoved, removedTouchId, this);
			}
		}
		
		_touchData = _t;

    } else {
		_touchData = _t;
		ofNotifyEvent(update, _touchData.count, this);
	}
}