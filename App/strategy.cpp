#include "strategy.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

Strategy::Strategy(QString name, QString timeFrame, bool hasMA, bool hasRSI, bool hasAD, bool hasMACD,
                   bool hasMFI, bool hasCCI, bool hasSTOOCH, bool hasVOLUME, bool hasAROON, int prefeeredBuyIndex,
                   int prefeeredSellIndex, int MACDBlueLineLowLimit, int MACDBlueLineHighLimit,  int MACDRedLineLowLimit, int MACDRedLineHighLimit, int RSILineLowLimit, int RSILineHighLimit)
{
    this->name = name;
    this->timeFrame = timeFrame;
    this->hasMA = hasMA;
    this->hasRSI = hasRSI;
    this->hasAD = hasAD;
    this->hasMACD = hasMACD;
    this->hasMFI = hasMFI;
    this->hasCCI = hasCCI;
    this->hasSTOOCH = hasSTOOCH;
    this->hasVOLUME = hasVOLUME;
    this->hasAROON = hasAROON;
    this->prefeeredBuyIndex = prefeeredBuyIndex;
    this->prefeeredSellIndex = prefeeredSellIndex;
    this->MACDBlueLineLowLimit = MACDBlueLineLowLimit;
    this->MACDBlueLineHighLimit = MACDBlueLineHighLimit;
    this->MACDRedLineLowLimit = MACDRedLineLowLimit;
    this->MACDRedLineHighLimit = MACDRedLineHighLimit;
    this->RSILineLowLimit = RSILineLowLimit;
    this->RSILineHighLimit = RSILineHighLimit;
}


// Getters
QString Strategy::getName() const { return name; }
QString Strategy::getTimeFrame() const { return timeFrame; }
bool Strategy::getHasMA() const { return hasMA; }
bool Strategy::getHasRSI() const { return hasRSI; }
bool Strategy::getHasAD() const { return hasAD; }
bool Strategy::getHasMACD() const { return hasMACD; }
bool Strategy::getHasMFI() const { return hasMFI; }
bool Strategy::getHasCCI() const { return hasCCI; }
bool Strategy::getHasSTOOCH() const { return hasSTOOCH; }
bool Strategy::getHasVOLUME() const { return hasVOLUME; }
bool Strategy::getHasAROON() const { return hasAROON; }
int Strategy::getPrefeeredBuyIndex() const { return prefeeredBuyIndex; }
int Strategy::getPrefeeredSellIndex() const { return prefeeredSellIndex; }
int Strategy::getMACDBlueLineLowLimit() const { return MACDBlueLineLowLimit; }
int Strategy::getMACDBlueLineHighLimit() const { return MACDBlueLineHighLimit; }
int Strategy::getMACDRedLineLowLimit() const { return MACDRedLineLowLimit; }
int Strategy::getMACDRedLineHighLimit() const { return MACDRedLineHighLimit; }
int Strategy::getRSILineLowLimit() const { return RSILineLowLimit; }
int Strategy::getRSILineHighLimit() const { return RSILineHighLimit; }

