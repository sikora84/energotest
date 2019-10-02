#ifndef DBOSESSION_H_
#define DBOSESSION_H_

#include <Wt/Auth/Login.h>

#include <optional>
#include <vector>

#include "user.h"
#include "entry.h"
#include "database.h"

using UserDatabase = Wt::Auth::Dbo::UserDatabase <AuthInfo>;

class DboSession: public Database
{
public:
    DboSession();
    ~DboSession();

    void addEntry(const DbEntry& entry) override;
    void registerUser(const std::string& name, const std::string& passwd) const override;
    bool userVerified(const std::string& name, const std::string& passwd) override;
    std::vector<DbEntry> getEntries() const override;
    void writeSerialisedEntries(std::ostream&) const override;

private:
    void configureAuth();
    std::optional<Wt::Auth::User> userRegistered(const std::string& name) const;
    mutable Wt::Dbo::Session session_;
    std::unique_ptr<UserDatabase> users_;
};

#endif //DBOSESSION_H_
