#pragma once

#include <IceUtil/IceUtil.h>
#include <Ice/Ice.h>
#include "Synchronizer.h"
#include "Profile.h"
#include <string>
#include <ftw.h>

using namespace std;

namespace hat
{
	class SynchronizerI : public Synchronizer			   
	{
	public:
	    
		SynchronizerI(const Ice::CommunicatorPtr&, const Ice::PropertiesPtr&, const Ice::LoggerPtr&);
		virtual ~SynchronizerI();
		
		bool initialize();
		
	public:
		virtual void refresh(const ::std::string&, const ::Ice::Current& = ::Ice::Current());
		
		static int _checkFile(const char *pathname, const struct stat *statptr, int type);		
		int checkFile(const char *pathname, const struct stat *statptr, int type);
		
		void updateFile(const string& pathname, const struct stat *statptr);		
		string getDigest(const string& pathname);
		
	private:
		::Ice::CommunicatorPtr _communicator;
		::Ice::PropertiesPtr _properties;
		::Ice::LoggerPtr _logger;
				
		string _filepath;
		string _hostname;
				
		FileStatSeq _filestats;
		
	};
	
}  
