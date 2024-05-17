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
    bool hasMA;
    bool hasRSI;
    bool hasAD;
    bool hasMACD;
    bool hasMFI;
    bool hasCCI;
    bool hasSTOOCH;
    bool hasVOLUME;
    bool hasAROON;
    int prefeeredBuyIndex;
    int prefeeredSellIndex;
    int MACDBlueLineLowLimit;
    int MACDBlueLineHighLimit;
    int MACDRedLineLowLimit;
    int MACDRedLineHighLimit;
    int RSILineLowLimit;
    int RSILineHighLimit;

public:
    Strategy(QString name, QString timeFrame, bool hasMA, bool hasRSI, bool hasAD, bool hasMACD,
             bool hasMFI, bool hasCCI, bool hasSTOOCH, bool hasVOLUME, bool hasAROON, int prefeeredBuyIndex,
             int prefeeredSellIndex, int MACDBlueLineLowLimit, int MACDBlueLineHighLimit, int MACDRedLineLowLimit, int MACDRedLineHighLimit, int RSILineLowLimit, int RSILineHighLimit);
    // Getters
    QString getName() const;
    QString getTimeFrame() const;
    bool getHasMA() const;
    bool getHasRSI() const;
    bool getHasAD() const;
    bool getHasMACD() const;
    bool getHasMFI() const;
    bool getHasCCI() const;
    bool getHasSTOOCH() const;
    bool getHasVOLUME() const;
    bool getHasAROON() const;
    int getPrefeeredBuyIndex() const;
    int getPrefeeredSellIndex() const;
    int getMACDBlueLineLowLimit() const;
    int getMACDRedLineLowLimit() const;
    int getMACDBlueLineHighLimit() const;
    int getMACDRedLineHighLimit() const;
    int getRSILineLowLimit() const;
    int getRSILineHighLimit() const;

    // Setters
    void setName(const QString &name);
    void setTimeFrame(const QString &timeFrame);
    void setHasMA(bool hasMA);
    void setHasRSI(bool hasRSI);
    void setHasAD(bool hasAD);
    void setHasMACD(bool hasMACD);
    void setHasMFI(bool hasMFI);
    void setHasCCI(bool hasCCI);
    void setHasSTOOCH(bool hasSTOOCH);
    void setHasVOLUME(bool hasVOLUME);
    void setHasAROON(bool hasAROON);
    void setPrefeeredBuyIndex(int prefeeredBuyIndex);
    void setPrefeeredSellIndex(int prefeeredSellIndex);
    void setMACDBlueLineLowLimit(int MACDBlueLineLowLimit);
    void setMACDBlueLineHighLimit(int MACDBlueLineHighLimit);
    void setMACDRedLineLowLimit(int MACDRedLineLowLimit);
    void setMACDRedLineHighLimit(int MACDRedLineHighLimit);
    void setRSILineLowLimit(int RSILineLowLimit);
    void setRSILineHighLimit(int RSILineHighLimit);

    QString toString() const;
    QJsonObject toJson() const;
    static Strategy fromJson(const QJsonObject &json);

    static QVector<Strategy> loadSettings(const QString &fileName);
    static void saveSettings(const QVector<Strategy> &settingsList, const QString &fileName);
    static bool addNewStrategy(const Strategy &strategy, const QString &filePath);
    static bool updateStrategy(const Strategy &strategy, const QString &filePath);

};

#endif // STRATEGY_H
