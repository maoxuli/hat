#include "SynchronizerI.h"
#include "FSWatcher.h"

using namespace std;
using namespace hat;

SynchronizerI* _synchronizer = NULL;

SynchronizerI::SynchronizerI(const Ice::CommunicatorPtr& communicator, const Ice::PropertiesPtr& properties, const Ice::LoggerPtr& logger)
: _communicator(communicator)
, _properties(properties)
, _logger(logger)
{
	
}

SynchronizerI::~SynchronizerI()
{
	_synchronizer = NULL;
}

bool SynchronizerI::initialize()
{
	//_fswatcher.setCallback(this, _pathChange); 
	//_fswatcher.start();
	
	_synchronizer = this;
	
	return true;
}

void SynchronizerI::refresh(const ::std::string& path, const ::Ice::Current&)
{
	printf("SynchronizerI::refresh(%s)\n", path.c_str());
	
	if (path.empty()) {
		return;
	}
	
	if(!_profile) {
		_profile = hat::ProfilePrx::checkedCast(_communicator->propertyToProxy("Profile.Proxy"));
	}
	
    if(!_profile){
        cerr << "SynchronizerI: invalid proxy" << endl;
    }
	
	if (ftw(path.c_str(), _checkFile, 3) == 1) 
	{
		printf("fts error\n");
		return;
	} 
}

int SynchronizerI::_checkFile(const char *pathname, const struct stat *statptr, int type)
{
	if( _synchronizer != NULL )
	{
		return _synchronizer->checkFile(pathname, statptr, type);
	}
	
	return -1;
}

int SynchronizerI::checkFile(const char *pathname, const struct stat *statptr, int type)
{
	printf("pathname = [%s]\n", pathname);
	
	printf("type = [%d]\n",type);
	printf("statptr->st_size = [%d]\n", statptr->st_size);
	switch (type) {
		case FTW_F:
			/* process file */
			printf("process file\n");
			break;
		case FTW_D:
			/* process dir */
			printf("process dir\n");
			break;
		default:
			printf("process other\n");
			/* process other; */
			return -1;
	}
	
	return 0;
}
