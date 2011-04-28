#pragma once

#include <IceUtil/IceUtil.h>
#include <Ice/Ice.h>
#include "Filter.h"

namespace hat
{
	class FilterI : public Filter			   
	{
	public:
	    
		FilterI(const Ice::PropertiesPtr&, const Ice::LoggerPtr&);
		virtual ~FilterI();
		
		bool initialize();
		
	public:
		virtual ::std::string getFile(const ::Ice::Current& = ::Ice::Current());
		
	private:
		::Ice::PropertiesPtr _properties;
		::Ice::LoggerPtr _logger;
		
	private:
		
	};
}  
