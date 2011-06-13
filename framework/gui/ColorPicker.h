/**
 * SomanticsColorPicker.h
 * SomanticsMac
 *
 * Created by Marek Bereza on 11/05/2011.
 *
 */
#pragma once
#define NUM_PICKER_COLORS 21
#include "ImageCache.h"
#include "Container.h"
#include "constants.h"
#include "ColorCube.h"
#include "Settings.h"
#include "GlowingBorder.h"
#include "ImageObject.h"

class ColorPicker: public Container, public ColorCubeListener {
public:
	ofImage *cross;
	ColorPicker() ;
	
	GlowingBorder glowingBorder;
	void setup() ;
	void reset() ;
	
	void selectFg(int index) ;
	
	void selectBg(int index) ;
	
	void cubePressed(ColorCube *cube) ;
	ColorCube **fgs;
	ColorCube **bgs;
	ImageObject bgTitle;
	ImageObject fgTitle;
	
	ColorCube fg;
	ColorCube bg;
};
