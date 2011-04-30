#pragma once

#include <IceUtil/IceUtil.h>
#include <Ice/Ice.h>
#include "Filter.h"
#include "Persistence.h"

namespace hat
{
	class FilterI : public Filter			   
	{
	public:
	    
		FilterI(const Ice::PropertiesPtr&, const Ice::LoggerPtr&);
		virtual ~FilterI();
				
	public:
		virtual ::Ice::StringSeq select(const ::std::string&, const ::Ice::Current& = ::Ice::Current());
		
	private:
		::Ice::PropertiesPtr _properties;
		::Ice::LoggerPtr _logger;
		
	private:
		Persistence* _persistence;
		inline bool persistence()
		{
			if(!_persistence)
				_persistence = new Persistence("hatcore");
			
			return _persistence->activate();
		}
	};
}  
