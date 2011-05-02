#include "ImgFile.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

ImgFile::ImgFile()
{
	_iplimage = NULL;
}

ImgFile::~ImgFile()
{
	if(_iplimage)
		cvReleaseImage(&_iplimage);
}

bool ImgFile::load(const string& filename)
{
	printf("imgFile::load(%s)\n",filename.c_str());
	
	if(_iplimage)
	{
		cvReleaseImage(&_iplimage);
	}
	
	_filename = filename;
	IplImage* img = cvLoadImage(filename.c_str(),1);
	
	if(!img)
	{
		return false;
	}
	
	_iplimage = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);
	cvCvtColor(img,_iplimage,CV_RGB2GRAY);
	cvReleaseImage(&img);
	
	if(!_iplimage)
	{
		return false;
	}
	
	return true;
}

ImgMeta ImgFile::metadata()
{
	ImgMeta imm;
	
	return imm;
}

string ImgFile::histogram()
{
	if(!_iplimage)
		return "";
	
	//ｃalculate histogram
	int hdims = 10;
	float hranges_arr[] = {0,255};
	float* hranges = hranges_arr;
	CvHistogram *hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );
	if(!hist)
		return "";
	
	cvCalcHist( &_iplimage, hist, 0, 0 );
	
	float max_val = 0.0;
	cvGetMinMaxHistValue(hist, 0, &max_val, 0, 0);
	cvConvertScale( hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0 );
	
	ostringstream oss;
	for (int i=0; i<hdims; ++i) 
	{
		int v = (int)cvGetReal1D(hist->bins,i);
		oss << v;
		oss << ";";
	}
	
	cvReleaseHist(&hist);
	return oss.str();
}
