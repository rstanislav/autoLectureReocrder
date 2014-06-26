#ifndef BACKGROUNDSUBTRACTION_H
#define BACKGROUNDSUBTRACTION_H

#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>

class BackgroundSubtraction{
	private:
		//MOG2 Baground subtractor

		cv::BackgroundSubtractorMOG2 pMOG2;
		//MOG2 data members
		cv::Mat fgMaskMOG2, fgMaskMOG2Bin;
		cv::Mat fgMaskMOG2Erode, fgMaskMOG2Dilate, fgMaskMOG2Filled;
		//countour memebers
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Point> contours_poly;
		cv::Rect boundRect;
		std::vector<cv::Rect> newFound;
		//morphing members
		cv::Mat elementErode;
		cv::Mat elementDilate;
	public:
		//constructor and destructor
		BackgroundSubtraction();
		~BackgroundSubtraction();
		//run background subtractor
		cv::Rect runBgSub(cv::Mat &frame, bool drawFlag = 1);
};

#endif
