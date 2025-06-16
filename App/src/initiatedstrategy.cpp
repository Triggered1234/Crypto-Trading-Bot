#include "../include/initiatedstrategy.hpp"
#include "ui/ui_initiatedstrategy.h"
#include "ScriptManager.hpp"
#include <QProcess>
InitiatedStrategy::InitiatedStrategy(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InitiatedStrategy)
{
    ui->setupUi(this);
}

InitiatedStrategy::InitiatedStrategy(const Strategy& strategy, const QString& currentCoinID, double currentCoinBalance, double usdtBalance, double currentCoinPrice, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InitiatedStrategy)
{
    this->strategy = std::make_shared<Strategy>(strategy);
    ui->setupUi(this);
    ui->coinLabel->setText(currentCoinID);
    ui->coinBalanceLabel->setText("Coin Balance: " + QString::number(currentCoinBalance));
    ui->usdtBalanceLabel->setText("USDT Balance: " + QString::number(usdtBalance));
    ui->budgetInput->setMaximum(usdtBalance);
    ui->usdtCoinPriceLabel->setText("Coin Balance(USDT): " + QString::number(currentCoinBalance*currentCoinPrice));
    this->currentCoinID = currentCoinID;
    logtext = new QTextEdit(this);
    logtext->setReadOnly(true);
    ui->logsContainerLayout->addWidget(logtext);
    logtext->show();
    qDebug() << currentCoinID;

}

InitiatedStrategy::~InitiatedStrategy()
{
    delete ui;
}

