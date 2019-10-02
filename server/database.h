#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <ostream>
#include <vector>
#include "protocol.h"

class Database
{
public:
    virtual void addEntry(const DbEntry& entry) = 0;
    virtual void registerUser(const std::string& name, const std::string& passwd) const = 0;
    virtual bool userVerified(const std::string& name, const std::string& passwd) = 0;
    virtual std::vector<DbEntry> getEntries() const = 0;
    virtual void writeSerialisedEntries(std::ostream&) const = 0;
};

#endif // DATABASE_H