// Setters
void Strategy::setName(const QString &name) { this->name = name; }
void Strategy::setTimeFrame(const QString &timeFrame) { this->timeFrame = timeFrame; }
void Strategy::setHasMA(bool hasMA) { this->hasMA = hasMA; }
void Strategy::setHasRSI(bool hasRSI) { this->hasRSI = hasRSI; }
void Strategy::setHasAD(bool hasAD) { this->hasAD = hasAD; }
void Strategy::setHasMACD(bool hasMACD) { this->hasMACD = hasMACD; }
void Strategy::setHasMFI(bool hasMFI) { this->hasMFI = hasMFI; }
void Strategy::setHasCCI(bool hasCCI) { this->hasCCI = hasCCI; }
void Strategy::setHasSTOOCH(bool hasSTOOCH) { this->hasSTOOCH = hasSTOOCH; }
void Strategy::setHasVOLUME(bool hasVOLUME) { this->hasVOLUME = hasVOLUME; }
void Strategy::setHasAROON(bool hasAROON) { this->hasAROON = hasAROON; }
void Strategy::setPrefeeredBuyIndex(int prefeeredBuyIndex) { this->prefeeredBuyIndex = prefeeredBuyIndex; }
void Strategy::setPrefeeredSellIndex(int prefeeredSellIndex) { this->prefeeredSellIndex = prefeeredSellIndex; }
void Strategy::setMACDBlueLineLowLimit(int MACDBlueLineLowLimit) { this->MACDBlueLineLowLimit = MACDBlueLineLowLimit; }
void Strategy::setMACDBlueLineHighLimit(int MACDBlueLineHighLimit) { this->MACDBlueLineHighLimit = MACDBlueLineHighLimit; }
void Strategy::setMACDRedLineLowLimit(int MACDRedLineLowLimit) { this->MACDRedLineLowLimit = MACDRedLineLowLimit; }
void Strategy::setMACDRedLineHighLimit(int MACDRedLineHighLimit) { this->MACDRedLineHighLimit = MACDRedLineHighLimit; }
void Strategy::setRSILineLowLimit(int RSILineLowLimit) { this->RSILineLowLimit = RSILineLowLimit; }
void Strategy::setRSILineHighLimit(int RSILineHighLimit) { this->RSILineHighLimit = RSILineHighLimit; }

QString Strategy::toString() const
{
    return QString("Strategy:\n"
                   "Name: %1\n"
                   "Time Frame: %2\n"
                   "Has MA: %3\n"
                   "Has RSI: %4\n"
                   "Has AD: %5\n"
                   "Has MACD: %6\n"
                   "Has MFI: %7\n"
                   "Has CCI: %8\n"
                   "Has STOOCH: %9\n"
                   "Has VOLUME: %10\n"
                   "Has AROON: %11\n"
                   "Preferred Buy Index: %12\n"
                   "Preferred Sell Index: %13\n"
                   "MACD Blue Line Low Limit: %14\n"
                   "MACD Blue Line High Limit: %15\n"
                   "MACD Red Line Low Limit: %16\n"
                   "MACD Red Line High Limit: %17\n"
                   "RSI Line Low Limit: %18\n"
                   "RSI Line High Limit: %19")
        .arg(name)
        .arg(timeFrame)
        .arg(hasMA)
        .arg(hasRSI)
        .arg(hasAD)
        .arg(hasMACD)
        .arg(hasMFI)
        .arg(hasCCI)
        .arg(hasSTOOCH)
        .arg(hasVOLUME)
        .arg(hasAROON)
        .arg(prefeeredBuyIndex)
        .arg(prefeeredSellIndex)
        .arg(MACDBlueLineLowLimit)
        .arg(MACDBlueLineHighLimit)
        .arg(MACDRedLineLowLimit)
        .arg(MACDRedLineHighLimit)
        .arg(RSILineLowLimit)
        .arg(RSILineHighLimit);
}

QJsonObject Strategy::toJson() const {
    QJsonObject json;
    json["name"] = name;
    json["timeFrame"] = timeFrame;
    json["hasMA"] = hasMA;
    json["hasRSI"] = hasRSI;
    json["hasAD"] = hasAD;
    json["hasMACD"] = hasMACD;
    json["hasMFI"] = hasMFI;
    json["hasCCI"] = hasCCI;
    json["hasSTOOCH"] = hasSTOOCH;
    json["hasVOLUME"] = hasVOLUME;
    json["hasAROON"] = hasAROON;
    json["preferredBuyIndex"] = prefeeredBuyIndex;
    json["preferredSellIndex"] = prefeeredSellIndex;
    json["MACDBlueLineLowLimit"] = MACDBlueLineLowLimit;
    json["MACDBlueLineHighLimit"] = MACDBlueLineHighLimit;
    json["MACDRedLineLowLimit"] = MACDRedLineLowLimit;
    json["MACDRedLineHighLimit"] = MACDRedLineHighLimit;
    json["RSILineLowLimit"] = RSILineLowLimit;
    json["RSILineHighLimit"] = RSILineHighLimit;
    return json;
}

