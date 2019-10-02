#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

struct DbEntry
{
    int priority;
    int timestamp;
    std::string text;
};

static constexpr char USER[] = "u";
static constexpr char PASSWD[] = "p";
static constexpr char REGISTER[] = "r";
static constexpr char GET[] = "g";
static constexpr char ADD[] = "a";
static constexpr char TEXT[] = "txt";
static constexpr char PRIORITY[] = "pr";
static constexpr char TIMESTAMP[] = "tm";
static constexpr char ENTRIES[] = "entries";
static constexpr char RESPONSE[] = "response";

static constexpr char ENTRY_TIMESTAMP[] = "timestamp";
static constexpr char ENTRY_PRIORITY[] = "priority";
static constexpr char ENTRY_TEXT[] = "text";

#endif // PROTOCOL_H
