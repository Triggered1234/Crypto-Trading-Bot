#include "initiatedstrategy.h"
#include "ui_initiatedstrategy.h"
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

// initiatedstrategy.cpp

void InitiatedStrategy::updateDisplay()
{
    // Get the elapsed time in milliseconds
    qint64 elapsedTimeMs = elapsedTimer.elapsed();

    // Convert milliseconds to hours, minutes, and seconds
    int hours = elapsedTimeMs / (60 * 60 * 1000);
    int minutes = (elapsedTimeMs % (60 * 60 * 1000)) / (60 * 1000);
    int seconds = (elapsedTimeMs % (60 * 1000)) / 1000;

    // Display the time in hh:mm:ss format on the LCD number widget
    ui->elapsedTime->display(QString("%1:%2:%3").arg(hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0')));
}

void InitiatedStrategy::on_deployStrategyButton_clicked()
{
    elapsedTimer.start();
    int index = 0;
    // Create a new timer
    QTimer *elapsedTimeTimer = new QTimer(this);
    connect(elapsedTimeTimer, &QTimer::timeout, this, &InitiatedStrategy::updateDisplay);

    // Start the timer with an interval of 1000 ms (1 second)
    elapsedTimeTimer->start(1000);

    // Add a log message indicating that the strategy is deployed
    addLog("Strategy deployed!");
    QTime waitTime;
    if(this->strategy->getRefreshRate()=="5min")
        waitTime = QTime::currentTime().addSecs(300); // 300 seconds = 5 minutes
    while (true)
    {
        addLog("Fetching data...");
        if(strategy->getHasMACD()==true)
        {
            qDebug() << currentCoinID;
            QVector<QString> macdLines = fetchMACDData(currentCoinID);
            addLog("Successfully fetched MACD Data");
            double MACDRedLine = macdLines[0].toDouble();
            qDebug() << MACDRedLine;
            double MACDBlueLine = macdLines[1].toDouble();
            qDebug() <<MACDBlueLine;
            if(MACDRedLine < strategy->getMACDRedLineLowLimit() && MACDBlueLine < strategy->getMACDRedLineLowLimit())
            {
                addLog("MACD Suggests BUY");
                index++;
            }
            else if(MACDRedLine > strategy->getMACDRedLineHighLimit() && MACDBlueLine > strategy->getMACDBlueLineHighLimit())
            {
                addLog("MACD Suggests SELL");
                index--;
            }
            else addLog("MACD Suggets HOLD/DON'T BUY");
        }

        if(index == 1)
        {
            addLog("Placing buy order for " + currentCoinID);
            buy(currentCoinID, "22");
        }
        else if(index == 0)
            addLog("Holding");
        else if(index == -1)
            addLog("Placing sell order for " + currentCoinID);

        addLog("Waiting for next cycle");
        while (QTime::currentTime() < waitTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // Process events to keep the application responsive
        }
    }
    // Other button clicked actions here
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

QVector<QString> InitiatedStrategy::fetchMACDData(QString coinID) {
    QVector<QString> MACDLines;
    QString program = "python";
    QStringList arguments;
    QString coin = coinID+"USDT";
    arguments << "fetch_macd_data.py" << coin;
    qDebug() << arguments;

    // Create a process to execute the script
    QProcess process;
    process.start(program, arguments);
    process.waitForFinished();

    // Read the output of the script
    QString output = process.readAllStandardOutput();
    qDebug() << output;
    QString error = process.readAllStandardError();

    // Parse the output to extract MACD data
    QStringList lines = output.split(" ");
    if (lines.size() >= 2) {
        QString redLine = lines[0]; // Assuming the first line is MACDRedLine
        QString blueLine = lines[1]; // Assuming the second line is MACDBlueLine
        MACDLines.push_back(redLine);
        MACDLines.push_back(blueLine);
    }
    qDebug() << MACDLines;
    return MACDLines;
}

void InitiatedStrategy::buy(const QString& coinId, const QString& quantity) {
    QStringList arguments;
    arguments << "demobuy.py" << coinId + "USDT" << quantity;
    QProcess process;
    process.start("python", arguments);
    QString output = process.readAllStandardOutput();
    qDebug() << output;
}
