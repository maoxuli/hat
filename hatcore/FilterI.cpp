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

::Ice::StringSeq FilterI::select(const ::std::string& where, const ::Ice::Current&)
{
	printf("FilterI::select(%s)\n", where.c_str());
	
	Ice::StringSeq files;
	
	if(persistence())
	{
		try {
			files = _persistence->selectFiles(where);
		}
		catch (const Ice::Exception& ex) {
			cerr << ex << endl;
		}
		_persistence->shutdown();
	}
	
	return files;
}