void InitiatedStrategy::updateDisplay()
{
    // Update elapsed time (never resets)
    qint64 elapsedTimeMs = elapsedTimer.elapsed();
    int hours = elapsedTimeMs / (60 * 60 * 1000);
    int minutes = (elapsedTimeMs % (60 * 60 * 1000)) / (60 * 1000);
    int seconds = (elapsedTimeMs % (60 * 1000)) / 1000;
    ui->elapsedTime->display(QString("%1:%2:%3")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0')));
    
}

void InitiatedStrategy::on_deployStrategyButton_clicked()
{
    elapsedTimer.start();
    // Start elapsed time display timer
    if (!elapsedTimeTimer) {
        elapsedTimeTimer = new QTimer(this);
        connect(elapsedTimeTimer, &QTimer::timeout, this, &InitiatedStrategy::updateDisplay);
    }
    elapsedTimeTimer->start(1000);

    // Add a log message indicating that the strategy is deployed
    addLog("Strategy deployed!");

    // Determine refresh interval in milliseconds
    int refreshIntervalMs = 60000; // default 1min
    QString refreshRate = this->strategy->getRefreshRate();
    if (refreshRate == "1min")
        refreshIntervalMs = 60000;
    else if (refreshRate == "5min")
        refreshIntervalMs = 300000;
    else if (refreshRate == "15min")
        refreshIntervalMs = 900000;
    else if (refreshRate == "30min")
        refreshIntervalMs = 1800000;
    else if (refreshRate == "1h")
        refreshIntervalMs = 3600000;
    else if (refreshRate == "6h")
        refreshIntervalMs = 21600000;
    else if (refreshRate == "24h")
        refreshIntervalMs = 86400000;

    // Start the cycle timer
    currentCycleTimer.start();

    // Start a timer to update the cycle timer display every second
    cycleDisplayTimer = new QTimer(this);
    connect(cycleDisplayTimer, &QTimer::timeout, this, [this]() {
        // Only update the cycle timer display
        qint64 cycleTimeMs = currentCycleTimer.elapsed();
        int cycleMinutes = (cycleTimeMs % (60 * 60 * 1000)) / (60 * 1000);
        int cycleSeconds = (cycleTimeMs % (60 * 1000)) / 1000;
        ui->currentCycleTime->display(QString("%1:%2")
            .arg(cycleMinutes, 2, 10, QLatin1Char('0'))
            .arg(cycleSeconds, 2, 10, QLatin1Char('0')));
    });
    cycleDisplayTimer->start(1000);

    // Define the strategy logic as a lambda so we can call it immediately and on timer
    auto strategyLogic = [this]() {
        // Restart the cycle timer at the beginning of each cycle
        currentCycleTimer.start();

        // Reset the cycle timer display to 00:00
        ui->currentCycleTime->display("00:00");

        QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> indicators = strategy->getIndicators();
        int index = 0;
        addLog("Fetching data...");
        if(indicators.contains("MACD"))
        {
            QVector<QString> macdLines = TechnicalIndicators::Utils::fetchMACDData(currentCoinID);
            addLog("Successfully fetched MACD Data");
            double MACDRedLine = macdLines[0].toDouble();
            double MACDBlueLine = macdLines[1].toDouble();
            auto macdIndicator = dynamic_cast<TechnicalIndicators::MACD*>(indicators["MACD"].get());
            if(MACDRedLine < macdIndicator->getMacdRedLineLowLimit() && MACDBlueLine < macdIndicator->getMacdBlueLineLowLimit())
            {
                addLog("MACD Suggests BUY");
                index+= macdIndicator->getImportanceIndex();
            }
            else if(MACDRedLine > macdIndicator->getMacdRedLineHighLimit() && MACDBlueLine > macdIndicator->getMacdBlueLineHighLimit())
            {
                addLog("MACD Suggests SELL");
                index-= macdIndicator->getImportanceIndex();
            }
            else addLog("MACD Suggets HOLD/DON'T BUY");
        }

        if(indicators.contains("RSI"))
        {
            double rsiLine = TechnicalIndicators::Utils::fetchRSIData(currentCoinID);
            auto rsiIndicator = dynamic_cast<TechnicalIndicators::RSI*>(indicators["RSI"].get());
            if(rsiLine < rsiIndicator->getRsiLineLowLimit())
            {
                addLog("RSI Suggests BUY");
                index+= rsiIndicator->getImportanceIndex();
            }
            else if(rsiLine > rsiIndicator->getRsiLineHighLimit())
            {
                addLog("RSI Suggests SELL");
                index-= rsiIndicator->getImportanceIndex();
            }
            else addLog("RSI Suggests HOLD/DON'T BUY");
        }

        if(indicators.contains("ACUMDIST"))
        {
            double ACUMDISTLine = TechnicalIndicators::Utils::fetchACUMDISTData(currentCoinID);
            auto acumDistIndicator = dynamic_cast<TechnicalIndicators::ACUMDIST*>(indicators["ACUMDIST"].get());
            if(ACUMDISTLine < acumDistIndicator->getAcumDistLowLimit())
            {
                addLog("ACUM/DIST Suggests BUY!");
                index+= acumDistIndicator->getImportanceIndex();
            }
            else if(ACUMDISTLine > acumDistIndicator->getAcumDistHighLimit())
            {
                addLog("ACUM/DIST Suggests SELL!");
                index-= acumDistIndicator->getImportanceIndex();
            }
            else addLog("ACUM/DIST Suggests HOLD/DON'T BUY!");
        }

        if(indicators.contains("CCI"))
        {
            double CCILine = TechnicalIndicators::Utils::fetchCCIData(currentCoinID);
            auto cciIndicator = dynamic_cast<TechnicalIndicators::CCI*>(indicators["CCI"].get());
            if(CCILine < cciIndicator->getCciLowLimit())
            {
                addLog("CCI Suggests BUY!");
                index+= cciIndicator->getImportanceIndex();
            }
            else if(CCILine > cciIndicator->getCciHighLimit())
            {
                addLog("CCI Suggests SELL!");
                index-= cciIndicator->getImportanceIndex();
            }
            else addLog("CCI Suggests HOLD/DON'T BUY!");
        }

        if(indicators.contains("MFI"))
        {
            double MFILine = TechnicalIndicators::Utils::fetchMFIData(currentCoinID);
            auto mfiIndicator = dynamic_cast<TechnicalIndicators::MFI*>(indicators["MFI"].get());
            if (MFILine < mfiIndicator->getMfiLowLimit())
            {
                addLog("MFI Suggests BUY!");
                index+= mfiIndicator->getImportanceIndex();
            }
            else if(MFILine > mfiIndicator->getMfiHighLimit())
            {
                addLog("MFI Suggests SELL!");
                index-= mfiIndicator->getImportanceIndex();
            }
            else addLog("MFI Suggests HOLD/DON'T BUY!");
        }

        if(indicators.contains("MA"))
        {
            auto maIndicator = dynamic_cast<TechnicalIndicators::MA*>(indicators["MA"].get());
            double MAValue = TechnicalIndicators::Utils::fetchMAData(currentCoinID, maIndicator->getMaLength());
            if(MAValue <= currentCoinPrice)
            {
                addLog("MA Suggests BUY!");
                index+= maIndicator->getImportanceIndex();
            }
            else if(MAValue >= currentCoinPrice)
            {
                addLog("MA Suggests SELL!");
                index-= maIndicator->getImportanceIndex();
            }
        }
        if(indicators.contains("STOCH"))
        {
            auto stochIndicator = dynamic_cast<TechnicalIndicators::STOCH*>(indicators["STOCH"].get());
            QVector<QString> STOCHLines = TechnicalIndicators::Utils::fetchSTOCHData(currentCoinID);
            if(STOCHLines.size() >= 2)
            {
                double slowK = STOCHLines[0].toDouble();
                double slowD = STOCHLines[1].toDouble();
                if(slowK < stochIndicator->getStochBlueLineLowLimit() && slowD < stochIndicator->getStochRedLineLowLimit())
                {
                    addLog("STOCH Suggests BUY!");
                    index+= stochIndicator->getImportanceIndex();
                }
                else if(slowK > stochIndicator->getStochBlueLineHighLimit() && slowD > stochIndicator->getStochRedLineHighLimit())
                {
                    addLog("STOCH Suggests SELL!");
                    index-= stochIndicator->getImportanceIndex();
                }
                else addLog("STOCH Suggests HOLD/DON'T BUY!");
            }
        }
        if (indicators.contains("AROON"))
        {
            auto aroonIndicator = dynamic_cast<TechnicalIndicators::AROON*>(indicators["AROON"].get());
            QVector<QString> aroonLines = TechnicalIndicators::Utils::fetchAROONData(currentCoinID);
            if(aroonLines.size() >= 2)
            {
                double aroonUp = aroonLines[0].toDouble();
                double aroonDown = aroonLines[1].toDouble();
                if(aroonUp > aroonIndicator->getAroonUpHighLimit() && aroonDown < aroonIndicator->getAroonDownLowLimit())
                {
                    addLog("AROON Suggests BUY!");
                    index+= aroonIndicator->getImportanceIndex();
                }
                else if(aroonUp < aroonIndicator->getAroonUpLowLimit() && aroonDown > aroonIndicator->getAroonDownHighLimit())
                {
                    addLog("AROON Suggests SELL!");
                    index-= aroonIndicator->getImportanceIndex();
                }
                else addLog("AROON Suggests HOLD/DON'T BUY!");
            }
        }

        if(index > strategy->getPreferredBuyIndex())
        {
            double quantity = ((ui->budgetInput->value() * ui->fractionalBuyingPercentage->value()) / 100.0) / currentCoinPrice;
            addLog("Placing buy order for " + currentCoinID + " with quantity: " + QString::number(quantity));
            buy(currentCoinID, QString::number(quantity));
        }
        else if(index < strategy->getPreferredSellIndex())
            addLog("Placing sell order for " + currentCoinID);
        else
            addLog("Holding for " + currentCoinID);

        addLog("Waiting for next cycle");
    };

    // Use a QTimer to periodically execute the strategy logic
    QTimer *strategyTimer = new QTimer(this);
    connect(strategyTimer, &QTimer::timeout, this, strategyLogic);
    strategyTimer->start(refreshIntervalMs);

    // Execute the strategy logic immediately on deployment
    strategyLogic();
}

void InitiatedStrategy::addLog(const QString& message) {
    static const int MaxLogs = 100; // Limit the number of displayed log messages
    static QStringList logs; // Circular buffer to store log messages
    logs.prepend(message); // Add the new log message to the beginning of the buffer
    if (logs.size() > MaxLogs) {
        logs.pop_back(); // Remove the oldest log message if the buffer is full
    }
    updateLogsDisplay(logs);
}

void InitiatedStrategy::updateLogsDisplay(const QStringList& logs) {
    // Clear the existing log messages
    logtext->clear();
    // Add the log messages to the text edit
    logtext->setPlainText(logs.join("\n"));
}

void InitiatedStrategy::buy(const QString& coinId, const QString& quantity) {
    QStringList arguments;
    arguments << "demobuy.py" << coinId + "USDT" << quantity;
    QProcess process;
    process.start("python", arguments);
    QString output = process.readAllStandardOutput();
    qDebug() << output;
}

void InitiatedStrategy::on_stopStrategyButton_clicked()
{
    if (elapsedTimeTimer) {
        elapsedTimeTimer->stop();
    }
    if (cycleDisplayTimer) {
        cycleDisplayTimer->stop();
    }
    currentCycleTimer.invalidate();
    addLog("Strategy stopped.");
    ui->currentCycleTime->display("00:00");
    ui->elapsedTime->display("00:00:00");
}



void InitiatedStrategy::on_closeMenuButton_clicked()
{
    this->close();
    if (elapsedTimeTimer) {
        elapsedTimeTimer->stop();
    }
    if (cycleDisplayTimer) {
        cycleDisplayTimer->stop();
    }
    currentCycleTimer.invalidate();
}

