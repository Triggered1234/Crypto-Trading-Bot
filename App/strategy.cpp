#include "strategy.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

Strategy::Strategy(QString name, QString timeFrame, QString refreshRate, bool takeProfitStatus,
                   bool hasMA, bool hasRSI, bool hasAD, bool hasMACD,
                   bool hasMFI, bool hasCCI, bool hasSTOOCH, bool hasVOLUME, bool hasAROON, double takeProfitPercentage,
                   double prefeeredBuyIndex, double prefeeredSellIndex, double MACDBlueLineLowLimit, double MACDBlueLineHighLimit,
                   double MACDRedLineLowLimit, double MACDRedLineHighLimit, double RSILineLowLimit, double RSILineHighLimit,
                   double ACUMDISTLowLimit, double ACUMDISTHighLimit, double MALength, double MFILowLimit, double MFIHighLimit, double CCILowLimit,
                   double CCIHighLimit)
{
    this->name = name;
    this->timeFrame = timeFrame;
    this->refreshRate = refreshRate;
    this->takeProfitStatus = takeProfitStatus;
    this->hasMA = hasMA;
    this->hasRSI = hasRSI;
    this->hasAD = hasAD;
    this->hasMACD = hasMACD;
    this->hasMFI = hasMFI;
    this->hasCCI = hasCCI;
    this->hasSTOOCH = hasSTOOCH;
    this->hasVOLUME = hasVOLUME;
    this->hasAROON = hasAROON;
    this->takeProfitPercentage = takeProfitPercentage;
    this->prefeeredBuyIndex = prefeeredBuyIndex;
    this->prefeeredSellIndex = prefeeredSellIndex;
    this->MACDBlueLineLowLimit = MACDBlueLineLowLimit;
    this->MACDBlueLineHighLimit = MACDBlueLineHighLimit;
    this->MACDRedLineLowLimit = MACDRedLineLowLimit;
    this->MACDRedLineHighLimit = MACDRedLineHighLimit;
    this->RSILineLowLimit = RSILineLowLimit;
    this->RSILineHighLimit = RSILineHighLimit;
    this->ACUMDISTLowLimit = ACUMDISTLowLimit;
    this->ACUMDISTHighLimit = ACUMDISTHighLimit;
    this->MALength = MALength;
    this->MFILowLimit = MFILowLimit;
    this->MFIHighLimit = MFIHighLimit;
    this->CCILowLimit = CCILowLimit;
    this->CCIHighLimit = CCIHighLimit;

}


// Getters
QString Strategy::getName() const { return name; }
QString Strategy::getTimeFrame() const { return timeFrame; }
QString Strategy::getRefreshRate() const {return refreshRate; }
bool Strategy::getTakeProfitStatus() const {return takeProfitStatus; }
bool Strategy::getHasMA() const { return hasMA; }
bool Strategy::getHasRSI() const { return hasRSI; }
bool Strategy::getHasAD() const { return hasAD; }
bool Strategy::getHasMACD() const { return hasMACD; }
bool Strategy::getHasMFI() const { return hasMFI; }
bool Strategy::getHasCCI() const { return hasCCI; }
bool Strategy::getHasSTOOCH() const { return hasSTOOCH; }
bool Strategy::getHasVOLUME() const { return hasVOLUME; }
bool Strategy::getHasAROON() const { return hasAROON; }
double Strategy::getTakeProfitPercentage() const {return takeProfitPercentage;}
double Strategy::getPrefeeredBuyIndex() const { return prefeeredBuyIndex; }
double Strategy::getPrefeeredSellIndex() const { return prefeeredSellIndex; }
double Strategy::getMACDBlueLineLowLimit() const { return MACDBlueLineLowLimit; }
double Strategy::getMACDBlueLineHighLimit() const { return MACDBlueLineHighLimit; }
double Strategy::getMACDRedLineLowLimit() const { return MACDRedLineLowLimit; }
double Strategy::getMACDRedLineHighLimit() const { return MACDRedLineHighLimit; }
double Strategy::getRSILineLowLimit() const { return RSILineLowLimit; }
double Strategy::getRSILineHighLimit() const { return RSILineHighLimit; }
double Strategy::getACUMDISTLowLimit() const {return ACUMDISTLowLimit; }
double Strategy::getACUMDISTHighLimit() const {return ACUMDISTHighLimit; }
double Strategy::getMALength() const {return MALength; }
double Strategy::getMFILowLimit() const {return MFILowLimit; }
double Strategy::getMFIHighLimit() const {return MFIHighLimit; }
double Strategy::getCCILowLimit() const {return CCILowLimit; }
double Strategy::getCCIHighLimit() const {return CCIHighLimit; }


