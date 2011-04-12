#include <iostream>
#include <Ice/Service.h>

class LocalService : public Ice::Service {
protected:
	virtual bool start(int, char*[], int&status); 
private:
	Ice::ObjectAdapterPtr _adapter;
};

bool LocalService::start(int argc, char* argv[], int& status) {
	
	std::cout << "Service start" << std::endl;
	return true;
}

int main (int argc, char * const argv[]) {
    
	LocalService ls;
    return ls.main(argc, argv);
}
