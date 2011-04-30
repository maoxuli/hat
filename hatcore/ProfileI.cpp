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

::Ice::Int ProfileI::updateFile(const ::hat::FileStat& stat, const ::Ice::Current&)
{
	cout << stat.fid << stat.host << stat.path << stat.name << stat.stamp << stat.size << stat.hash << endl;

	int fid = -1;
	if(persistence())
	{
		try {
			FSTAT fs(stat);
			fid = _persistence->insertFile(fs);
		}
		catch (const Ice::Exception& ex) {
			cerr << ex << endl;
		}
		_persistence->shutdown();			
	}
	
	return fid;
}

void ProfileI::updateMeta(const ::hat::FileMeta& meta, const ::Ice::Current&)
{
	printf("ProfileI::updateMeta(%d)\n", meta.fid);
	
	if(persistence())
	{
		try {
			FMETA fm;
			_persistence->updateMeta(meta.fid, fm);
		}
		catch (const Ice::Exception& ex) {
			cerr << ex << endl;
		}
		_persistence->shutdown();
	}	
}

void ProfileI::updateFeature(const ::hat::FileFeature& feature, const ::Ice::Current&)
{
	printf("ProfileI::updateFeature(%d)\n", feature.fid);
		
	if(persistence())
	{
		try {
			FFEATURE ff;
			_persistence->updateFeature(feature.fid, ff);
		}
		catch (const Ice::Exception& ex) {
			cerr << ex << endl;
		}
		_persistence->shutdown();
	}
}
