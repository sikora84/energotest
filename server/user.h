#ifndef USER_H
#define USER_H

#include <Wt/Auth/Dbo/AuthInfo.h>
#include "entry.h"

using namespace Wt;

namespace dbo = Wt::Dbo;

class User;
using AuthInfo = Auth::Dbo::AuthInfo<User>;
using Entries = dbo::collection<dbo::ptr<Entry>>;

class User
{
public:
    dbo::collection<dbo::ptr<AuthInfo>> authInfos;

    template<class Action>
	void persist(Action& a)
	{
        dbo::hasMany(a, authInfos, dbo::ManyToOne, "user");
	}
};

DBO_EXTERN_TEMPLATES(User);

#endif // USER_H
