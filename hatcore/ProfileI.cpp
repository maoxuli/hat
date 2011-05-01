#include "ProfileI.h"

using namespace hat;

ProfileI::ProfileI(const Ice::PropertiesPtr& properties, const Ice::LoggerPtr& logger)
: _properties(properties)
, _logger(logger)
{
	_persistence = NULL;
}

ProfileI::~ProfileI()
{
	if(!_persistence) {
		delete _persistence;
	}
}

::hat::FileStatSeq ProfileI::refreshPath(const ::std::string& path, const ::hat::FileStatSeq& fss, const ::Ice::Current&)
{
	printf("ProfileI::refreshStat(%d)\n",fss.size());
	
	FileStatSeq files;

	if(persistence())
	{
		map<string,FILE_INFO*> ufs = _persistence->checkFiles(path);

		for(FileStatSeq::const_iterator p = fss.begin(); p != fss.end(); ++p)
		{
			int fid = -1;
			map<string,FILE_INFO*>::iterator it = ufs.find(p->uri);
			if(it != ufs.end())
			{
				if (it->second->stamp != p->stamp || it->second->size != p->size) 
				{
					cout << "File change:" << p->uri << endl;
					fid = it->second->id;
					_persistence->markFile(fid);
				}
				ufs.erase(it);
			}
			else 
			{
				cout << "New file:" << p->uri << endl;
				FILE_INFO fi(*p);
				fid = _persistence->insertFile(fi);
			}

			if(fid >= 0)
			{
				FileStat fs = *p;
				fs.id = fid;
				files.push_back(fs);
			}
		}
		
		//Delete files
		for(map<string,FILE_INFO*>::iterator p = ufs.begin(); p != ufs.end(); ++p)
		{
			cout << "Delete file:" << p->second->uri << endl;;
			_persistence->deleteFile(p->second->id);
		}
		
		_persistence->shutdown();			
	}

	return files;
}

bool ProfileI::updateFile(const ::hat::FileStat& stat, const ::std::string& hash, const ::Ice::Current&)
{
	printf("ProfileI::updataFile(%d, %s)\n",stat.id, hash.c_str());
		
	bool ret = false;
	if(persistence())
	{
		FILE_INFO fi(stat,hash);
		ret = _persistence->updateFile(fi);

		_persistence->shutdown();			
	}
	
	return ret;	
}

bool ProfileI::updateMeta(const ::hat::ImageMeta& meta, const ::Ice::Current&)
{
	printf("ProfileI::updateMeta(%d)\n", meta.id);
	
	bool ret = false;
	if(persistence())
	{
		IMAGE_META imm(meta);
		ret = _persistence->updateMeta(imm);

		_persistence->shutdown();
	}
	
	return ret;
}

bool ProfileI::updateFeature(const ::hat::ImageFeature& feature, const ::Ice::Current&)
{
	printf("ProfileI::updateFeature(%d)\n", feature.id);
		
	bool ret = false;
	if(persistence())
	{
		IMAGE_FEATURE imf(feature);
		ret = _persistence->updateFeature(imf);
		
		_persistence->shutdown();
	}
	
	return ret;
}
