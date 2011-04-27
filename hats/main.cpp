#include <iostream>
#include <Ice/Service.h>

class HatService : public Ice::Service {
protected:
	virtual bool start(int, char*[], int&status); 
private:
	Ice::ObjectAdapterPtr _adapter;
};

bool HatService::start(int argc, char* argv[], int& status) {
	
	std::cout << "Hat service start" << std::endl;
	return true;
}

int main (int argc, char * const argv[]) {
    
	HatService hs;
    return hs.main(argc, argv);
}