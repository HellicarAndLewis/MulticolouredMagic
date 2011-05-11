/**
 * SomanticsColorPicker.h
 * SomanticsMac
 *
 * Created by Marek Bereza on 11/05/2011.
 *
 */
#pragma once
#define NUM_PICKER_COLORS 21

#include "Container.h"
#include "ColorCube.h"

class SomanticsColorPicker: public Container {
public:
	SomanticsColorPicker() {
		int colors[NUM_PICKER_COLORS] = {
			0x4D1965,
			0xE50043,
			0x0E2356,
			0x74AF27,
			0xFFEC00,
			0xED6B06,
			0x6D1B00,
			
			0xA80F79,
			0xE7378C,
			0x0070BA,
			0xC0D886,
			0xF0E500,
			0xF0856A,
			0xE42313,
			
			0xF1DCED,
			0xF6B6CB,
			0xBDE3F2,
			0xF9F3B2,
			0xFFFADE,
			0xF8E7E2,
			0xFBE0EE
		};

		
		for(int i = 0; i < NUM_PICKER_COLORS; i++) {
			ColorCube *c = new ColorCube();
			c->setup(colors[i]);
			
		}
		
	}
};