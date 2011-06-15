/* ------------------------------------------------------------------------- */
/*  MTTypes.h                                                                */
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

#ifndef _MT_TYPES_
#define _MT_TYPES_

#include <mach/mach.h> 
#include <IOKit/IOKitLib.h> 
#include <CoreFoundation/CoreFoundation.h> 

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct { float x,y; } mtPoint;
    typedef struct { mtPoint pos,vel; } mtReadout;
    
    typedef struct {
        int frame;
        double timestamp;
        int identifier, state, foo3, foo4;
        mtReadout normalized;
        float size;
        int zero1;
        float angle, majorAxis, minorAxis; // ellipsoid
        mtReadout mm;
        int zero2[2];
        float unk2;
    } Finger;
    
    typedef int MTDeviceRef;
    typedef int (*MTContactCallbackFunction)(int,Finger*,int,double,int);
    
    MTDeviceRef MTDeviceCreateDefault();
    void MTRegisterContactFrameCallback(MTDeviceRef, MTContactCallbackFunction);
    void MTUnregisterContactFrameCallback(MTDeviceRef, MTContactCallbackFunction);
    void MTDeviceStart(MTDeviceRef, int);
    void MTDeviceStop(MTDeviceRef);
    void MTDeviceRelease(MTDeviceRef);
    
#ifdef __cplusplus
}
#endif
#endif
/*
 END types
 */

