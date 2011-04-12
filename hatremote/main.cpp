#include <iostream>
#include <Ice/Service.h>

class RemoteService : public Ice::Service {
protected:
	virtual bool start(int, char*[], int&status); 
private:
	Ice::ObjectAdapterPtr _adapter;
};

bool RemoteService::start(int argc, char* argv[], int& status) {
	
	std::cout << "Remote service start" << std::endl;
	return true;
}

int main (int argc, char * const argv[]) {
    
	RemoteService rs;
    return rs.main(argc, argv);
}

