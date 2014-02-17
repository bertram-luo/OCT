/************************************************************************
* File:	RunTracker.cpp
* Brief: C++ demo for paper: Kaihua Zhang, Lei Zhang, Ming-Hsuan Yang,"Real-Time Compressive Tracking," ECCV 2012.
* Version: 1.0
* Author: Yang Xian
* Email: yang_xian521@163.com
* Date:	2012/08/03
* History:
* Revised by Kaihua Zhang on 14/8/2012, 23/8/2012
* Email: zhkhua@gmail.com
* Homepage: http://www4.comp.polyu.edu.hk/~cskhzhang/
* Project Website: http://www4.comp.polyu.edu.hk/~cslzhang/CT/CT.htm
************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include "ConfigParser.h"
#include "DataProvider.h"
#include "CompressiveTracker.h"

using namespace cv;
using namespace std;

void init(char* conf,char* imgFilePath,Rect& box);
void process(char* imgFilePath,Rect box);

int main(int argc, char * argv[])
{

	char imgFilePath[100];
    char  conf[100];
	strcpy(conf,"./config.txt");
	Rect box; // [x y width height] tracking position

	// CT framework
	init(conf,imgFilePath,box);
	process(imgFilePath,box);

	return 0;
}

void init(char* conf,char* imgFilePath,Rect& box){
	ConfigParser cp;
	cp.readConfig(conf,imgFilePath,box);
	return;
}

void process(char* imgFilePath,Rect box){

	DataProvider dp = DataProvider(DataProvider::DP_SEQUENCE);
	dp.init(imgFilePath);

	Mat frame;
	Mat grayImg;

	CompressiveTracker ct;

	frame = dp.getFrame();
	cvtColor(frame,grayImg,CV_RGB2GRAY);
	ct.init(grayImg, box);

	char strFrame[20];

    FILE* resultStream;
	resultStream = fopen("TrackingResults.txt", "w");
	fprintf (resultStream,"%i %i %i %i\n",(int)box.x,(int)box.y,(int)box.width,(int)box.height);

	int size = dp.nFrame();
	for(int i = 1; i < size; i ++)
	{
		frame = dp.getFrame();
		cvtColor(frame,grayImg,CV_RGB2GRAY);
		ct.processFrame(grayImg, box);// Process frame

		fprintf (resultStream,"%i %i %i %i\n",(int)box.x,(int)box.y,(int)box.width,(int)box.height);

		rectangle(frame, box, Scalar(200,0,0),2);// Draw rectangle
		sprintf(strFrame, "#%d ",i) ;
		putText(frame,strFrame,cvPoint(0,20),2,1,CV_RGB(25,200,25));

		imshow("CT", frame);// Display
		waitKey(2);
	}
	fclose(resultStream);

}

