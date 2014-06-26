#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <opencv2/imgproc/imgproc.hpp>

class CameraControl{
	private:
		void updatePTZ(int panNum);
		int getPresetValue(cv::Rect r);
		int centerX, centerY;

	public:
		CameraControl();
		~CameraControl();

		void autoSet(cv::Rect r);
};

#endif
