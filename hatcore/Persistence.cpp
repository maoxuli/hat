#include "Persistence.h"
#include <iostream>
#include <string>

using namespace std;
using namespace hat;

Persistence::Persistence(const string& dsn)
: _dsn(dsn)
{	
	
}

Persistence::~Persistence()
{
	
}

bool Persistence::activate()
{
	printf("Persistence::activate()\n");
	
	try
	{
		otl_connect::otl_initialize();
		_db.rlogon(_dsn.c_str());		// connect to db
	}
	catch(otl_exception& e)
	{
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error

		return false;
	}

	return true;
}

void Persistence::shutdown()
{
	printf("Persistence::shutdown()\n");
	
	try
	{
		_db.logoff();   // disconnect from db
	}
	catch(otl_exception& e)
	{
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
}

FSTAT Persistence::getStat(int fid)
{
	FSTAT fs;
	return fs;
}

FSTAT Persistence::getStatByName(const string& pathname)
{
	FSTAT fs;
	return fs;
}

FSTAT Persistence::getStatByHash(const string& hash)
{
	FSTAT fs;
	return fs;
}

int  Persistence::insertFile(FSTAT& stat)
{
	printf("Persistence::insertFile()\n");
	cout << stat.fid << stat.host << stat.path << stat.name << stat.stamp << stat.size << stat.hash << endl;
	
	try
	{	
		otl_stream out(1,
					   "insert into file (fid,host,path,name,stamp,size,hash) values (NULL,:host<char[128]>,:path<char[128]>,:name<char[128]>,:stamp<timestamp>,:size<int>,:hash<char[128]>)",
					   _db);
		
		out << stat.host.c_str() << stat.path.c_str() << stat.name.c_str() << long2time(stat.stamp) << stat.size << stat.hash.c_str();
	}
	catch(otl_exception& e)
	{        
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	
	return true;
}

bool Persistence::updateStat(int fid, FSTAT& stat)
{
	return true;
}

FMETA Persistence::getMeta(int fid)
{
	FMETA fm;
	return fm;
}

bool  Persistence::updateMeta(int fid, FMETA& meta)
{
	return true;
}

FFEATURE Persistence::getFeature(int fid)
{
	FFEATURE ff;
	return ff;
}

bool Persistence::updateFeature(int fid, FFEATURE& feature)
{
	return true;
}

vector<string> Persistence::selectFiles(const string& where)
{
	printf("Persistence::selectFiles(%s)\n", where.c_str());

	vector<string> files;
	
	try
	{	
		//select host,path,name from file where ...
		string sql = "select host,path,name from file ";
		if(!where.empty()) 
		{
			sql += "where ";
			sql += where;
		}
		
		otl_stream in;
		in.set_column_type(1,otl_var_char,128);
		in.set_column_type(2,otl_var_char,128);
		in.set_column_type(3,otl_var_char,128);
		in.open(50, sql.c_str(), _db);

		
		while(!in.eof())
		{
			char host[128], path[128], name[128];
			in >> host >> path >> name;
			
			ostringstream oss;
			oss << host << path << name;

			files.push_back(oss.str());
			
			cout << oss.str() << endl;
		}
	}
	catch(otl_exception& e)
	{        
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	
	return files;
}

otl_datetime Persistence::long2time(long t)
{
	otl_datetime odt;
	struct tm* pt = localtime(&t);
	if(pt)
	{
		odt.year=pt->tm_year+1900;
		odt.month=pt->tm_mon+1;
		odt.day=pt->tm_mday;
		odt.hour=pt->tm_hour;
		odt.minute=pt->tm_min;
		odt.second=pt->tm_sec;
	}

	return odt;
}
