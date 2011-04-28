#include "SynchronizerI.h"

using namespace hat;

SynchronizerI::SynchronizerI(const Ice::PropertiesPtr& properties, const Ice::LoggerPtr& logger)
: _properties(properties)
, _logger(logger)
{
	
}

SynchronizerI::~SynchronizerI()
{
	
}

bool SynchronizerI::initialize()
{
	printf("SynchronizerI::initialize\n");
	return true;
}

void SynchronizerI::refresh(const ::std::string&, const ::Ice::Current&)
{
}

