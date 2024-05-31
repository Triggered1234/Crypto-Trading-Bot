#ifndef STRATEGY_H
#define STRATEGY_H
#include <QString>
#include <QJsonObject>
#include <QVector>
class Strategy
{
private:
    QString name;
    QString timeFrame;
    QString refreshRate;
    bool takeProfitStatus;
    bool hasMA;
    bool hasRSI;
    bool hasAD;
    bool hasMACD;
    bool hasMFI;
    bool hasCCI;
    bool hasSTOOCH;
    bool hasVOLUME;
    bool hasAROON;
    double takeProfitPercentage;
    double prefeeredBuyIndex;
    double prefeeredSellIndex;
    double MACDBlueLineLowLimit;
    double MACDBlueLineHighLimit;
    double MACDRedLineLowLimit;
    double MACDRedLineHighLimit;
    double RSILineLowLimit;
    double RSILineHighLimit;
    double ACUMDISTLowLimit;
    double ACUMDISTHighLimit;
    double MALength;
    double MFILowLimit;
    double MFIHighLimit;
    double CCILowLimit;
    double CCIHighLimit;

public:
    Strategy(QString name, QString timeFrame, QString refreshRate, bool takeProfitStatus, bool hasMA,
             bool hasRSI, bool hasAD, bool hasMACD, bool hasMFI, bool hasCCI, bool hasSTOOCH, bool hasVOLUME,
             bool hasAROON, double takeProfitPercentage, double prefeeredBuyIndex, double prefeeredSellIndex,
             double MACDBlueLineLowLimit, double MACDBlueLineHighLimit, double MACDRedLineLowLimit, double MACDRedLineHighLimit,
             double RSILineLowLimit, double RSILineHighLimit, double ACUMDISTLowLimit, double ACUMDISTHighLimit, double MALength, double MFILowLimit,
             double MFIHighLimit, double CCILowLimit, double CCIHighLimit);
    Strategy& operator=(const Strategy& other);

    // Getters
    QString getName() const;
    QString getTimeFrame() const;
    QString getRefreshRate() const;
    bool getTakeProfitStatus() const;
    bool getHasMA() const;
    bool getHasRSI() const;
    bool getHasAD() const;
    bool getHasMACD() const;
    bool getHasMFI() const;
    bool getHasCCI() const;
    bool getHasSTOOCH() const;
    bool getHasVOLUME() const;
    bool getHasAROON() const;
    double getTakeProfitPercentage() const;
    double getPrefeeredBuyIndex() const;
    double getPrefeeredSellIndex() const;
    double getMACDBlueLineLowLimit() const;
    double getMACDRedLineLowLimit() const;
    double getMACDBlueLineHighLimit() const;
    double getMACDRedLineHighLimit() const;
    double getRSILineLowLimit() const;
    double getRSILineHighLimit() const;
    double getACUMDISTLowLimit() const;
    double getACUMDISTHighLimit() const;
    double getMALength() const;
    double getMFILowLimit() const;
    double getMFIHighLimit() const;
    double getCCILowLimit() const;
    double getCCIHighLimit() const;

    // Setters
    void setName(const QString &name);
    void setTimeFrame(const QString &timeFrame);
    void setRefreshRate(const QString &refreshRate);
    void setTakeProfitStatus(bool takeProfitStatus);
    void setHasMA(bool hasMA);
    void setHasRSI(bool hasRSI);
    void setHasAD(bool hasAD);
    void setHasMACD(bool hasMACD);
    void setHasMFI(bool hasMFI);
    void setHasCCI(bool hasCCI);
    void setHasSTOOCH(bool hasSTOOCH);
    void setHasVOLUME(bool hasVOLUME);
    void setHasAROON(bool hasAROON);
    void setTakeProfitPercentage(double takeProfitPercentage);
    void setPrefeeredBuyIndex(double prefeeredBuyIndex);
    void setPrefeeredSellIndex(double prefeeredSellIndex);
    void setMACDBlueLineLowLimit(double MACDBlueLineLowLimit);
    void setMACDBlueLineHighLimit(double MACDBlueLineHighLimit);
    void setMACDRedLineLowLimit(double MACDRedLineLowLimit);
    void setMACDRedLineHighLimit(double MACDRedLineHighLimit);
    void setRSILineLowLimit(double RSILineLowLimit);
    void setRSILineHighLimit(double RSILineHighLimit);
    void setACUMDISTLowLimit(double ACUMDISTLowLimit);
    void setACUMDISTHighLimit(double ACUMDISTHighLimit);
    void setMALength(double MALength);
    void setMFILowLimit(double MFILowLimit);
    void setMFIHighLimit(double MFIHighLimit);
    void setCCILowLimit(double CCILowLimit);
    void setCCIHighLimit(double CCIHighLimit);

    QString toString() const;
    QJsonObject toJson() const;
    static Strategy fromJson(const QJsonObject &json);

    static QVector<Strategy> loadSettings(const QString &fileName);
    static void saveSettings(const QVector<Strategy> &settingsList, const QString &fileName);
    static bool addNewStrategy(const Strategy &strategy, const QString &filePath);
    static bool updateStrategy(const Strategy &strategy, const QString &filePath);

};

#endif // STRATEGY_H
