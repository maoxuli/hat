#include "SynchronizerI.h"
#include "FSWatcher.h"
#include "ImgFile.h"

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
	_hostname = _properties->getPropertyWithDefault("Host.Name","maoxu");
	
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
	
	_filestats.clear();
	
	if (ftw(filepath.c_str(), _checkFile, 3) == 1) 
	{
		printf("ftw error\n");
	} 
	printf("Refresh files (%d)\n",_filestats.size());
	
	try 
	{
		ProfilePrx profile = hat::ProfilePrx::checkedCast(_communicator->propertyToProxy("Profile.Proxy"));
		
		FileStatSeq files = profile->refreshPath(_hostname+filepath, _filestats);
		printf("Refresh files return (%d)\n",files.size());
		
		for(FileStatSeq::iterator p = files.begin(); p != files.end(); ++p)
		{
			if(profile->updateFile(*p, getDigest(p->pathname)))
			{
				printf("Refresh hash return true (%d)\n",p->id);
				
				ImgFile imgfile;
				if(imgfile.load(p->pathname))
				{
					//Update image meta
					//ImageMeta
					ImgMeta im = imgfile.metadata();
					
					ImageMeta imm;
					imm.id = p->id;
					imm.width = im.width;
					imm.height = im.height;
					imm.origin = im.origin;
					profile->updateMeta(imm);
					cout << "Refresh meta:" << imm.width << "," << imm.height << "," << imm.origin << endl;
				
					//Update image feature
					//ImageFeature
					string hist = imgfile.histogram();
					ImageFeature imf;
					imf.id = p->id;
					imf.hist = hist;
					profile->updateFeature(imf);
					cout << "Refresh feature: " << imf.hist << endl;

				}
			}
		}
		
		profile = NULL;
		printf("Refresh done!");
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
		{
			//File, add to list
			FileStat fs;
			fs.id = -1;
			fs.uri = _hostname;
			fs.uri += pathname;
			fs.pathname = pathname;
			fs.stamp = statptr->st_mtime;
			fs.size = statptr->st_size;
			
			_filestats.push_back(fs);
			cout << fs.id << "\t" << fs.uri << "\t" << fs.stamp << "\t" << fs.size << endl;
			break;
		}
		case FTW_D:
		{
			//Directory, do nothing
			break;
		}
		default:
		{
			//Other files, do nothing
			//return -1;
		}
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

