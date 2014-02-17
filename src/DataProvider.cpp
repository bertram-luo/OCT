/*
 * DataProvider.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: bertrand
 */
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <dirent.h>
#include <sys/stat.h>

#include "DataProvider.h"
using namespace std;
using namespace cv;

DataProvider::DataProvider(SRC_TYPE src_type){
	type = src_type;
	sq_index = 0;
}
DataProvider::~DataProvider(){
}

void DataProvider::init(char* src){
	switch(type){
		case DP_SEQUENCE: readImageSequenceFiles(src);break;
		default: break;
	}
}

int DataProvider::nFrame(){
	return imgNames.size();
}

Mat& DataProvider::getFrame(){
	frame = imread(imgNames[sq_index]);
	sq_index++;
	cout<<"getting frame "<<sq_index<<endl;
	return frame;


}

void DataProvider::readImageSequenceFiles(char* imgFilePath)
{
	DIR * dir;
	class dirent* ent;
	class stat st;

	dir = opendir(imgFilePath);
	cout << "====getting image sequences======"<<endl;
	while((ent = readdir(dir)) != NULL){
		const string file_name = ent->d_name;
		const string full_file_name = string(imgFilePath) + "/" + file_name;

		if(file_name[0] == '.')
			continue;

		if(stat(full_file_name.c_str(),&st) == -1)
			continue;

		const bool is_directory = (st.st_mode & S_IFDIR) != 0;

		if(is_directory)
			continue;
		imgNames.push_back(full_file_name);
	}
	std::sort(imgNames.begin(),imgNames.end());
	cout << "======"<<imgNames.size()<<" images getted======"<<endl;
	closedir(dir);
}
