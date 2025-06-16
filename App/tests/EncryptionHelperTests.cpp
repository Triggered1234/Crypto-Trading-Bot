#include <QtTest/QtTest>
#include "EncryptionHelper.hpp"

class EncryptionHelperTest : public QObject {
    Q_OBJECT
private slots:
    void testStoreAndRetrieveSecret();
};

void EncryptionHelperTest::testStoreAndRetrieveSecret() {
    EncryptionHelper helper;
    QString key = "testKey";
    QString secret = "superSecret";
    QVERIFY(helper.storeSecret(key, secret));
    QCOMPARE(helper.retrieveSecret(key), secret);
}

QTEST_MAIN(EncryptionHelperTest)
#include "EncryptionHelperTests.moc"