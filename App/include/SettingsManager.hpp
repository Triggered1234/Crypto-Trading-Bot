#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QString>
#include <QSettings>
#include "EncryptionHelper.hpp"

class SettingsManager {
public:
    static SettingsManager& getInstance();

    QString getApiKey();
    void setApiKey(const QString& key);

    QString getApiSecretKey();
    void setApiSecretKey(const QString& secret);

    QString getDemoApiKey();
    void setDemoApiKey(const QString& key);

    QString getDemoApiSecretKey();
    void setDemoApiSecretKey(const QString& secret);

    bool isDemoModeEnabled();
    void setDemoModeEnabled(bool enabled);

    void loadSettings();
    void saveSettings();

private:
    SettingsManager();
    ~SettingsManager();

    QString apiKey;
    QString apiSecretKey;
    QString demoApiKey;
    QString demoApiSecretKey;
    bool demoModeToggle;

    EncryptionHelper* encryptionHelper;
    QSettings* settings;
};

#endif // SETTINGSMANAGER_HPP