#include "SettingsManager.hpp"

SettingsManager::SettingsManager()
    : encryptionHelper(new EncryptionHelper()),
      settings(new QSettings("Crypto", "CryptoTradingBot")) // personalizează aici
{
    loadSettings();
}

SettingsManager::~SettingsManager() {
    delete encryptionHelper;
    delete settings;
}

SettingsManager& SettingsManager::getInstance() {
    static SettingsManager instance;
    return instance;
}

QString SettingsManager::getApiKey() {
    return apiKey;
}

void SettingsManager::setApiKey(const QString& key) {
    apiKey = key;
}

QString SettingsManager::getApiSecretKey() {
    return apiSecretKey;
}

void SettingsManager::setApiSecretKey(const QString& secret) {
    apiSecretKey = secret;
}

QString SettingsManager::getDemoApiKey() {
    return demoApiKey;
}

void SettingsManager::setDemoApiKey(const QString& key) {
    demoApiKey = key;
}

QString SettingsManager::getDemoApiSecretKey() {
    return demoApiSecretKey;
}

void SettingsManager::setDemoApiSecretKey(const QString& secret) {
    demoApiSecretKey = secret;
}

bool SettingsManager::isDemoModeEnabled() {
    return demoModeToggle;
}

void SettingsManager::setDemoModeEnabled(bool enabled) {
    demoModeToggle = enabled;
}

void SettingsManager::loadSettings() {
    apiKey = settings->value("apiKey").toString();
    demoApiKey = settings->value("demoApiKey").toString();
    demoModeToggle = settings->value("demoModeEnabled", false).toBool();

    apiSecretKey = encryptionHelper->retrieveSecret("apiSecretKey");
    demoApiSecretKey = encryptionHelper->retrieveSecret("demoApiSecretKey");
}

void SettingsManager::saveSettings() {
    settings->setValue("apiKey", apiKey);
    settings->setValue("demoApiKey", demoApiKey);
    settings->setValue("demoModeEnabled", demoModeToggle);

    encryptionHelper->storeSecret("apiSecretKey", apiSecretKey);
    encryptionHelper->storeSecret("demoApiSecretKey", demoApiSecretKey);
}
