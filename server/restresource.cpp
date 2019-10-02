#include "restresource.h"
#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>
#include "protocol.h"

void RestResource::handleRequest(const Wt::Http::Request& request, Wt::Http::Response& response)
{
    response.setMimeType("application/json");
    response.addHeader("Server", "Wt");

    if(request.getParameter(USER) && request.getParameter(PASSWD))
    {
        if(request.getParameter(REGISTER))
        {
            registerUser(request, response);
            return;
        }
        else if(dbo->userVerified(*request.getParameter(USER), *request.getParameter(PASSWD)))
        {
            if(addEntry(request))
            {
                dbo->addEntry(createEntry(request));
                response.out() << R"(")" << RESPONSE << R"(": OK)";
                return;
            }
            else if(request.getParameter(GET))
            {
                response.out() << "{";
                response.out() << R"(")" << ENTRIES << R"(":)";
                dbo->writeSerialisedEntries(response.out());
                response.out() << "}";
                return;
            }
        }
    }
    response.out() << R"({"response":"INV"})";
    return;
}

void RestResource::registerUser(const Wt::Http::Request& request, Wt::Http::Response& response)
{
    dbo->registerUser(*request.getParameter(USER), *request.getParameter(PASSWD));
    response.out() << R"(")" << RESPONSE << R"(": OK)";
}

bool RestResource::addEntry(const Wt::Http::Request& request)
{
    return request.getParameter(ADD) && request.getParameter(TEXT) && request.getParameter(PRIORITY)
            && request.getParameter(TIMESTAMP);
}

DbEntry RestResource::createEntry(const Wt::Http::Request& request)
{
    DbEntry entry;
    entry.text = request.getParameter(TEXT) == nullptr ? "" : *request.getParameter(TEXT);
    entry.priority = request.getParameter(PRIORITY) == nullptr ? 0 : stoi(*request.getParameter(PRIORITY));
    entry.timestamp = request.getParameter(TIMESTAMP) == nullptr ? 0 : stoi(*request.getParameter(TIMESTAMP));
    return entry;
}
