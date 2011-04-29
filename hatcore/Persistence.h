#ifndef __PERSISTENCE_H__
#define __PERSISTENCE_H__

#define OTL_IODBC_BSD // Compile OTL 4.0/ODBC
#include <otlv4.h>

#include <string>
using namespace std;

namespace hat
{
	
	class Persistence
	{
	public:
		Persistence(const string& name);
		virtual ~Persistence();
		
		bool initialize();
		void shutdown();
		
		bool insertFile(const string& name);
		
	private:
		
		string _name;
		otl_connect _db; //OTL database connection

	}; 
}

#endif //__PERSISTENCE_H__