void Strategy::setName(const QString &name) { this->name = name; }
void Strategy::setTimeFrame(const QString &timeFrame) { this->timeFrame = timeFrame; }
void Strategy::setRefreshRate(const QString &refreshRate) { this->refreshRate = refreshRate; }
void Strategy::setTakeProfitStatus(bool takeProfitStatus) { this->takeProfitStatus = takeProfitStatus; }
void Strategy::setHasMA(bool hasMA) { this->hasMA = hasMA; }
void Strategy::setHasRSI(bool hasRSI) { this->hasRSI = hasRSI; }
void Strategy::setHasAD(bool hasAD) { this->hasAD = hasAD; }
void Strategy::setHasMACD(bool hasMACD) { this->hasMACD = hasMACD; }
void Strategy::setHasMFI(bool hasMFI) { this->hasMFI = hasMFI; }
void Strategy::setHasCCI(bool hasCCI) { this->hasCCI = hasCCI; }
void Strategy::setHasSTOOCH(bool hasSTOOCH) { this->hasSTOOCH = hasSTOOCH; }
void Strategy::setHasVOLUME(bool hasVOLUME) { this->hasVOLUME = hasVOLUME; }
void Strategy::setHasAROON(bool hasAROON) { this->hasAROON = hasAROON; }
void Strategy::setTakeProfitPercentage(double takeProfitPercentage) { this->takeProfitPercentage = takeProfitPercentage; }
void Strategy::setPrefeeredBuyIndex(double prefeeredBuyIndex) { this->prefeeredBuyIndex = prefeeredBuyIndex; }
void Strategy::setPrefeeredSellIndex(double prefeeredSellIndex) { this->prefeeredSellIndex = prefeeredSellIndex; }
void Strategy::setMACDBlueLineLowLimit(double MACDBlueLineLowLimit) { this->MACDBlueLineLowLimit = MACDBlueLineLowLimit; }
void Strategy::setMACDBlueLineHighLimit(double MACDBlueLineHighLimit) { this->MACDBlueLineHighLimit = MACDBlueLineHighLimit; }
void Strategy::setMACDRedLineLowLimit(double MACDRedLineLowLimit) { this->MACDRedLineLowLimit = MACDRedLineLowLimit; }
void Strategy::setMACDRedLineHighLimit(double MACDRedLineHighLimit) { this->MACDRedLineHighLimit = MACDRedLineHighLimit; }
void Strategy::setRSILineLowLimit(double RSILineLowLimit) { this->RSILineLowLimit = RSILineLowLimit; }
void Strategy::setRSILineHighLimit(double RSILineHighLimit) { this->RSILineHighLimit = RSILineHighLimit; }
void Strategy::setACUMDISTLowLimit(double ACUMDISTLowLimit) { this->ACUMDISTLowLimit = ACUMDISTLowLimit; }
void Strategy::setACUMDISTHighLimit(double ACUMDISTHighLimit) { this->ACUMDISTHighLimit = ACUMDISTHighLimit; }
void Strategy::setMALength(double MALength) { this->MALength = MALength; }
void Strategy::setMFILowLimit(double MFILowLimit) { this->MFILowLimit = MFILowLimit; }
void Strategy::setMFIHighLimit(double MFIHighLimit) { this->MFIHighLimit = MFIHighLimit; }
void Strategy::setCCILowLimit(double CCILowLimit) { this->CCILowLimit = CCILowLimit; }
void Strategy::setCCIHighLimit(double CCIHighLimit) { this->CCIHighLimit = CCIHighLimit; }

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
    json["refreshRate"] = refreshRate;
    json["takeProfitStatus"] = takeProfitStatus;
    json["hasMA"] = hasMA;
    json["hasRSI"] = hasRSI;
    json["hasAD"] = hasAD;
    json["hasMACD"] = hasMACD;
    json["hasMFI"] = hasMFI;
    json["hasCCI"] = hasCCI;
    json["hasSTOOCH"] = hasSTOOCH;
    json["hasVOLUME"] = hasVOLUME;
    json["hasAROON"] = hasAROON;
    json["takeProfitPercentage"] = takeProfitPercentage;
    json["preferredBuyIndex"] = prefeeredBuyIndex;
    json["preferredSellIndex"] = prefeeredSellIndex;
    json["MACDBlueLineLowLimit"] = MACDBlueLineLowLimit;
    json["MACDBlueLineHighLimit"] = MACDBlueLineHighLimit;
    json["MACDRedLineLowLimit"] = MACDRedLineLowLimit;
    json["MACDRedLineHighLimit"] = MACDRedLineHighLimit;
    json["RSILineLowLimit"] = RSILineLowLimit;
    json["RSILineHighLimit"] = RSILineHighLimit;
    json["ACUMDISTLowLimit"] = ACUMDISTLowLimit;
    json["ACUMDISTHighLimit"] = ACUMDISTHighLimit;
    json["MALength"] = MALength;
    json["MFILowLimit"] = MFILowLimit;
    json["MFIHighLimit"] = MFIHighLimit;
    json["CCILowLimit"] = CCILowLimit;
    json["CCIHighLimit"] = CCIHighLimit;
    return json;
}

