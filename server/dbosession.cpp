#include "dbosession.h"

#include "Wt/Auth/AuthService.h"
#include "Wt/Auth/HashFunction.h"
#include "Wt/Auth/PasswordService.h"
#include "Wt/Auth/PasswordVerifier.h"
#include "Wt/Auth/Identity.h"
#include "Wt/Auth/Dbo/AuthInfo.h"
#include "Wt/Auth/Dbo/UserDatabase.h"

#include <Wt/WApplication.h>
#include <Wt/WLogger.h>

#include <Wt/Dbo/ptr.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/Dbo/Json.h>
#include <unistd.h>
#include <mutex>


#define HAVE_CRYPT

namespace dbo = Wt::Dbo;

namespace
{
std::once_flag flag;

#ifdef HAVE_CRYPT

    class UnixCryptHashFunction : public Auth::HashFunction
    {
    public:
        std::string compute(const std::string& msg, const std::string& salt) const override
        {
            std::string md5Salt = "$1$" + salt;
            return crypt(msg.c_str(), md5Salt.c_str());
        }

        bool verify(const std::string& msg, const std::string& /*salt*/, const std::string& hash) const override
        {
            return crypt(msg.c_str(), hash.c_str()) == hash;
        }

        std::string name() const override
        {
            return "crypt";
        }
    };

#endif // HAVE_CRYPT

    Auth::AuthService myAuthService;
    Auth::PasswordService myPasswordService(myAuthService);
}

void DboSession::configureAuth()
{
    myAuthService.setIdentityPolicy(Auth::IdentityPolicy::LoginName);

    std::unique_ptr<Auth::PasswordVerifier> verifier = std::make_unique<Auth::PasswordVerifier>();
    verifier->addHashFunction(std::make_unique<Auth::BCryptHashFunction>(7));
    verifier->addHashFunction(std::make_unique<UnixCryptHashFunction>());

    myPasswordService.setVerifier(std::move(verifier));
}

DboSession::DboSession()
{
    std::call_once(flag, std::bind(&DboSession::configureAuth, this));
    auto sqlite3 = std::make_unique<Dbo::backend::Sqlite3>(WApplication::appRoot() + "energotest.db");
    sqlite3->setProperty("show-queries", "false");
    session_.setConnection(std::move(sqlite3));

    session_.mapClass<User>("user");
    session_.mapClass<AuthInfo>("auth_info");
    session_.mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    session_.mapClass<AuthInfo::AuthTokenType>("auth_token");
    session_.mapClass<Entry>("entry");

    users_ = std::make_unique<UserDatabase>(session_);

    dbo::Transaction transaction(session_);
    try
    {
        session_.createTables();
        log("info") << "Database created";
    } catch(...)
    {
        log("info") << "Using existing database";
    }

    transaction.commit();
}

DboSession::~DboSession()
{
}

void DboSession::addEntry(const DbEntry& entry)
{
    dbo::Transaction transaction(session_);
    auto ptr = session_.add(std::make_unique<Entry>());
    auto entry_ptr = ptr.modify();
    entry_ptr->text = entry.text;
    entry_ptr->priority = entry.priority;
    entry_ptr->timestamp = entry.timestamp;
    transaction.commit();
}

void DboSession::registerUser(const std::string& name, const std::string& passwd) const
{
    auto u = userRegistered(name);
    if(!u.has_value())
    {
        dbo::Transaction transaction(session_);
        u = users_->registerNew();
        u->addIdentity(Auth::Identity::LoginName, name);
        myPasswordService.updatePassword(u.value(), passwd);
        transaction.commit();
    }
}

std::optional<Wt::Auth::User> DboSession::userRegistered(const std::string& name) const
{
    auto u = users_->findWithIdentity(Wt::Auth::Identity::LoginName, name);
    if (u.isValid())
        return std::optional(u);
    return std::nullopt;
}

bool DboSession::userVerified(const std::string& name, const std::string& passwd)
{
    auto u = userRegistered(name);
    if (u.has_value() && Auth::PasswordResult::PasswordValid == myPasswordService.verifyPassword(u.value(), passwd))
    {
        return true;
    }
    return false;
}

std::vector<DbEntry> DboSession::getEntries() const
{
    dbo::Transaction transaction(session_);
    std::vector<DbEntry> entries;
    Entries all = session_.find<Entry>().orderBy("priority");
    for(auto i = all.begin(); i != all.end(); ++i)
    {
        entries.push_back({(*i)->timestamp, (*i)->priority, (*i)->text});
    }
    return entries;
}

void DboSession::writeSerialisedEntries(std::ostream& out) const
{
    dbo::Transaction transaction(session_);
    std::vector<dbo::ptr<Entry>> entries;
    Entries all = session_.find<Entry>().orderBy("priority");
    for(auto i = all.begin(); i != all.end(); ++i)
    {
        entries.push_back(*i);
    }
    Wt::Dbo::JsonSerializer writer(out);
    writer.serialize(entries);
}
