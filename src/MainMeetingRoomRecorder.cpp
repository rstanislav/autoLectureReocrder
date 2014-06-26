/*
 *	@brief:
 *			In this Meeting Room Recorder System, I will use Background Subtraction
 *			method to find the speaker with a whole-view camera. Another Digital PTZ 
 * 			camera will zoom to the upper body of the speaker and track him.
 *
 *	@tools:
 *			OS:				Ubuntu 14.04 LTS 64-bit
 *			OpenCV: 		OpenCV2.4.9
 *			Cameras: 		Logitech C910 (Digital PTZ), Logitech C510 (whole view)
 *			Linux Commands:	system, uvcdynctrl
 *
 *	@Date:
 *			16:00 24 Jun, 2014.
 *
 *	@author:
 *			Wang Ziyi
 */

//opencv
#include <opencv2/highgui/highgui.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
//self header
#include "BackgroundSubtraction.h"
#include "CameraControl.h"
#include "config.h"

using namespace cv;
using namespace std;

//function declarations
void help();

//global variables
//current frame
int keyboard;
Mat frameView, framePTZ; 


void help()
{
  cout
  << "----------------------------------------------------------------" 	<< endl
  << "This program shows how to use background subtraction methods and" 	<< endl
  << "Haar Upper Body detection method to form a Meeting Room Recorder" 	<< endl
  << "System"													            << endl
                                                                           	<< endl
  << "Usage:"                                                              	<< endl
  << "./meetingRoomRecorder"					                          	<< endl
  << "----------------------------------------------------------------"		<< endl
  << endl;
}


int main(int argc, char* argv[]){
	//print help information
	help();

	VideoCapture captureView(1);
	VideoCapture capturePTZ(0);
	if(!captureView.isOpened() || !capturePTZ.isOpened()){
		//error in opening the video input
		cerr << "Unable to open video file: " << endl;
		exit(EXIT_FAILURE);
	}
	//store the result of speaker detection
	Rect speakerRect;
	//create GUI windows
	namedWindow("FrameView");
	namedWindow("FramePTZ");
	//create camera control and background subtraction object
	CameraControl camCtrl;
	BackgroundSubtraction bgSub;
	
	//read input data. ESC or 'q' for quitting
	while( (char)keyboard != 'q' && (char)keyboard != 27 ){
		//read the current frame
		if(!captureView.read(frameView) || !capturePTZ.read(framePTZ)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}
		
		speakerRect = bgSub.runBgSub(frameView);
		//after this step, we get the rectangle for the speaker
		//control the PTZ camera based on the rectangle
		camCtrl.autoSet(speakerRect);

		//show the both frames
		imshow("FrameView", frameView);
		imshow("FramePTZ", framePTZ);
		
		//get the input from the keyboard
		keyboard = waitKey( 30 );
	}

	//destroy GUI windows
	destroyAllWindows();
	//delete capture object
	captureView.release();
	capturePTZ.release();
	return EXIT_SUCCESS;
}






