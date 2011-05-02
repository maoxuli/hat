#ifndef __IMGFILE_H__
#define __IMGFILE_H__

#include <string>
#include <OpenCV.h>

using namespace std;

typedef struct _ImgMeta 
{
public:
	_ImgMeta()
	{
		width = 0;
		height = 0;
		origin = 0;
	}
	
	int width;
	int height;
	long origin;
}ImgMeta;

class ImgFile
{
public:
	ImgFile();
	~ImgFile();
	
	bool load(const string& filename);
	ImgMeta metadata();
	string histogram();
	
	string _filename;
	IplImage* _iplimage;
};

#endif //__IMGFILE_H__

