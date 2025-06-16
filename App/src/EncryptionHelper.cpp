#include "EncryptionHelper.hpp"

bool EncryptionHelper::storeSecret(const QString& key, const QString& secret) {
    return keychain.writePassword(key, secret);
}

QString EncryptionHelper::retrieveSecret(const QString& key) {
    return keychain.readPassword(key);
}
