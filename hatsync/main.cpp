#include <iostream>
#include <Ice/Service.h>
#include "SynchronizerI.h"

class SyncService : public Ice::Service {
protected:
	virtual bool start(int, char*[], int&status); 
	
private:
	Ice::ObjectAdapterPtr _adapter;
};

bool SyncService::start(int argc, char* argv[], int& status) {
	
	std::cout << "Sync service start" << std::endl;
	
	_adapter = communicator()->createObjectAdapter("HatSync");
	
    hat::SynchronizerI* synchronizer = new hat::SynchronizerI(communicator(), communicator()->getProperties(), communicator()->getLogger());
	synchronizer->initialize();
    _adapter->add((hat:: SynchronizerPtr)synchronizer, communicator()->stringToIdentity("synchronizer"));
	
    _adapter->activate();
	
	return true;
}

int main (int argc, char * const argv[]) {
    
	SyncService ss;
    return ss.main(argc, argv);
}