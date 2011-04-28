#include <iostream>
#include <Ice/Service.h>
#include "ProfileI.h"
#include "FilterI.h"

class CoreService : public Ice::Service {
protected:
	virtual bool start(int, char*[], int&status); 
private:
	Ice::ObjectAdapterPtr _adapter;
};

bool CoreService::start(int argc, char* argv[], int& status) {
	
	std::cout << "Core service start" << std::endl;
	
	_adapter = communicator()->createObjectAdapter("hatcore");
	
    hat::ProfilePtr profile = new hat::ProfileI(communicator()->getProperties(), communicator()->getLogger());
    _adapter->add(profile, communicator()->stringToIdentity("profile"));
	
	hat::FilterPtr filter = new hat::FilterI(communicator()->getProperties(), communicator()->getLogger());
	_adapter->add(filter, communicator()->stringToIdentity("filter"));	
	
    _adapter->activate();
	
	return true;
}

int main (int argc, char * const argv[]) {
    
	CoreService cs;
    return cs.main(argc, argv);
}