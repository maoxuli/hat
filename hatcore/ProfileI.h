#pragma once

#include <IceUtil/IceUtil.h>
#include <Ice/Ice.h>
#include "Profile.h"
#include "Persistence.h"

namespace hat
{
	class ProfileI : public Profile			   
	{
	public:
	    
		ProfileI(const Ice::PropertiesPtr&, const Ice::LoggerPtr&);
		virtual ~ProfileI();
				
	public:
		virtual ::Ice::Int updateFile(const ::hat::FileStat&, const ::Ice::Current& = ::Ice::Current());
		
		virtual void updateMeta(const ::hat::FileMeta&, const ::Ice::Current& = ::Ice::Current());
		
		virtual void updateFeature(const ::hat::FileFeature&, const ::Ice::Current& = ::Ice::Current());

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
