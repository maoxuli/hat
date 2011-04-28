#include <iostream>
#include <Ice/Service.h>
#include "SynchronizerI.h"

class FileService : public Ice::Service {
protected:
	virtual bool start(int, char*[], int&status); 
	
private:
	Ice::ObjectAdapterPtr _adapter;
};

bool FileService::start(int argc, char* argv[], int& status) {
	
	std::cout << "File service start" << std::endl;
	
	_adapter = communicator()->createObjectAdapter("hatfile");
	
    hat::SynchronizerPtr synchronizer = new hat::SynchronizerI(communicator()->getProperties(), communicator()->getLogger());
    _adapter->add(synchronizer, communicator()->stringToIdentity("synchronizer"));

    _adapter->activate();
	
	return true;
}

int main (int argc, char * const argv[]) {
    
	FileService fs;
    return fs.main(argc, argv);
}