#include <iostream>
#include "BackgroundSubtraction.h"

using namespace std;
using namespace cv;

BackgroundSubtraction::BackgroundSubtraction(){
	//create element for morphing
	elementErode = getStructuringElement(MORPH_RECT, Size(2, 2), Point(1,1));
	elementDilate = getStructuringElement(MORPH_RECT, Size(5, 5), Point(1,1));
}

BackgroundSubtraction::~BackgroundSubtraction(){

}

/*
 * 	@brief:
 * 		use background subtraction method to find the speaker
 * 		return the last detection location so that this is always
 * 		a detection result. (Background subtraction can make foreground
 * 		as background when one stays at a place too long)
 * */
Rect BackgroundSubtraction::runBgSub(Mat &frame, bool drawFlag){
	Rect tempRect;
	//update the background model
	pMOG2.operator()(frame, fgMaskMOG2);
	//bin img
	threshold(fgMaskMOG2, fgMaskMOG2Bin, THRESH_BINARY, 255, 0);
	//morphing
	erode(fgMaskMOG2Bin, fgMaskMOG2Erode, elementErode);
	dilate(fgMaskMOG2Erode, fgMaskMOG2Dilate, elementDilate);
	fgMaskMOG2Filled = fgMaskMOG2Dilate.clone();
	cv::findContours(fgMaskMOG2Filled, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	// Get Bound Rect

	for(unsigned i = 0; i < contours.size(); i++){
		approxPolyDP(Mat(contours[i]), contours_poly, 3, true);
		boundRect = boundingRect(Mat(contours_poly));
		if(boundRect.area() > 10000){
			newFound.push_back(boundRect);
			if(drawFlag){
				rectangle(frame, boundRect, Scalar(255, 0, 0));
				return boundRect;
			}
		}
	}

	return *newFound.end();
}
