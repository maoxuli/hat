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
	/*hat::FilterPrx filter = hat::FilterPrx::checkedCast(communicator()->propertyToProxy("Filter.Proxy"));
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
    }*/
	
    menu();
	
    string cmd;
    do
    {
        try
        {
            cout << ">> ";
            getline(cin, cmd);
            if(cmd.size() >= 6 && cmd.substr(0, 6) == "select")
            {
				string where = cmd.substr(6);
				where.erase(where.find_last_not_of(' ')+1); 
				where.erase(0,where.find_first_not_of(' ')); 
				
				hat::FilterPrx filter = hat::FilterPrx::checkedCast(communicator()->propertyToProxy("Filter.Proxy"));
				hat::FileInfoSeq files = filter->select(where);
				int i=0;
				for (hat::FileInfoSeq::iterator p = files.begin(); p != files.end(); ++p) 
				{
					cout << ++i << ":\t" << p->id << "\t" << p->uri << "\t" << p->size << endl;
				}
				filter = NULL;           
			}
			else if(cmd.size() >= 5 && cmd.substr(0, 5) == "score")
            {
				string id = cmd.substr(5);
				id.erase(id.find_last_not_of(' ')+1); 
				id.erase(0,id.find_first_not_of(' ')); 
				int nid = -1;
				if(!id.empty())
				{
					istringstream iss(id);
					iss >> nid;
				}
				
				hat::FilterPrx filter = hat::FilterPrx::checkedCast(communicator()->propertyToProxy("Filter.Proxy"));
				hat::FileInfoSeq files = filter->score(nid);
				int i=0;
				for (hat::FileInfoSeq::iterator p = files.begin(); p != files.end(); ++p) 
				{
					cout << ++i << ":\t" << p->id << "\t" << p->uri << "\t" << p->size << endl;
				}
				filter = NULL; 
			}
			else if(cmd.size() >= 7 && cmd.substr(0, 7) == "refresh")
			{
				string path = cmd.substr(7);
				path.erase(path.find_last_not_of(' ')+1); 
				path.erase(0,path.find_first_not_of(' ')); 
				
				string prefix = "/Users/Shared/Photos";
				if(((path.size() >= prefix.size()) &&  (path.substr(0, prefix.size()) != prefix))
					|| ((path.size() > 0) && (path.size() < prefix.size())))
				{
					cout << "Wrong path: " << path << endl;
				}
				else
				{
					hat::SynchronizerPrx synchronizer = hat::SynchronizerPrx::checkedCast(communicator()->propertyToProxy("Synchronizer.Proxy"));
					synchronizer->refresh(path);
					synchronizer = NULL;
				}
			}
            else if(cmd == "exit")
            {
                // Nothing to do
            }
            else if(cmd == "?")
            {
                menu();
            }
            else
            {
                cout << "Unknown command: " << cmd << endl;
                menu();
            }
        }
        catch(const Ice::Exception& ex)
        {
            cerr << ex << endl;
        }
    }
    while(cin.good() && cmd != "exit");
	
    return EXIT_SUCCESS;
}

void HatApp::menu()
{
    cout <<
	"\n"
	"Usage:\n"
	"\n"
	"select [where] \t\t:Query photos with SQL syntax\n"
	"score [id] \t\t:Score to find duplicated and like photos\n"
	"refresh [path] \t:Refresh metadata of photos in a directory\n"
	"exit \t\t:Exit the application\n"
	"? \t\t:Display the menu\n"
	"\n";
}
