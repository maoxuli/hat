#include <Ice/Ice.h>
#include "Filter.h"
#include "Synchronizer.h"
#include <iostream>


using namespace std;

class HatApp : public Ice::Application
{
public:
	
    HatApp();
	
    virtual int run(int, char*[]);
	
private:
	
    void menu();
};

int main (int argc, char * const argv[]) {
	
    HatApp app;
    return app.main(argc, argv, "hat.config");
}

HatApp::HatApp()
{
}

int HatApp::run(int argc, char* argv[])
{
    if(argc > 1)
    {
        cerr << appName() << ": too many arguments" << endl;
        return EXIT_FAILURE;
    }
	
	hat::FilterPrx filter = hat::FilterPrx::checkedCast(communicator()->propertyToProxy("Filter.Proxy"));
    if(!filter)
    {
        cerr << argv[0] << ": invalid proxy Filter" << endl;
        return EXIT_FAILURE;
    }
	
	hat::SynchronizerPrx synchronizer = hat::SynchronizerPrx::checkedCast(communicator()->propertyToProxy("Synchronizer.Proxy"));
    if(!synchronizer)
    {
        cerr << argv[0] << ": invalid proxy Synchronizer" << endl;
        return EXIT_FAILURE;
    }
	
    menu();
	
    char c;
    do
    {
        try
        {
            cout << "==> ";
            cin >> c;
            if(c == 'f')
            {
                filter->getFile();
            }
			if(c == 's')
            {
                synchronizer->refresh("testpath");
            }
            else if(c == 'x')
            {
                // Nothing to do
            }
            else if(c == '?')
            {
                menu();
            }
            else
            {
                cout << "unknown command `" << c << "'" << endl;
                menu();
            }
        }
        catch(const Ice::Exception& ex)
        {
            cerr << ex << endl;
        }
    }
    while(cin.good() && c != 'x');
	
    return EXIT_SUCCESS;
}

void HatApp::menu()
{
    cout <<
	"usage:\n"
	"f: filter\n"
	"s: synchronizer\n"
	"x: exit\n"
	"?: help\n";
}
