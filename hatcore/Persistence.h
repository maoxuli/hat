#ifndef __PERSISTENCE_H__
#define __PERSISTENCE_H__

#define OTL_IODBC_BSD // Compile OTL 4.0/ODBC
#include <otlv4.h>
#include "Profile.h"
#include "Filter.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace hat
{
	typedef struct _FILE_INFO
	{
	public:
		_FILE_INFO()
		{
			id = -1;
			uri = "";
			stamp = 0;
			size = 0;
			hash = "";
		}
		
		_FILE_INFO(const FileStat& fs)
		{
			id = fs.id;
			uri = fs.uri;
			stamp = fs.stamp;
			size = fs.size;
			hash = "";
		}
		
		_FILE_INFO(const FileStat& fs, const string& fh)
		{
			id = fs.id;
			uri = fs.uri;
			stamp = fs.stamp;
			size = fs.size;
			hash = fh;
		}
		
		hat::FileInfo toFileInfo()
		{
			FileInfo fi;
			fi.id = id;
			fi.uri = uri;
			fi.stamp = stamp;
			fi.size = size;
			fi.hash = hash;
			
			return fi;
		}
		
		int		id;
		string	uri;
		long	stamp;
		long	size;
		string	hash;
	
	}FILE_INFO;
		
	typedef struct _IMAGE_META
	{
		_IMAGE_META()
		{
			id = -1;
			width = 0;
			height = 0;
			origin = 0;
		}
		
		_IMAGE_META(const ImageMeta& imm)
		{
			id = imm.id;
			width = imm.width;
			height = imm.height;
			origin = imm.origin;
		}
		
		int		id;
		int		width;
		int		height;
		long	origin;
		
	}IMAGE_META;
	
	typedef struct _IMAGE_FEATURE
	{
		_IMAGE_FEATURE()
		{
			id = -1;
		}
		
		_IMAGE_FEATURE(const ImageFeature& imf)
		{
			id = imf.id;
		}
		
		int		id;
		
	}IMAGE_FEATURE;
	
	class Persistence
	{
	public:
		Persistence(const string& dsn);
		virtual ~Persistence();
		
		bool activate();
		void shutdown();
		
		bool deleteFile(int id);
		int insertFile(const FILE_INFO& info);
		
		FILE_INFO getFile(int id);
		bool markFile(int id);
		bool updateFile(const FILE_INFO& info);
		
		
		IMAGE_META getMeta(int id);
		bool  updateMeta(const IMAGE_META& meta);
		
		IMAGE_FEATURE getFeature(int id);
		bool updateFeature(const IMAGE_FEATURE& feature);
		
		map<string,FILE_INFO*> checkFiles(const string& path);
		vector<FILE_INFO> selectFiles(const string& where);
		vector<FILE_INFO> likeFiles(int id);
		
	private:
		
		string _dsn;
		otl_connect _db; //OTL database connection
		
		otl_datetime long2time(long t);
		long time2long(otl_datetime odt);

	}; 
}

#endif //__PERSISTENCE_H__