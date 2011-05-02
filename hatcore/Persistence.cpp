#include "Persistence.h"
#include <iostream>
#include <string>
#include <math.h>

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

bool Persistence::deleteFile(int id)
{
	printf("Persistence::deleteFile(%d)\n",id);
	
	try 
	{
		otl_stream os(1, "delete from file where id=:id<int>",_db);
		os << id;
		
		otl_stream os2(1, "delete from meta where id=:id<int>",_db);
		os2 << id;
		
		otl_stream os3(1, "delete from meta where id=:id<int>",_db);
		os3 << id;
	}
	catch(otl_exception& e)
	{        
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	return true;
}

int  Persistence::insertFile(const FILE_INFO& info)
{
	printf("Persistence::insertFile()\n");
	cout << info.id << "\t" << info.uri << "\t" << info.stamp << "\t" << info.size << "\t" << info.hash << "\t";
	
	int id = -1;
	try
	{	
		otl_stream out(1,
					   "insert into file (id,flag,uri,stamp,size,hash) values (NULL,1,:uri<char[256]>,:stamp<timestamp>,:size<long>,:hash<char[128]>)",
					   _db);
		
		out << info.uri.c_str() << long2time(info.stamp) << info.size << info.hash.c_str();
		
		otl_stream in(1,
					  "select id from file where flag=1 and uri=:uri<char[256]> and hash=:hash<char[128]>",
					  _db);
		
		in << info.uri.c_str() << info.hash.c_str();
		
		if(!in.eof())
		{
			in >> id;
		}
		
		otl_stream os2(1, "insert into meta (id,flag) values (:id<int>,1)",_db);
		os2 << id;
		
		otl_stream os3(1, "insert into feature (id,flag) values (:id<int>,1)",_db);
		os3 << id;
		
	}
	catch(otl_exception& e)
	{        
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	
	cout << "[" << id  << "]" << endl;
	return id;
}

FILE_INFO Persistence::getFile(int id)
{
	printf("Persistence::getFile(%d)\n",id);

	FILE_INFO fi;
	return fi;
}

bool Persistence::markFile(int id)
{
	printf("Persistence::markFile(%d)\n",id);
	
	bool ret = false;
	try
	{
		otl_stream os(1, "update file set flag=1 where id=:id<int>", _db);
		os << id;
		
		otl_stream os2(1, "update meta set flag=1 where id=:id<int>",_db);
		os2 << id;
		
		otl_stream os3(1, "update feature set flag=1 where id=:id<int>", _db);
		os3 << id;
		
		ret = true;
	}
	catch (otl_exception& e)
	{
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	
	return ret;
}

bool Persistence::updateFile(const FILE_INFO& info)
{
	printf("Persistence::updateFile(%d,%s)\n",info.id,info.hash.c_str());

	bool ret = false;
	try
	{ 
		otl_stream os(1, "update file set flag=0,stamp=:stamp<timestamp>,size=:size<long>,hash=:hash<char[128]> where id=:id<int>",_db);
		os << long2time(info.stamp) << info.size << info.hash.c_str() << info.id;
		ret = true;
		
	}
	catch (otl_exception& e)
	{
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	
	return ret;
}

IMAGE_META Persistence::getMeta(int id)
{
	printf("Persistence::getMeta(%d)\n",id);

	IMAGE_META imm;
	return imm;
}

bool Persistence::updateMeta(const IMAGE_META& meta)
{
	printf("Persistence::updateMeta(%d)\n",meta.id);
	
	bool ret = false;
	try
	{ 
		otl_stream os(1, "update meta set flag=0 where id=:id<int>",_db);
		os << meta.id;
		ret = true;
		
	}
	catch (otl_exception& e)
	{
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	
	return ret;
}

IMAGE_FEATURE Persistence::getFeature(int id)
{
	printf("Persistence::getFeature(%d)\n",id);

	IMAGE_FEATURE imf;
	return imf;
}

bool Persistence::updateFeature(const IMAGE_FEATURE& feature)
{
	printf("Persistence::updateFeature(%d,%s)\n",feature.id,feature.hist.c_str());

	bool ret = false;
	try
	{ 
		otl_stream os(1, "update feature set flag=0,histogram=:hist<char[512]> where id=:id<int>",_db);
		os << feature.hist.c_str() << feature.id;
		ret = true;
		
	}
	catch (otl_exception& e)
	{
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	
	return ret;
}

map<string,FILE_INFO*> Persistence::checkFiles(const string& path)
{
	printf("Persistence::checkFiles(%s)\n",path.c_str());
	map<string,FILE_INFO*> files;
	
	try
	{
		otl_stream os;
		os.set_column_type(2,otl_var_char,256);
		ostringstream oss;
		oss << "select id,uri,stamp,size from file where uri like \'" << path << "%\'";
		os.open(50,oss.str().c_str(),_db);
				
		char suri[256];
		otl_datetime tstamp;
		while(!os.eof())
		{
			FILE_INFO* fi = new FILE_INFO;
			os >> fi->id >> suri >> tstamp >> fi->size;
			fi->uri = suri;
			fi->stamp = time2long(tstamp);
			
			files.insert(pair<string,FILE_INFO*>(fi->uri,fi));
		}
		
	}
	catch (otl_exception& e) {
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}

	return files;
}

vector<FILE_INFO> Persistence::selectFiles(const string& where)
{
	printf("Persistence::selectFiles(%s)\n", where.c_str());

	vector<FILE_INFO> files;
	
	try
	{	
		//select host,path,name from file where ...
		string sql = "select id,uri,stamp,size,hash from file ";
		if(!where.empty()) 
		{
			sql += "where ";
			sql += where;
		}
		
		otl_stream in;
		in.set_column_type(2,otl_var_char,256);
		in.set_column_type(5,otl_var_char,128);
		in.open(50, sql.c_str(), _db);
		
		while(!in.eof())
		{
			FILE_INFO fi;
			char uri[256], hash[128];
			otl_datetime odt;
			in >> fi.id >> uri >> odt >> fi.size >> hash;
			
			fi.uri = uri;
			fi.stamp = time2long(odt);
			fi.hash = hash;

			files.push_back(fi);
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

vector<FILE_INFO> Persistence::likeFiles(int id)
{
	printf("Persistence::likeFiles(%d)\n", id);
	vector<FILE_INFO> files;
	
	try
	{
		otl_stream os;
		os.set_column_type(1, otl_var_char, 128);
		os.open(1,"select hash from file where id=:id<int>",_db);
		os << id;
		
		if(!os.eof())
		{
			char hash[128];
			os >> hash;
		
			otl_stream os2;
			os2.set_column_type(2, otl_var_char, 256);
			os2.set_column_type(5, otl_var_char, 128);
			os2.open(50,"select id,uri,stamp,size,hash from file where hash=:shash<char[128]>",_db);
			os2 << hash;
				
			while(!os2.eof())
			{
				FILE_INFO fi;
				char uri[256], hash[128];
				otl_datetime odt;
				os2 >> fi.id >> uri >> odt >> fi.size >> hash;
				
				fi.uri = uri;
				fi.stamp = time2long(odt);
				fi.hash = hash;
				fi.score = 100.00;
				
				files.push_back(fi);
			}
		}
		
		otl_stream os3;
		os3.set_column_type(1, otl_var_char, 512);
		os3.open(1,"select histogram from feature where id=:id<int>",_db);
		os3 << id;
		
		if(!os3.eof())
		{
			char hist1[512];
			os3 >> hist1;
			cout << hist1 << endl;
			
			otl_stream os4;
			os4.set_column_type(2, otl_var_char, 256);
			os4.set_column_type(5, otl_var_char, 128);
			os4.set_column_type(6, otl_var_char, 512);
			os4.open(50,"select file.id,uri,stamp,size,hash,histogram from file,feature where file.id=feature.id",_db);
			
			while(!os4.eof())
			{
				int id2 = 0;
				long size2 = 0;
				char uri2[256], hash2[128], hist2[512];
				otl_datetime odt2;
				os4 >>  id2 >> uri2 >> odt2 >> size2 >> hash2 >> hist2;

				float score = scoreHist(hist1,hist2); 
				
				if(score >= 70.00)
				{
					FILE_INFO fi;
					fi.id = id2;
					fi.uri = uri2;
					fi.stamp = time2long(odt2);
					fi.size = size2;
					fi.hash = hash2;
					fi.score = score;
					files.push_back(fi);
				}
			}
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

float Persistence::scoreHist(const char* hist1, const char* hist2)
{
	printf("Persistence::scoreHist()\n");
	
	string shist1 = hist1;
	string shist2 = hist2;
	
	cout << shist1 << endl;
	std::vector<unsigned char> ihist1;
	for(int i = 0; i < shist1.size()/2; ++i)
	{ 
		istringstream iss(shist1.substr(i * 2, 2));
		unsigned int temp;
		iss >> std::hex >> temp;
		ihist1.push_back(static_cast<unsigned char>(temp));
	}
	
	for(int i=0; i<ihist1.size(); i++)
	{
		cout << (int)ihist1[i] << ",";
	}
	cout << endl;
	
	cout << shist2 << endl;
	std::vector<unsigned char> ihist2;
	for(int i = 0; i < shist2.size()/2; ++i)
	{ 
		istringstream iss(shist2.substr(i * 2, 2));
		unsigned int temp;
		iss >> std::hex >> temp;
		ihist2.push_back(static_cast<unsigned char>(temp));
	}
	
	for(int i=0; i<ihist2.size(); i++)
	{
		cout << (int)ihist2[i] << ",";
	}
	cout << endl;
	
	long sum = 0;
	for(int i=0; i<ihist1.size(); i++)
	{
		sum += (ihist1[i] - ihist2[i]) * (ihist1[i] - ihist2[i]);
	}
	sum = sum/ihist1.size();
	
	float score = (255 - sqrt(sum)) * 100 / 255.00;
	cout << "Euclidean distance: " << score << endl;
	
	return score;
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

long Persistence::time2long(otl_datetime odt)
{
	struct tm t;
	t.tm_year = odt.year - 1900;
	t.tm_mon = odt.month - 1;
	t.tm_mday = odt.day;
	t.tm_hour = odt.hour;
	t.tm_min = odt.minute;
	t.tm_sec = odt.second;
	
	return timelocal(&t);
}

