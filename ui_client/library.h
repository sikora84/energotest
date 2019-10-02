#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "protocol.h"

struct User
{
    const std::string name;
    const std::string password;
};

std::vector<DbEntry> getEntries(const User& user);
void registerUser(const User& user);
void addEntry(const User& user, const DbEntry& entry);

#endif // LIBRARY_H
