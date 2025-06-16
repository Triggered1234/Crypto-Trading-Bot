#include "../include/strategy.hpp"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

Strategy::Strategy(QString name, QString timeFrame, QString refreshRate, bool takeProfitStatus, double takeProfitPercentage, int preferredBuyIndex, int preferredSellIndex, QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> indicators)
    : name(std::move(name)),
      timeFrame(std::move(timeFrame)),
      refreshRate(std::move(refreshRate)),
      takeProfitStatus(takeProfitStatus),
      takeProfitPercentage(takeProfitPercentage),
      preferredBuyIndex(preferredBuyIndex),
      preferredSellIndex(preferredSellIndex),
      indicators()
{
    for (auto it = indicators.begin(); it != indicators.end(); ++it) {
        if (it.value()) {
            this->indicators[it.key()] = it.value();
        }
    }
}

// Getters
QString Strategy::getName() const { return name; }
QString Strategy::getTimeFrame() const { return timeFrame; }
QString Strategy::getRefreshRate() const { return refreshRate; }
bool Strategy::getTakeProfitStatus() const { return takeProfitStatus; }
double Strategy::getTakeProfitPercentage() const {return takeProfitPercentage;}
int Strategy::getPreferredBuyIndex() const { return preferredBuyIndex; }
int Strategy::getPreferredSellIndex() const { return preferredSellIndex; }
QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> Strategy::getIndicators() const {
    QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> copy;
    for (auto it = indicators.begin(); it != indicators.end(); ++it) {
        if (it.value()) {
            copy[it.key()] = it.value();
        }
    }
    return copy;
}


void Strategy::setName(const QString &name) { this->name = name; }
void Strategy::setTimeFrame(const QString &timeFrame) { this->timeFrame = timeFrame; }
void Strategy::setRefreshRate(const QString &refreshRate) { this->refreshRate = refreshRate; }
void Strategy::setTakeProfitStatus(bool takeProfitStatus) { this->takeProfitStatus = takeProfitStatus; }
void Strategy::setTakeProfitPercentage(double takeProfitPercentage) { this->takeProfitPercentage = takeProfitPercentage; }
void Strategy::setPreferredBuyIndex(int index) { this->preferredBuyIndex = index; }
void Strategy::setPreferredSellIndex(int index) { this->preferredSellIndex = index; }
void Strategy::setIndicators(const QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> &indicators) {
    this->indicators = indicators;
}

QString Strategy::toString() const
{
    return QString("Strategy:\n"
                   "Name: %1\n"
                   "Time Frame: %2\n"
                   "Refresh Rate: %3\n"
                   "Take Profit Status: %4\n"
                   "Take Profit Percentage: %5\n"
                   "Preferred Buy Index: %6\n"
                   "Preferred Sell Index: %7\n"
                   "Indicators: %8")
        .arg(name)
        .arg(timeFrame)
        .arg(refreshRate)
        .arg(takeProfitStatus)
        .arg(takeProfitPercentage)
        .arg(preferredBuyIndex)
        .arg(preferredSellIndex)
        .arg(indicators.keys().join(", "));
}

QJsonObject Strategy::toJson() const {
    QJsonObject json;
    json["name"] = name;
    json["timeFrame"] = timeFrame;
    json["refreshRate"] = refreshRate;
    json["takeProfitStatus"] = takeProfitStatus;
    json["takeProfitPercentage"] = takeProfitPercentage;
    json["preferredBuyIndex"] = preferredBuyIndex;
    json["preferredSellIndex"] = preferredSellIndex;

    QJsonObject indicatorsJson;
    for (const auto &key : indicators.keys()) {
        if (indicators[key]) {
            indicatorsJson[key] = indicators[key]->toJson();
        }
    }
    json["technicalIndicators"] = indicatorsJson;
    return json;
}

Strategy Strategy::fromJson(const QJsonObject &json) {
    QString name = json["name"].toString();
    QString timeFrame = json["timeFrame"].toString();
    QString refreshRate = json["refreshRate"].toString();
    bool takeProfitStatus = json["takeProfitStatus"].toBool();
    double takeProfitPercentage = json["takeProfitPercentage"].toDouble();
    int preferredBuyIndex = json["preferredBuyIndex"].toInt();
    int preferredSellIndex = json["preferredSellIndex"].toInt();

    QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> indicators;
    if (json.contains("technicalIndicators") && json["technicalIndicators"].isObject()) {
        QJsonObject indicatorsJson = json["technicalIndicators"].toObject();
        for (const QString &key : indicatorsJson.keys()) {
            QJsonObject indicatorObj = indicatorsJson[key].toObject();
            auto indicator = TechnicalIndicators::TechnicalIndicator::fromJson(indicatorObj);
            if (indicator) {
                indicators.insert(key, std::move(indicator));
            }
        }
    }

    return Strategy(name, timeFrame, refreshRate, takeProfitStatus, takeProfitPercentage, preferredBuyIndex, preferredSellIndex, std::move(indicators));
}


QVector<Strategy> Strategy::loadSettings(const QString &fileName) {
    QVector<Strategy> settingsList;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonArray jsonArray = jsonDoc.array();
        for (const auto &jsonValue : jsonArray) {
            settingsList.append(Strategy::fromJson(jsonValue.toObject()));
        }
    }
    return settingsList;
}

void Strategy::saveSettings(const QVector<Strategy> &settingsList, const QString &fileName) {
    QJsonArray jsonArray;
    for (const auto &settings : settingsList) {
        jsonArray.append(settings.toJson());
    }

    QJsonDocument jsonDoc(jsonArray);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        file.close();
    }
}

bool Strategy::addNewStrategy(const Strategy &strategy, const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Could not open file for reading and writing:" << filePath;
        return false;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument document(QJsonDocument::fromJson(fileData));
    QJsonArray jsonArray = document.array();

    for (const QJsonValue &value : jsonArray) {
        QJsonObject jsonObject = value.toObject();
        if (jsonObject["name"].toString() == strategy.name) {
            qDebug() << "Strategy with the same name already exists.";
            return false; // Strategy already exists
        }
    }

    QJsonObject jsonObject = strategy.toJson();
    jsonArray.append(jsonObject);

    document.setArray(jsonArray);
    file.resize(0); // Clear the file before writing new data
    file.write(document.toJson());
    file.close();

    return true;
}

bool Strategy::updateStrategy(const Strategy &strategy, const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Could not open file for reading and writing:" << filePath;
        return false;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument document(QJsonDocument::fromJson(fileData));
    QJsonArray jsonArray = document.array();

    for (QJsonValueRef value : jsonArray) {
        QJsonObject jsonObject = value.toObject();
        if (jsonObject["name"].toString() == strategy.name) {
            jsonObject = strategy.toJson(); // Update the JSON object with new strategy data
            value = jsonObject; // Update the value in the array
            document.setArray(jsonArray);
            file.resize(0); // Clear the file before writing new data
            file.write(document.toJson());
            file.close();

            return true;
        }
    }

    qDebug() << "Strategy not found in the JSON file.";
    file.close();
    return false;
}

Strategy& Strategy::operator=(const Strategy& other)
{
    if (this == &other) {
        return *this; // handle self assignment
    }

    name = other.getName();
    timeFrame = other.getTimeFrame();
    refreshRate = other.getRefreshRate();
    takeProfitStatus = other.getTakeProfitStatus();
    takeProfitPercentage = other.getTakeProfitPercentage();
    preferredBuyIndex = other.getPreferredBuyIndex();
    preferredSellIndex = other.getPreferredSellIndex();
    indicators = other.getIndicators();

    return *this;
}
