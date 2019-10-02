#include "library_wrap.h"
#include "library.h"

Q_INVOKABLE QString LibraryWrapper::getAllEntries(const QString& login, const QString& passwd)
{
    auto entries = getEntries({login.toStdString(), passwd.toStdString()});
    QString ret;
    for(const auto& x: entries)
    {
        ret += QString::fromStdString(x.text + ", " + std::to_string(x.priority) + ", " + std::to_string(x.timestamp)) + "\n";
    }
    return ret;
}

Q_INVOKABLE void LibraryWrapper::createUser(const QString& login, const QString& passwd)
{
    registerUser(User{login.toStdString(), passwd.toStdString()});
}

Q_INVOKABLE void LibraryWrapper::createEntry(const QString& login, const QString& passwd, const QString& text, int priority, int timestamp)
{
    addEntry({login.toStdString(), passwd.toStdString()}, {priority, timestamp, text.toStdString()});
}
