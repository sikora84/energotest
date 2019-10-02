#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <map>
#include <algorithm>
#include "library.h"

using namespace std;
using Params = map<string, string>;
static constexpr char ADDR[] = "127.0.0.1:8080/?";

static size_t writeCb(void* contents, size_t size, size_t nmemb, void* userp)
{
    static_cast<string*>(userp)->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

static string params_string(Params const& params)
{
    string data;
    for_each(params.cbegin(), params.cend(), [&data](const auto& x)
    {
        data += "&" + x.first + "=" + x.second;
    });
    return data;
}

string formatString(const string& orig)
{
    string str = orig;
    transform(orig.cbegin(), orig.cend(), str.begin(), [](char ch)
    {
        return ch == ' ' ? '+' : ch;
    });
    return str;
}

string executeRequest(const string& params)
{
    string response;
    auto curl = curl_easy_init();
    if(curl)
    {
        auto str = ADDR + params;
        curl_easy_setopt(curl, CURLOPT_URL, str.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

vector<DbEntry> getEntries(const User& user)
{
    string response = executeRequest(params_string({{GET, ""}, {USER, formatString(user.name)}, {PASSWD, formatString(user.password)}}));
    vector<DbEntry> entries;
    Json::Reader reader;
    Json::Value obj;
    reader.parse(response, obj);
    auto resp = obj[ENTRIES];
    for(const auto& x: resp)
    {
        entries.push_back({x[ENTRY_PRIORITY].asInt(), x[ENTRY_TIMESTAMP].asInt(), x[ENTRY_TEXT].asString()});
    }
    return entries;
}

void registerUser(const User& user)
{
    executeRequest(params_string({{REGISTER, ""}, {USER, formatString(user.name)}, {PASSWD, formatString(user.password)}}));
}

void addEntry(const User& user, const DbEntry& entry)
{
    executeRequest(params_string({{ADD, ""}, {USER, formatString(user.name)}, {PASSWD, formatString(user.password)},
                                 {TEXT, formatString(entry.text)}, {PRIORITY, to_string(entry.priority)}, {TIMESTAMP, to_string(entry.timestamp)}}));
}
