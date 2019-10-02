#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <memory>
#include "restresource.h"
#include "dbosession.h"

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
        RestResource rest(make_unique<DboSession>());

        server.addResource(&rest, "/");
        server.run();
    }
    catch(Wt::WServer::Exception& e)
    {
        cerr << e.what() << endl;
    }
    catch(exception& e)
    {
        cerr << "exception: " << e.what() << endl;
    }
}
