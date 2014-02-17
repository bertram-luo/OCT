/*
 * DataProvier.h
 *
 *  Created on: Feb 17, 2014
 *      Author: bertrand
 */

#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;
class DataProvider{
public:
	enum SRC_TYPE {DP_VIDEO,DP_CAMERA,DP_SEQUENCE};
public:
	DataProvider(SRC_TYPE src_type);
	~DataProvider();
private:
	SRC_TYPE type;
	vector <string> imgNames;
	int sq_index;
	Mat frame;
	Mat grayFrame;
private:
	void readImageSequenceFiles(char* imgFilePath);
public:
	void init(char* src);
	int nFrame();
	Mat& getFrame();

};

