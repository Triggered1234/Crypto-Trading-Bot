#ifndef INITIATEDSTRATEGY_H
#define INITIATEDSTRATEGY_H

#include <QDialog>
#include <QTimer>
#include <QLCDNumber>
#include <QTime>
#include <QElapsedTimer>
#include <QTextEdit>
#include "strategy.hpp"
#include "TechnicalIndicatorUtils.hpp"

namespace Ui {
class InitiatedStrategy;
}

class InitiatedStrategy : public QDialog
{
    Q_OBJECT

public:
    explicit InitiatedStrategy(QWidget *parent = nullptr);
    explicit InitiatedStrategy(const Strategy& strategy, const QString& currentCoinId, double currentCoinBalance, double usdtBalance, double currentCoinPrice, QWidget *parent = nullptr);
    ~InitiatedStrategy();

    void buy(const QString& coinId, const QString& quantity);
    void addLog(const QString& message);
    void updateLogsDisplay(const QVector<QString>& logs);

private slots:
    void updateDisplay();
    void on_deployStrategyButton_clicked();
    void on_stopStrategyButton_clicked();
    void on_closeMenuButton_clicked();

private:
    Ui::InitiatedStrategy *ui;
    std::shared_ptr<Strategy> strategy;
    QString currentCoinID;
    double currentCoinPrice;
    double currentCoinBalance;
    double usdtBalance;

    QElapsedTimer elapsedTimer;
    QElapsedTimer currentCycleTimer; // cronometru pentru un ciclu
    QTimer *elapsedTimeTimer;       // actualizare afisaj timp scurs
    QTimer *strategyCycleTimer;     // nou: cronometru pentru un ciclu
    int refreshRateSeconds;         // nou: durata unui ciclu în secunde
    QTimer *cycleDisplayTimer;
    bool strategyRunning = false;
    int refreshIntervalSecs;
    QTextEdit *logtext;
    int maxIndex;
    int minIndex;
};

#endif // INITIATEDSTRATEGY_H
