#ifndef __IMGFILE_H__
#define __IMGFILE_H__

#include <string>
#include <OpenCV.h>

using namespace std;

class ImgFile
{
public:
	ImgFile();
	~ImgFile();
	
	bool load(const string& filename);
	
	
};

#endif //__IMGFILE_H__

