#ifndef ENCRYPTIONHELPER_HPP
#define ENCRYPTIONHELPER_HPP
#include <QString>
#include "QtKeychainWrapper.hpp"

class EncryptionHelper {
public:
    EncryptionHelper() = default;

    bool storeSecret(const QString& key, const QString& secret);
    QString retrieveSecret(const QString& key);

private:
    QtKeychainWrapper keychain;
};

#endif // ENCRYPTIONHELPER_HPP