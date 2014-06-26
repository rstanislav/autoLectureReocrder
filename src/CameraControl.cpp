#include <iostream>
#include <stdio.h>
#include "config.h"
#include "CameraControl.h"

using namespace std;
using namespace cv;

/*
 * @brief:
 * 		Input for the class is the detected rectangle
 * 		for the speaker, the we can get the center of
 * 		speaker
 */
CameraControl::CameraControl(){
	centerX = 0;
	centerY = 0;
}

CameraControl::~CameraControl(){

}

/*
 * 	@brief:
 * 		change the pan value based on panNUm
 * 		Zoom and tilt value are fixed
 * */
void CameraControl::updatePTZ(int panNum){
	static char command[70];

	sprintf(command, "uvcdynctrl -d video0 -s 'Zoom, Absolute' -- %d\n", 2);
	system(command);
	sprintf(command, "uvcdynctrl -d video0 -s 'Pan (Absolute)' -- %d\n", panNum);
	system(command);
}

/*
 * @biref:
 * 		This auto set function will get the preset value based on
 * 		the location of the speaker and set the camera control parameters
 * */
void CameraControl::autoSet(Rect r){
	int presetValue = getPresetValue(r);
	int panNum;

	switch(presetValue){
		case 0:
			panNum = 25200;
			break;
		case 1:
			panNum = 21600;
			break;
		case 2:
			panNum = 18000;
			break;
		case 3:
			panNum = 14400;
			break;
		case 4:
			panNum = 3600;
			break;
		case 5:
			panNum = -7200;
			break;
		case 6:
			panNum = -10800;
			break;
		case 7:
			panNum = -14400;
			break;
		case 8:
			panNum = -18000;
			break;
		case 9:
			panNum = -21600;
			break;
		case 10:
			panNum = -36000;
			break;

		case -1:
			break;
	}
	updatePTZ(panNum);
}

/*
 * @brief:
 * 		Since the camera horizontally has 21 values in total
 * 		and 11 values (to be changed) actually cover the whole
 * 		scene of the meeting room
 */
int CameraControl::getPresetValue(Rect r){
	centerX = r.x + 0.5*r.width;
	centerY = r.y + 0.5*r.height;

	cout << "centerX = " << centerX << endl;
	//try to do test on the value range of the centerX value,
	//and set enough values to determine the boundary of each
	//grid
	if(centerX > BOUNDARY0 && centerX < BOUNDARY1)
		return 0;
	else if(centerX >= BOUNDARY1 && centerX < BOUNDARY2)
		return 1;
	else if(centerX >= BOUNDARY2 && centerX < BOUNDARY3)
		return 2;
	else if(centerX >= BOUNDARY3 && centerX < BOUNDARY4)
		return 3;
	else if(centerX >= BOUNDARY4 && centerX < BOUNDARY5)
		return 4;
	else if(centerX >= BOUNDARY5 && centerX < BOUNDARY6)
		return 5;
	else if(centerX >= BOUNDARY6 && centerX < BOUNDARY7)
		return 6;
	else if(centerX >= BOUNDARY7 && centerX < BOUNDARY8)
		return 7;
	else if(centerX >= BOUNDARY8 && centerX < BOUNDARY9)
		return 8;
	else if(centerX >= BOUNDARY9 && centerX < BOUNDARY10)
		return 9;
	else if(centerX >= BOUNDARY10 && centerX < BOUNDARY11)
		return 10;

	return -1;
}






