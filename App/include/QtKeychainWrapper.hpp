#ifndef QTKEYCHAINWRAPPER_HPP
#define QTKEYCHAINWRAPPER_HPP
#include <QString>
#include "keychain.h"

class QtKeychainWrapper {
public:
    bool writePassword(const QString& service, const QString& password);
    QString readPassword(const QString& service);
};

#endif // QTKEYCHAINWRAPPER_HPP