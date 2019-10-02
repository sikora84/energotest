#ifndef ENTRY_H_
#define ENTRY_H_

#include <Wt/Dbo/Dbo.h>
#include "protocol.h"

namespace dbo = Wt::Dbo;

class Entry: public DbEntry
{
public:
    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, timestamp, ENTRY_TIMESTAMP);
        dbo::field(a, priority, ENTRY_PRIORITY);
        dbo::field(a, text, ENTRY_TEXT);
    }
};

DBO_EXTERN_TEMPLATES(Entry)

#endif // ENTRY_H_