Strategy Strategy::fromJson(const QJsonObject &json) {
    return Strategy(
        json["name"].toString(),
        json["timeFrame"].toString(),
        json["hasMA"].toBool(),
        json["hasRSI"].toBool(),
        json["hasAD"].toBool(),
        json["hasMACD"].toBool(),
        json["hasMFI"].toBool(),
        json["hasCCI"].toBool(),
        json["hasSTOOCH"].toBool(),
        json["hasVOLUME"].toBool(),
        json["hasAROON"].toBool(),
        json["prefeeredBuyIndex"].toInt(),
        json["prefeeredSellIndex"].toInt(),
        json["MACDBlueLineLowLimit"].toInt(),
        json["MACDBlueLineHighLimit"].toInt(),
        json["MACDRedLineLowLimit"].toInt(),
        json["MACDRedLineHighLimit"].toInt(),
        json["RSILineLowLimit"].toInt(),
        json["RSILineHighLimit"].toInt()
        );
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

    QJsonObject jsonObject;
    jsonObject["name"] = strategy.name;
    jsonObject["timeFrame"] = strategy.timeFrame;
    jsonObject["hasMA"] = strategy.hasMA;
    jsonObject["hasRSI"] = strategy.hasRSI;
    jsonObject["hasAD"] = strategy.hasAD;
    jsonObject["hasMACD"] = strategy.hasMACD;
    jsonObject["hasMFI"] = strategy.hasMFI;
    jsonObject["hasCCI"] = strategy.hasCCI;
    jsonObject["hasSTOOCH"] = strategy.hasSTOOCH;
    jsonObject["hasVOLUME"] = strategy.hasVOLUME;
    jsonObject["hasAROON"] = strategy.hasAROON;
    jsonObject["prefeeredBuyIndex"] = strategy.prefeeredBuyIndex;
    jsonObject["prefeeredSellIndex"] = strategy.prefeeredSellIndex;
    jsonObject["MACDBlueLineLowLimit"] = strategy.MACDBlueLineLowLimit;
    jsonObject["MACDBlueLineHighLimit"] = strategy.MACDBlueLineHighLimit;
    jsonObject["MACDRedLineLowLimit"] = strategy.MACDRedLineLowLimit;
    jsonObject["MACDRedLineHighLimit"] = strategy.MACDRedLineHighLimit;
    jsonObject["RSILineLowLimit"] = strategy.RSILineLowLimit;
    jsonObject["RSILineHighLimit"] = strategy.RSILineHighLimit;

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
            jsonObject["timeFrame"] = strategy.timeFrame;
            jsonObject["hasMA"] = strategy.hasMA;
            jsonObject["hasRSI"] = strategy.hasRSI;
            jsonObject["hasAD"] = strategy.hasAD;
            jsonObject["hasMACD"] = strategy.hasMACD;
            jsonObject["hasMFI"] = strategy.hasMFI;
            jsonObject["hasCCI"] = strategy.hasCCI;
            jsonObject["hasSTOOCH"] = strategy.hasSTOOCH;
            jsonObject["hasVOLUME"] = strategy.hasVOLUME;
            jsonObject["hasAROON"] = strategy.hasAROON;
            jsonObject["prefeeredBuyIndex"] = strategy.prefeeredBuyIndex;
            jsonObject["prefeeredSellIndex"] = strategy.prefeeredSellIndex;
            jsonObject["MACDBlueLineLowLimit"] = strategy.MACDBlueLineLowLimit;
            jsonObject["MACDBlueLineHighLimit"] = strategy.MACDBlueLineHighLimit;
            jsonObject["MACDRedLineLowLimit"] = strategy.MACDRedLineLowLimit;
            jsonObject["MACDRedLineHighLimit"] = strategy.MACDRedLineHighLimit;
            jsonObject["RSILineLowLimit"] = strategy.RSILineLowLimit;
            jsonObject["RSILineHighLimit"] = strategy.RSILineHighLimit;

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
