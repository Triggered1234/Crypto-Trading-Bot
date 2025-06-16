#include <QtTest/QtTest>
#include "SettingsManager.hpp"

class SettingsManagerTests : public QObject {
    Q_OBJECT
private slots:
    void testSetAndGetApiKey();
    void testSetAndGetApiSecretKey();
    void testSetAndGetDemoApiKey();
    void testSetAndGetDemoApiSecretKey();
    void testSetAndGetDemoModeEnabled();
    void testSaveAndLoadSettings();
};

void SettingsManagerTests::testSetAndGetApiKey() {
    SettingsManager& manager = SettingsManager::getInstance();
    QString key = "testApiKey";
    manager.setApiKey(key);
    QCOMPARE(manager.getApiKey(), key);
}

void SettingsManagerTests::testSetAndGetApiSecretKey() {
    SettingsManager& manager = SettingsManager::getInstance();
    QString secret = "testApiSecret";
    manager.setApiSecretKey(secret);
    QCOMPARE(manager.getApiSecretKey(), secret);
}

void SettingsManagerTests::testSetAndGetDemoApiKey() {
    SettingsManager& manager = SettingsManager::getInstance();
    QString key = "testDemoApiKey";
    manager.setDemoApiKey(key);
    QCOMPARE(manager.getDemoApiKey(), key);
}

void SettingsManagerTests::testSetAndGetDemoApiSecretKey() {
    SettingsManager& manager = SettingsManager::getInstance();
    QString secret = "testDemoApiSecret";
    manager.setDemoApiSecretKey(secret);
    QCOMPARE(manager.getDemoApiSecretKey(), secret);
}

void SettingsManagerTests::testSetAndGetDemoModeEnabled() {
    SettingsManager& manager = SettingsManager::getInstance();
    manager.setDemoModeEnabled(true);
    QVERIFY(manager.isDemoModeEnabled());
    manager.setDemoModeEnabled(false);
    QVERIFY(!manager.isDemoModeEnabled());
}

void SettingsManagerTests::testSaveAndLoadSettings() {
    SettingsManager& manager = SettingsManager::getInstance();
    manager.setApiKey("apiKeyTest");
    manager.setApiSecretKey("apiSecretTest");
    manager.setDemoApiKey("demoApiKeyTest");
    manager.setDemoApiSecretKey("demoApiSecretTest");
    manager.setDemoModeEnabled(true);
    manager.saveSettings();

    // Simulate reload
    manager.setApiKey("");
    manager.setApiSecretKey("");
    manager.setDemoApiKey("");
    manager.setDemoApiSecretKey("");
    manager.setDemoModeEnabled(false);

    manager.loadSettings();

    QCOMPARE(manager.getApiKey(), QString("apiKeyTest"));
    QCOMPARE(manager.getApiSecretKey(), QString("apiSecretTest"));
    QCOMPARE(manager.getDemoApiKey(), QString("demoApiKeyTest"));
    QCOMPARE(manager.getDemoApiSecretKey(), QString("demoApiSecretTest"));
    QVERIFY(manager.isDemoModeEnabled());
}

QTEST_MAIN(SettingsManagerTests)
#include "SettingsManagerTests.moc"