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
