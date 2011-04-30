#ifndef __PERSISTENCE_H__
#define __PERSISTENCE_H__

#define OTL_IODBC_BSD // Compile OTL 4.0/ODBC
#include <otlv4.h>
#include "Profile.h"

#include <string>
using namespace std;

namespace hat
{
	typedef struct _FSTAT
	{
	public:
		_FSTAT()
		{
			fid = -1;
			host = "";
			path = "";
			name = "";
			stamp = 0;
			size = 0;
			hash = "";
		}
		
		_FSTAT(const FileStat& fs)
		{
			fid = fs.fid;
			host = fs.host;
			path = fs.path;
			name = fs.name;
			stamp = fs.stamp;
			size = fs.size;
			hash = fs.hash;
		}
		
		FileStat fileStat()
		{
			FileStat fs;
			fs.fid = fid;
			fs.host = host;
			fs.path = path;
			fs.name = name;
			fs.stamp = stamp;
			fs.size = size;
			fs.hash = hash;
			
			return fs;
		}
		
		int		fid;
		string	host;
		string	path;
		string	name;
		long	stamp;
		int		size;
		string	hash;
	
	}FSTAT;
	
	typedef struct _FMETA
	{
		int		fid;
		int		width;
		int		height;
		long	origin;
	}FMETA;
	
	typedef struct _FFEATURE
	{
		int		fid;
	}FFEATURE;
	
	class Persistence
	{
	public:
		Persistence(const string& dsn);
		virtual ~Persistence();
		
		bool activate();
		void shutdown();
		
		FSTAT getStat(int fid);
		FSTAT getStatByName(const string& pathname);
		FSTAT getStatByHash(const string& hash);
		
		int  insertFile(FSTAT& stat);
		bool updateStat(int fid, FSTAT& stat);
		
		FMETA getMeta(int fid);
		bool  updateMeta(int fid, FMETA& meta);
		
		FFEATURE getFeature(int fid);
		bool updateFeature(int fid, FFEATURE& feature);
		
		vector<string> selectFiles(const string& where);
		
	private:
		
		string _dsn;
		otl_connect _db; //OTL database connection
		
		otl_datetime long2time(long t);

	}; 
}

#endif //__PERSISTENCE_H__