#pragma once

#include <IceUtil/IceUtil.h>
#include <Ice/Ice.h>
#include "Profile.h"

namespace hat
{
	class ProfileI : public Profile			   
	{
	public:
	    
		ProfileI(const Ice::PropertiesPtr&, const Ice::LoggerPtr&);
		virtual ~ProfileI();
		
		bool initialize();
		
	public:
		virtual void setHash(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current());
		virtual ::std::string getHash(const ::std::string&, const ::Ice::Current& = ::Ice::Current());
		
	private:
		::Ice::PropertiesPtr _properties;
		::Ice::LoggerPtr _logger;
		
	private:
		
	};
}  
