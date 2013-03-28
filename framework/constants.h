/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * constants.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */
#pragma once

#include <string>

// this is your pixel width and height
extern int WIDTH;
extern int HEIGHT;

// these are HEIGHT/320 and WIDTH/480 respectively
extern float HEIGHT_SCALE;
extern float WIDTH_SCALE;

// this is true if it's an iphone4 (not iphone3 or iPad)
extern bool RETINA;

// this is true only on iPad
extern bool IPAD;

// this is if it's an iPad or an iphone4 (retina)
extern bool HI_RES;

extern bool HAS_CAMERA;
// this is where you get your resolution dependent images from.
// it will get initialized to point to images/ or images4/ depending 
// on whether you're HI_RES or not. If it's an iPad or iPhone4, the images
// need to be 2x as big (well 2x2 times as big, hence the 4
extern std::string IMAGE_ROOT;

extern std::string APP_NAME;

#define HOST "localhost"
#define PORT 12345

extern bool FAKE_GAME_MODE;


//---------------------------------------------------------------------------------------------
// FIXMEs / TODOs / NOTE macros
//---------------------------------------------------------------------------------------------
#define _QUOTE(x) # x
#define QUOTE(x) _QUOTE(x)
#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "

#define NOTE( x )  message( x )
#define FILE_LINE  message( __FILE__LINE__ )

#define TODO( x )  message( __FILE__LINE__"\n"           \
" ------------------------------------------------\n" \
"|  TODO :   " #x "\n" \
" -------------------------------------------------\n" )
#define FIXME( x )  message(  __FILE__LINE__"\n"           \
" ------------------------------------------------\n" \
"|  FIXME :  " #x "\n" \
" -------------------------------------------------\n" )
#define todo( x )  message( __FILE__LINE__" TODO :   " #x "\n" )
#define fixme( x )  message( __FILE__LINE__" FIXME:   " #x "\n" )
