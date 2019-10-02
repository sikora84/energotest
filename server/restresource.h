#ifndef RESTRESOURCE_H
#define RESTRESOURCE_H

#include <Wt/WResource.h>
#include <memory>
#include "database.h"

namespace Wt
{
namespace Http
{
class Request;
class Response;
}
}

struct DbEntry;

class RestResource: public Wt::WResource
{
public:
    void handleRequest(const Wt::Http::Request& request, Wt::Http::Response& response) override;
    explicit RestResource(std::unique_ptr<Database> db) : dbo(std::move(db)){}
private:
    DbEntry createEntry(const Wt::Http::Request& request);
    bool addEntry(const Wt::Http::Request& request);
    void registerUser(const Wt::Http::Request& request, Wt::Http::Response& response);

    std::unique_ptr<Database> dbo;
};

#endif // RESTRESOURCE_H
