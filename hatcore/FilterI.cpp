#include "FilterI.h"

using namespace hat;

FilterI::FilterI(const Ice::PropertiesPtr& properties, const Ice::LoggerPtr& logger)
: _properties(properties)
, _logger(logger)
{
	
}

FilterI::~FilterI()
{
	
}

bool FilterI::initialize()
{
	printf("FilterI::initialize\n");
	return true;
}

::std::string FilterI::getFile(const ::Ice::Current&)
{
	printf("FilterI::getFile()\n");
	return "";
}
