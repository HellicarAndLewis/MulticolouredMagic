/**
 *  ConvexHull.cpp
 *
 *  Created by Marek Bereza on 15/08/2011.
 */

#include "contourutils.h"

// taken from http://code.google.com/p/julapy/source/browse/trunk/openframeworks/bom/bom_main/src/addons/ofxContourUtil/libs/convexHull.h?r=928
// Implementation of Monotone Chain Convex Hull algorithm.
#include <algorithm>
#include <float.h>


bool ofVec2flt(const ofVec2f &a, const ofVec2f &b) {
	return a.x < b.x || (a.x==b.x && a.y < b.y);
}



// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
static float ofVec2fcross(const ofVec2f &O, const ofVec2f &A, const ofVec2f &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
void tricks::math::calcConvexHull(vector<ofVec2f> &P, vector<ofVec2f> &H)
{
	int n = P.size(), k = 0;
	H.resize(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end(), &ofVec2flt);

	// Build lower hull
	for (int i = 0; i < n; i++) {
		while (k >= 2 && ofVec2fcross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && ofVec2fcross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k);
}


void tricks::math::offsetContour(vector<ofVec2f> &input, vector<ofVec2f> &output, float amount) {
	output.resize(input.size());
	for(int i = 0; i < input.size(); i++) {
		ofVec2f perp = (input[(i+1)%input.size()] - input[i]).perpendicular();
		if(perp.x==0 && perp.y==0) {
			if(i>0) {
				output[i] = output[i-1];
				continue;
			}
		} else {
			perp *= -amount;
			output[i] = input[i] + perp;
		}
	}
}

void tricks::math::fillContour(vector<ofVec2f> &contour, float maxPointDist) {
	if(maxPointDist<1) {
		printf("fillContour Error: maxPointDist must be bigger than 1\n");
		return;
	}










	// printf("contourSize: %d, maxPointDist: %f\n", contour.size(), maxPointDist);

	for(int i = 0; i < contour.size(); i++) {

		ofVec2f length = contour[(i+1)%contour.size()] - contour[i];

		float distanceToNextPoint = length.length();
		if(distanceToNextPoint>0) {



			// if the distance is too far
			if(distanceToNextPoint>maxPointDist) {

				// normalized direction vector
				ofVec2f direction = length/distanceToNextPoint;

				float numberOfPointsToInsert = distanceToNextPoint / maxPointDist;



				vector<ofVec2f> newPoints;

				for(int j = 1; j < numberOfPointsToInsert; j++) {
					ofVec2f point = contour[i] + direction * maxPointDist * (float)j;
					newPoints.push_back(point);
				}
				contour.insert(contour.begin()+i+1, newPoints.begin(), newPoints.end());
				i += newPoints.size();


			}
		}
	}
}

/**
 * This finds the furthest point in "points" from "point" and
 * returns its index in "points"
 */
int tricks::math:: findFurthestPointFromPoint(vector<ofVec2f> &points, ofVec2f &point) {
	float maxDistSqr = 0;
	int maxI = -1;
	for(int i = 0; i < points.size(); i++) {
		float distSqr = points[i].distanceSquared(point);
		if(distSqr>maxDistSqr) {
			maxDistSqr = distSqr;
			maxI = i;
		}
	}
	return maxI;
}

/**
 * this gets a normal non-angle-aligned bounding box for a set of points
 * or a contour.
 */
ofRectangle tricks::math::getBoundingBox(vector<ofVec2f> &contour) {
	ofVec2f minP(FLT_MAX, FLT_MAX);
	ofVec2f maxP(FLT_MIN, FLT_MIN);
	for(int i = 0; i < contour.size(); i++) {
		if(contour[i].x>maxP.x) maxP.x = contour[i].x;
		if(contour[i].y>maxP.y) maxP.y = contour[i].y;
		if(contour[i].x<minP.x) minP.x = contour[i].x;
		if(contour[i].y<minP.y) minP.y = contour[i].y;
	}

	return ofRectangle(minP.x, minP.y, maxP.x - minP.x, maxP.y - minP.y);
}



//--------------------------------------------------
bool tricks::math::pointInsidePolygon(ofVec2f &p, const vector<ofVec2f> &polygon){
	int counter = 0;
	int i;
	double xinters;
	ofVec2f p1,p2;

	float x = p.x;
	float y = p.y;

	int N = polygon.size();

	p1 = polygon[0];
	for (i=1;i<=N;i++) {
		p2 = polygon[i % N];
		if (y > MIN(p1.y,p2.y)) {
			if (y <= MAX(p1.y,p2.y)) {
				if (x <= MAX(p1.x,p2.x)) {
					if (p1.y != p2.y) {
						xinters = (y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
						if (p1.x == p2.x || x <= xinters)
							counter++;
					}
				}
			}
		}
		p1 = p2;
	}

	if (counter % 2 == 0) return false;
	else return true;
}

