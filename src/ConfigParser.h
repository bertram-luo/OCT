/*
 * ConfigParser.h
 *
 *  Created on: Feb 17, 2014
 *      Author: bertrand
 */

#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
/*
 * ConfigParser.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: bertrand
 */

class ConfigParser{
public:
	ConfigParser();
	~ConfigParser();
public:
	void readConfig(char* configFileName, char* imgFilePath, Rect &box);
};
