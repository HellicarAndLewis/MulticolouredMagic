/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  contourutils.h, created by Marek Bereza on 15/08/2011.
 */

#pragma once
#include "ofMain.h"

namespace tricks {
	namespace math {

		/** 
		 * This creates a convex hull of the input contour.
		 */
		void calcConvexHull(vector<ofVec2f> &P, vector<ofVec2f> &H);
		
		/**
		 * This makes a border around a contour which is "amount" distance
		 * away from the contour. Doesn't work amazingly.
		 */
		void offsetContour(vector<ofVec2f> &input, vector<ofVec2f> &output, float amount);
		
		/**
		 * This makes sure there are points at least every maxPointDist around the contour
		 * i.e. filling in points in between 2 points that are quite far apart.
		 */
		void fillContour(vector<ofVec2f> &contour, float maxPointDist);


		/**
		 * This finds the furthest point in "points" from "point" and
		 * returns its index in "points"
		 */
		int findFurthestPointFromPoint(vector<ofVec2f> &points, ofVec2f &point);
			
		/**
		 * this gets a normal non-angle-aligned bounding box for a set of points
		 * or a contour.
		 */
		ofRectangle getBoundingBox(vector<ofVec2f> &contour);
		
		
		bool pointInsidePolygon(ofVec2f &p, const vector<ofVec2f> &polygon);		
	}
}
