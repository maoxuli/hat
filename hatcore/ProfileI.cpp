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
	
}

bool ProfileI::initialize()
{
	printf("ProfileI::initialize\n");
	return true;
}

void ProfileI::setHash(const ::std::string& name, const ::std::string& hash, const ::Ice::Current&)
{
	printf("ProfileI::setHash(%s,%s)\n",name.c_str(),hash.c_str());
	
	if(_persistence == NULL)
	{
		_persistence = new Persistence("hatcore");
	}
	
	if(_persistence->initialize())
	{
		_persistence->insertFile(name);
		_persistence->shutdown();
	}
}

::std::string ProfileI::getHash(const ::std::string& name, const ::Ice::Current&)
{
	printf("ProfileI::getHash(%s)\n",name.c_str());
	if(_persistence == NULL)
	{
		_persistence = new Persistence("hatcore");
	}
	
	if(_persistence->initialize())
	{
		_persistence->insertFile(name);
		_persistence->shutdown();
	}
	return "";
}