Strategy Strategy::fromJson(const QJsonObject &json) {
    return Strategy(
        json["name"].toString(),
        json["timeFrame"].toString(),
        json["refreshRate"].toString(),
        json["takeProfitStatus"].toBool(),
        json["hasMA"].toBool(),
        json["hasRSI"].toBool(),
        json["hasAD"].toBool(),
        json["hasMACD"].toBool(),
        json["hasMFI"].toBool(),
        json["hasCCI"].toBool(),
        json["hasSTOOCH"].toBool(),
        json["hasVOLUME"].toBool(),
        json["hasAROON"].toBool(),
        json["takeProfitPercentage"].toDouble(),
        json["prefeeredBuyIndex"].toDouble(),
        json["prefeeredSellIndex"].toDouble(),
        json["MACDBlueLineLowLimit"].toDouble(),
        json["MACDBlueLineHighLimit"].toDouble(),
        json["MACDRedLineLowLimit"].toDouble(),
        json["MACDRedLineHighLimit"].toDouble(),
        json["RSILineLowLimit"].toDouble(),
        json["RSILineHighLimit"].toDouble(),
        json["ACUMDISTLowLimit"].toDouble(),
        json["ACUMDISTHighLimit"].toDouble(),
        json["MALength"].toDouble(),
        json["MFILowLimit"].toDouble(),
        json["MFIHighLimit"].toDouble(),
        json["CCILowLimit"].toDouble(),
        json["CCIHighLimit"].toDouble()
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
    hasMA = other.getHasMA();
    hasRSI = other.getHasRSI();
    hasAD = other.getHasAD();
    hasMACD = other.getHasMACD();
    hasMFI = other.getHasMFI();
    hasCCI = other.getHasCCI();
    hasSTOOCH = other.getHasSTOOCH();
    hasVOLUME = other.getHasVOLUME();
    hasAROON = other.getHasAROON();
    takeProfitPercentage = other.getTakeProfitPercentage();
    prefeeredBuyIndex = other.getPrefeeredBuyIndex();
    prefeeredSellIndex = other.getPrefeeredSellIndex();
    MACDBlueLineLowLimit = other.getMACDBlueLineLowLimit();
    MACDBlueLineHighLimit = other.getMACDBlueLineHighLimit();
    MACDRedLineLowLimit = other.getMACDRedLineLowLimit();
    MACDRedLineHighLimit = other.getMACDRedLineHighLimit();
    RSILineLowLimit = other.getRSILineLowLimit();
    RSILineHighLimit = other.getRSILineHighLimit();
    ACUMDISTLowLimit = other.getACUMDISTLowLimit();
    ACUMDISTHighLimit = other.getACUMDISTHighLimit();
    MALength = other.getMALength();
    MFILowLimit = other.getMFILowLimit();
    MFIHighLimit = other.getMFIHighLimit();
    CCILowLimit = other.getCCILowLimit();
    CCIHighLimit = other.getCCIHighLimit();

    return *this;
}
