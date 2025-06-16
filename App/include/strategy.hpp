#ifndef STRATEGY_H
#define STRATEGY_H

#include <QString>
#include <QJsonObject>
#include <QVector>
#include <QMap>
#include <QString>
#include <memory>
#include "TechnicalIndicators.hpp"
class Strategy
{
private:
    QString name;
    QString timeFrame;
    QString refreshRate;
    bool takeProfitStatus;
    double takeProfitPercentage;
    int preferredBuyIndex;
    int preferredSellIndex;
    QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> indicators;

public:
    Strategy(QString name, QString timeFrame, QString refreshRate, bool takeProfitStatus, double takeProfitPercentage, int preferredBuyIndex, int preferredSellIndex, QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> indicators);
    Strategy& operator=(const Strategy& other);

    // Getters
    QString getName() const;
    QString getTimeFrame() const;
    QString getRefreshRate() const;
    bool getTakeProfitStatus() const;
    double getTakeProfitPercentage() const;
    int getPreferredBuyIndex() const;
    int getPreferredSellIndex() const;
    QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> getIndicators() const;

    // Setters
    void setName(const QString &name);
    void setTimeFrame(const QString &timeFrame);
    void setRefreshRate(const QString &refreshRate);
    void setTakeProfitStatus(bool takeProfitStatus);
    void setPreferredBuyIndex(int index);
    void setPreferredSellIndex(int index);
    void setIndicators(const QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> &indicators);
    void setTakeProfitPercentage(double takeProfitPercentage);

    QString toString() const;
    QJsonObject toJson() const;
    static Strategy fromJson(const QJsonObject &json);

    static QVector<Strategy> loadSettings(const QString &fileName);
    static void saveSettings(const QVector<Strategy> &settingsList, const QString &fileName);
    static bool addNewStrategy(const Strategy &strategy, const QString &filePath);
    static bool updateStrategy(const Strategy &strategy, const QString &filePath);

};

#endif // STRATEGY_H
