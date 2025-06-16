#ifndef TECHNICALINDICATORUTILS_HPP
#define TECHNICALINDICATORUTILS_HPP

#include "TechnicalIndicators.hpp"
#include "ScriptManager.hpp"
#include "SettingsManager.hpp"
#include <QVector>
#include <QString>
#include <QEventLoop>
#include <QDebug>

namespace TechnicalIndicators
{
namespace Utils
{

inline QVector<QString> fetchMACDData(const QString& coinID) {
    QVector<QString> MACDLines;

    QString scriptName = "fetch_macd_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&MACDLines, &loop](const QStringList& output) {
            qDebug() << "[fetchMACDData] Script output:" << output;
            if (!output.isEmpty()) {
                QStringList values = output[0].trimmed().split(" ");
                if (values.size() >= 2) {
                    MACDLines.append(values.at(0));
                    MACDLines.append(values.at(1));
                } else {
                    qWarning() << "[fetchMACDData] Not enough MACD values:" << values;
                }
            } else {
                qWarning() << "[fetchMACDData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchMACDData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchMACDData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return MACDLines;
}

inline double fetchRSIData(const QString& coinID) {
    double RSIValue = 0.0;

    QString scriptName = "fetch_rsi_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&RSIValue, &loop](const QStringList& output) {
            qDebug() << "[fetchRSIData] Script output:" << output;
            if (!output.isEmpty()) {
                RSIValue = output[0].trimmed().toDouble();
            } else {
                qWarning() << "[fetchRSIData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchRSIData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchRSIData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return RSIValue;
}

inline double fetchACUMDISTData(const QString& coinID) {
    double ACUMDISTValue = 0.0;

    QString scriptName = "fetch_acum_dist_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&ACUMDISTValue, &loop](const QStringList& output) {
            qDebug() << "[fetchACUMDISTData] Script output:" << output;
            if (!output.isEmpty()) {
                ACUMDISTValue = output[0].trimmed().toDouble();
            } else {
                qWarning() << "[fetchACUMDISTData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchACUMDISTData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchACUMDISTData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return ACUMDISTValue;
}

inline double fetchMFIData(const QString& coinID) {
    double MFIValue = 0.0;

    QString scriptName = "fetch_mfi_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&MFIValue, &loop](const QStringList& output) {
            qDebug() << "[fetchMFIData] Script output:" << output;
            if (!output.isEmpty()) {
                MFIValue = output[0].trimmed().toDouble();
            } else {
                qWarning() << "[fetchMFIData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchMFIData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchMFIData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return MFIValue;
}

inline double fetchMAData(const QString& coinID, double MALength) {
    double MAValue = 0.0;

    QString scriptName = "fetch_ma_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin, QString::number(MALength) };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&MAValue, &loop](const QStringList& output) {
            qDebug() << "[fetchMAData] Script output:" << output;
            if (!output.isEmpty()) {
                MAValue = output[0].trimmed().toDouble();
            } else {
                qWarning() << "[fetchMAData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchMAData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchMAData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return MAValue;
}

inline double fetchCCIData(const QString& coinID)
{
    double CCIValue = 0.0;

    QString scriptName = "fetch_cci_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&CCIValue, &loop](const QStringList& output) {
            qDebug() << "[fetchCCIData] Script output:" << output;
            if (!output.isEmpty()) {
                CCIValue = output[0].trimmed().toDouble();
            } else {
                qWarning() << "[fetchCCIData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchCCIData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchCCIData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return CCIValue;
}

inline double fetchVolumeData(const QString& coinID)
{
    double volumeValue = 0.0;

    QString scriptName = "fetch_volume_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&volumeValue, &loop](const QStringList& output) {
            qDebug() << "[fetchVolumeData] Script output:" << output;
            if (!output.isEmpty()) {
                volumeValue = output[0].trimmed().toDouble();
            } else {
                qWarning() << "[fetchVolumeData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchVolumeData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchVolumeData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return volumeValue;
}

inline QVector<QString> fetchSTOCHData(const QString& coinID)
{
    QVector<QString> STOCHLines;

    QString scriptName = "fetch_stoch_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&STOCHLines, &loop](const QStringList& output) {
            qDebug() << "[fetchSTOCHData] Script output:" << output;
            if (!output.isEmpty()) {
                QStringList values = output[0].trimmed().split(" ");
                if (values.size() >= 2) {
                    STOCHLines.append(values.at(0));
                    STOCHLines.append(values.at(1));
                } else {
                    qWarning() << "[fetchSTOCHData] Not enough STOCH values:" << values;
                }
            } else {
                qWarning() << "[fetchSTOCHData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchSTOCHData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchSTOCHData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return STOCHLines;
}

inline QVector<QString> fetchAROONData(const QString& coinID)
{
    QVector<QString> AROONLines;

    QString scriptName = "fetch_aroon_data.py";
    QString coin = coinID + "USDT";

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = settings.getApiKey();
    QString apiSecret = settings.getApiSecretKey();

    QStringList args = { apiKey, apiSecret, coin };

    QEventLoop loop;
    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [&AROONLines, &loop](const QStringList& output) {
            qDebug() << "[fetchAROONData] Script output:" << output;
            if (!output.isEmpty()) {
                QStringList values = output[0].trimmed().split(" ");
                if (values.size() >= 2) {
                    AROONLines.append(values.at(0));
                    AROONLines.append(values.at(1));
                } else {
                    qWarning() << "[fetchAROONData] Not enough AROON values:" << values;
                }
            } else {
                qWarning() << "[fetchAROONData] Empty output";
            }
            loop.quit();
        },
        [&loop](int code, QProcess::ExitStatus status) {
            qWarning() << "[fetchAROONData] Script failed. Exit code:" << code << "Status:" << status;
            loop.quit();
        },
        [&loop](QProcess::ProcessError error) {
            qWarning() << "[fetchAROONData] Script crashed with error:" << error;
            loop.quit();
        }
    );

    loop.exec();
    return AROONLines;
}


} // namespace Utils
} // namespace TechnicalIndicators

#endif // TECHNICALINDICATORUTILS_HPP