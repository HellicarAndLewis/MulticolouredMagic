/**
 * Listener.h
 * emptyExample
 *
 * Created by Marek Bereza on 27/06/2011.
 *
 */
#pragma once
#include "Control.h"
#include "Event.h"


namespace xmlgui {
	class Listener {
	public:
		virtual void controlChanged(Event *e) = 0;
	};
};