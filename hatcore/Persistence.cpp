#include "Persistence.h"
#include <iostream>

using namespace std;
using namespace hat;

Persistence::Persistence(const string& name)
: _name(name)
{	
	
}

Persistence::~Persistence()
{
	
}

bool Persistence::initialize()
{
	try
	{
		otl_connect::otl_initialize();
		_db.rlogon(_name.c_str());   // connect to db
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

bool Persistence::insertFile(const string& name)
{
	try
	{	
		otl_stream ut_in(1,	// stream buffer size should be set to 1
						 "insert into file (id,name) values(NULL, :filename<char[100]>)", // SQL statement
						 _db);	//connect object
		
		ut_in<<name.c_str();
	}
	catch(otl_exception& e)
	{        
		cerr << e.msg << endl;          // print out error message
		cerr << e.stm_text << endl;     // print out SQL that caused the error
		cerr << e.var_info << endl;     // print out the variable that caused the error
	}
	
	return true;
}
