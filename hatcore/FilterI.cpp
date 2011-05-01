#include "FilterI.h"

using namespace hat;

FilterI::FilterI(const Ice::PropertiesPtr& properties, const Ice::LoggerPtr& logger)
: _properties(properties)
, _logger(logger)
{
	_persistence = NULL;
}

FilterI::~FilterI()
{
	if (!_persistence) {
		delete _persistence;
	}
}

::hat::FileInfoSeq FilterI::select(const ::std::string& where, const ::Ice::Current&)
{
	printf("FilterI::select(%s)\n", where.c_str());
	
	FileInfoSeq files;
	
	if(persistence())
	{
		vector<FILE_INFO> fis = _persistence->selectFiles(where);
		
		for(vector<FILE_INFO>::iterator p = fis.begin(); p != fis.end(); ++p)
		{
			FileInfo fi = p->toFileInfo();
			files.push_back(fi);
		}
		
		_persistence->shutdown();
	}
	
	return files;
}

::hat::FileInfoSeq FilterI::score(::Ice::Int id, const ::Ice::Current&)
{
	printf("FilterI::score(%d)\n", id);
	
	FileInfoSeq files;
	
	if(persistence())
	{
		vector<FILE_INFO> fis = _persistence->likeFiles(id);
		
		for(vector<FILE_INFO>::iterator p = fis.begin(); p != fis.end(); ++p)
		{
			FileInfo fi = p->toFileInfo();
			files.push_back(fi);
		}
		
		_persistence->shutdown();
	}
	
	return files;	
}


