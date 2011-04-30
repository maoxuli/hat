#include "ImgFile.h"

using namespace std;

ImgFile::ImgFile()
{
}

ImgFile::~ImgFile()
{
}

bool ImgFile::load(const string& filename)
{
	IplImage* pImg = cvLoadImage(filename.c_str(), 1);
	
	return true;
}