/**
 *  Parameterized.cpp
 *
 *  Created by Marek Bereza on 22/11/2012.
 */

#include "Parameterized.h"
#include "ParameterizedGui.h"

void xmlgui::Parameterized::save() {
	parent->save(this);
}