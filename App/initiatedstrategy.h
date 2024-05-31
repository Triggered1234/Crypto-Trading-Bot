#ifndef INITIATEDSTRATEGY_H
#define INITIATEDSTRATEGY_H

#include <QDialog>
#include <QTimer>
#include <QLCDNumber>
#include <QTime>
#include "strategy.h"
#include <QTextEdit>
#include <QElapsedTimer>
namespace Ui {
class InitiatedStrategy;
}

class InitiatedStrategy : public QDialog
{
    Q_OBJECT

public:
    explicit InitiatedStrategy(QWidget *parent = nullptr);
    explicit InitiatedStrategy(const Strategy& strategy, const QString& currentCoinId, double currentCoinBalance, double usdtBalance, double currentCoinPrice, QWidget *parent = nullptr);

    QVector<QString> fetchMACDData(QString coinID);
    void buy(const QString& coinId, const QString& quantity);
    ~InitiatedStrategy();
    void addLog(const QString& message);
    void updateLogsDisplay(const QVector<QString>& logs);

private slots:
    void updateDisplay();

    void on_deployStrategyButton_clicked();

private:
    QTimer *elapsedTimeTimer;
    QTime *elapsedTimeTime;
    Ui::InitiatedStrategy *ui;
    std::shared_ptr<Strategy> strategy;
    QString currentCoinID;
    double currentCoinPrice;
    QElapsedTimer elapsedTimer;
    QTextEdit *logtext;
};

#endif // INITIATEDSTRATEGY_H
