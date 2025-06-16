#include "QtKeychainWrapper.hpp"
#include <QEventLoop>

bool QtKeychainWrapper::writePassword(const QString& service, const QString& password) {
    QKeychain::WritePasswordJob job("CryptoTradingBot");
    job.setKey(service);
    job.setTextData(password);

    QEventLoop loop;
    QObject::connect(&job, &QKeychain::Job::finished, &loop, &QEventLoop::quit);
    job.start();
    loop.exec();

    return job.error() == QKeychain::NoError;
}

QString QtKeychainWrapper::readPassword(const QString& service) {
    QKeychain::ReadPasswordJob job("CryptoTradingBot");
    job.setKey(service);

    QEventLoop loop;
    QObject::connect(&job, &QKeychain::Job::finished, &loop, &QEventLoop::quit);
    job.start();
    loop.exec();

    if (job.error() == QKeychain::NoError) {
        return job.textData();
    }
    return QString();
}
