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
		virtual ::hat::FileStatSeq refreshPath(const ::std::string&, const ::hat::FileStatSeq&, const ::Ice::Current& = ::Ice::Current());
		
		virtual bool updateFile(const ::hat::FileStat&, const ::std::string&, const ::Ice::Current& = ::Ice::Current());
		
		virtual bool updateMeta(const ::hat::ImageMeta&, const ::Ice::Current& = ::Ice::Current());
		
		virtual bool updateFeature(const ::hat::ImageFeature&, const ::Ice::Current& = ::Ice::Current());

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
