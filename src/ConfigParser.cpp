/*
 * ConfigParser.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: bertrand
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include "ConfigParser.h"
using namespace cv;
using namespace std;
ConfigParser::ConfigParser(){}
ConfigParser::~ConfigParser(){}
void ConfigParser::readConfig(char* configFileName, char* imgFilePath, Rect &box)
{
	int x;
	int y;
	int w;
	int h;

	fstream f;
	char cstring[1000];
	int readS=0;

	f.open(configFileName, fstream::in);

	char param1[200]; strcpy(param1,"");
	char param2[200]; strcpy(param2,"");
	char param3[200]; strcpy(param3,"");

	f.getline(cstring, sizeof(cstring));
	readS=sscanf (cstring, "%s %s %s", param1,param2, param3);

	strcpy(imgFilePath,param3);

	f.getline(cstring, sizeof(cstring));
	f.getline(cstring, sizeof(cstring));
	f.getline(cstring, sizeof(cstring));


	readS=sscanf (cstring, "%s %s %i %i %i %i", param1,param2, &x, &y, &w, &h);

	box = Rect(x, y, w, h);

}

