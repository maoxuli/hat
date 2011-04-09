#include <iostream>
#include <Ice/Service.h>

class FileService : public Ice::Service {
protected:
	virtual bool start(int, char*[], int&status); 
private:
	Ice::ObjectAdapterPtr _adapter;
};

bool FileService::start(int argc, char* argv[], int& status) {
	
	std::cout << "Service start" << std::endl;
	return true;
}

int main (int argc, char * const argv[]) {
    
	FileService fs;
    return fs.main(argc, argv);
}
