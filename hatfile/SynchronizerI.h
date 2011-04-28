#pragma once

#include <IceUtil/IceUtil.h>
#include <Ice/Ice.h>
#include "Synchronizer.h"

namespace hat
{
	class SynchronizerI : public Synchronizer			   
	{
	public:
	    
		SynchronizerI(const Ice::PropertiesPtr&, const Ice::LoggerPtr&);
		virtual ~SynchronizerI();
		
		bool initialize();
		
	public:
		virtual void refresh(const ::std::string&, const ::Ice::Current& = ::Ice::Current());
		
	private:
		::Ice::PropertiesPtr _properties;
		::Ice::LoggerPtr _logger;
		
	private:
		
	};
}  
