#ifndef LIBRARY_WRAP_H
#define LIBRARY_WRAP_H

#include <QObject>
#include <QString>

class LibraryWrapper : public QObject
{
    Q_OBJECT
 public:
    Q_INVOKABLE QString getAllEntries(const QString& login, const QString& passwd);
    Q_INVOKABLE void createUser(const QString& login, const QString& passwd);
    Q_INVOKABLE void createEntry(const QString& login, const QString& passwd, const QString& text, int priority, int timestamp);

    virtual ~LibraryWrapper() {}
};

#endif // LIBRARY_WRAP_H
