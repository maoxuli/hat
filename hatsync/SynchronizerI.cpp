#include "SynchronizerI.h"
#include "FSWatcher.h"

#include <iostream>
#include <iomanip>
#include <sstream>

#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/sha.h>

#define BLOCKSIZE 5

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
	_filepath = _properties->getPropertyWithDefault("Files.Path","/Users/Shared/Photos");
	_synchronizer = this;
	
	//_fswatcher.setCallback(this, _pathChange); 
	//_fswatcher.start();	
	
	return true;
}

void SynchronizerI::refresh(const ::std::string& path, const ::Ice::Current&)
{
	printf("SynchronizerI::refresh(%s)\n", path.c_str());
	
	string filepath = path;
	if (filepath.empty()) {
		filepath = _filepath;
	}
	
	if (ftw(filepath.c_str(), _checkFile, 3) == 1) 
	{
		printf("fts error\n");
		return;
	} 
}

void SynchronizerI::updateFile(const string& pathname, const struct stat *statptr)
{
	printf("SynchronizerI::updateFile(%s)\n", pathname.c_str());
	
	FileStat fs;
	fs.fid = -1;
	fs.host = "local";
	fs.path = pathname.substr(0, pathname.rfind('/')+1);
	fs.name = pathname.substr(pathname.rfind('/')+1);
	fs.stamp = statptr->st_mtime;
	fs.size = statptr->st_size;
	fs.hash = getDigest(pathname);
	cout << fs.fid << fs.host << fs.path << fs.name << fs.stamp << fs.size << fs.hash << endl;
	
	try {
		ProfilePrx profile = hat::ProfilePrx::checkedCast(_communicator->propertyToProxy("Profile.Proxy"));
		int fid = profile->updateFile(fs);
		profile = NULL;
	}
	catch(const Ice::Exception& ex)
	{
		cerr << ex << endl;
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
	printf("SynchronizerI::checkFile(%s)\n", pathname);

	switch (type) {
		case FTW_F:
			updateFile(pathname, statptr);
			break;
		case FTW_D:
			break;
		default:
			return -1;
	}
	
	return 0;
}

string SynchronizerI::getDigest(const string& pathname)
{
    FILE *fp;
    
    unsigned char md[SHA_DIGEST_LENGTH];
    unsigned char buf[BLOCKSIZE]; 
    	
	memset(md, 0, sizeof(md));
	memset(buf, 0, sizeof(buf));
	
    EVP_MD_CTX ctx;
	EVP_MD_CTX_init(&ctx);
	EVP_DigestInit_ex(&ctx, EVP_sha1(), NULL);
	
    
    if (NULL == (fp = fopen(pathname.c_str(), "r")))
    {
        perror("can't open this file");
        return "";
    }
    
	while (!feof(fp))
	{
    	fread(buf, BLOCKSIZE-1, 1, fp);
    	EVP_DigestUpdate(&ctx, (const char*)buf, strlen((const char*)buf));
    }	
	
	EVP_DigestFinal_ex(&ctx, md, NULL);
	
	fclose(fp);
	
	std::ostringstream oss;
	int i = 0;
    oss << std::hex << std::setfill('0');
    while(i <= SHA_DIGEST_LENGTH) oss << std::setw(2) << int(md[i++]);
		
	return oss.str();
}

