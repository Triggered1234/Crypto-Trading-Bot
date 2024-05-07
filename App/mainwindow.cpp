#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFile>
#include <QCoreApplication> // Include this if QApplication is not included elsewhere
#include <QSettings> // Include for managing configuration files

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Check if API keys exist in settings
    QSettings settings("PC", "CryptoTradingBot");
    QString savedApiKey = settings.value("apiKey").toString();
    QString savedSecretApiKey = settings.value("secretApiKey").toString();

    if (!savedApiKey.isEmpty() && !savedSecretApiKey.isEmpty()) {
        // Try to log in automatically using saved API keys
        QStringList autoLoginArguments;
        autoLoginArguments << "login.py" << savedApiKey << savedSecretApiKey;
        qDebug() << savedApiKey << savedSecretApiKey;
        QString program = "python";
        QProcess autoLoginProcess;
        autoLoginProcess.setProgram(program);
        autoLoginProcess.setArguments(autoLoginArguments);
        autoLoginProcess.start();
        autoLoginProcess.waitForFinished(-1);

        int exitCode = autoLoginProcess.exitCode();  // Get the exit code
        qDebug() << "Exit code:" << exitCode;  // Print the exit code

        QByteArray output = autoLoginProcess.readAllStandardOutput();  // Read standard output
        QByteArray errorOutput = autoLoginProcess.readAllStandardError();  // Read standard error

        if (exitCode == 0) {
            // Auto-login successful, switch to main menu
            ui->stackedWidget->setCurrentWidget(ui->mainMenu);
        } else {
            qDebug() << "Auto-login failed, please log in again.";
            qDebug() << "Standard output:" << output;  // Print the standard output
            qDebug() << "Standard error:" << errorOutput;  // Print the standard error
            // Show API login menu
            ui->stackedWidget->setCurrentWidget(ui->apiMenu);
        }
    } else {
        // Show API login menu
        ui->stackedWidget->setCurrentWidget(ui->apiMenu);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_portfolioButton_clicked()
{
    if (ui->portfolioMenu && ui->portfolioContentLayout)
    {
        ui->stackedWidget->setCurrentWidget(ui->portfolioMenu);
        QSettings settings("PC", "CryptoTradingBot");
        bool demoMode = settings.value("demoMode").toBool();
        qDebug() << demoMode;
        QString program = "python";
        QStringList arguments;
        if(demoMode)
        {
            qDebug() << "IN DEMO MODE";
            arguments << "demoportfoliobalance.py";
        }
        else
        {
            qDebug() << "NOT IN DEMO MODE";
            arguments << "portfoliobalance.py";
        }
        QProcess *process = new QProcess(this);
        process->setProgram(program);
        process->setArguments(arguments);

        // Connect process signals to slots to read the output
        QObject::connect(process, &QProcess::readyReadStandardOutput, [=]()
                         {
                             QByteArray data = process->readAllStandardOutput();
                             QStringList lines = QString::fromUtf8(data).split('\n', Qt::SkipEmptyParts);
                             qDebug() << lines;
                             QLayoutItem *child;
                             while ((child = ui->portfolioContentLayout->takeAt(0)) != nullptr)
                             {
                                 if (child->widget() != nullptr) {
                                     delete child->widget();
                                 }
                                 delete child;
                             }

                             int row = 0;
                             // Add back button widget
                             QPushButton *portfolioBackButton = new QPushButton("Back");
                             ui->portfolioContentLayout->addWidget(portfolioBackButton, row, 0, 1, 2);
                             row++;

                             for (const QString &line : lines)
                             {
                                 QStringList coinInfo = line.split(": ");
                                 if (coinInfo.size() == 5)
                                 {
                                     QString asset = coinInfo[0].trimmed();
                                     QString balance = coinInfo[2].trimmed().split(",")[0].trimmed();
                                     QString price = coinInfo[3].trimmed().split(",")[0].trimmed();
                                     QString totalValue = coinInfo[4].trimmed();

                                     QLabel *coinLabel = new QLabel(QString("%1: Balance: %2, Price: %3, Total Value: %4")
                                                                        .arg(asset).arg(balance).arg(price).arg(totalValue));
                                     QPushButton *tradeButton = new QPushButton("Trade");
                                     tradeButton->setProperty("coinName", asset);
                                     connect(tradeButton, &QPushButton::clicked, this, &MainWindow::openTransactionMenu);

                                     ui->portfolioContentLayout->addWidget(coinLabel, row, 0);
                                     ui->portfolioContentLayout->addWidget(tradeButton, row, 1);
                                     row++;  // Move to the next row
                                 }
                                 else if (coinInfo.size() == 2 && coinInfo[0].trimmed() == "Total Balance")
                                 {
                                     QString totalBalance = coinInfo[1].trimmed();
                                     QLabel *totalBalanceLabel = new QLabel(QString("Total Balance: %1").arg(totalBalance));

                                     totalBalanceLabel->setAlignment(Qt::AlignCenter);
                                     ui->portfolioContentLayout->addWidget(totalBalanceLabel, row, 0, 1, 2);
                                 } else
                                 {
                                     qDebug() << "Skipping line:" << line;
                                 }
                             }

                             process->deleteLater();  // Clean up the process
                         });

        QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                         [=](int exitCode, QProcess::ExitStatus exitStatus){
                             if (exitStatus == QProcess::CrashExit) {
                                 qDebug() << "Process crashed with code" << exitCode;
                             } else {
                                 qDebug() << "Process finished with code" << exitCode;
                             }
                             process->deleteLater();  // Clean up the process
                         });

        // Connect process signals to slots for error handling
        QObject::connect(process, &QProcess::errorOccurred, [=](QProcess::ProcessError error){
            qDebug() << "Process error:" << error;
            process->deleteLater();  // Clean up the process
        });

        process->start();

        // Wait for the process to finish
        if (!process->waitForFinished(-1)) {
            qDebug() << "Process did not finish properly.";
        }
    } else {
        qDebug() << "Portfolio Menu or portfolioContentLayout is not initialized properly";
    }
}

void MainWindow::on_marketsButton_clicked()
{
    // Check if the marketsMenu and associated layout are initialized correctly
    if (ui->marketsMenu && ui->marketsLayout)
    {
        // Switch to the marketsMenu
        ui->stackedWidget->setCurrentWidget(ui->marketsMenu);

        // Initialize a QProcess to execute the Python script
        QString program = "python";
        QStringList arguments = {"markets.py"}; // Name of the Python script
        QProcess *process = new QProcess(this);
        process->setProgram(program);
        process->setArguments(arguments);

        // Connect process signals to slots to read the output
        QObject::connect(process, &QProcess::readyReadStandardOutput, [=]()
                         {
                             // Read the process output and parse the data
                             QByteArray data = process->readAllStandardOutput();
                             QStringList cryptos = QString::fromUtf8(data).split('\n', Qt::SkipEmptyParts);
                             // qDebug() << cryptos << "DEBUG";
                             // Display the cryptocurrencies in the marketsMenu
                             int test = 0;
                             for (const QString &crypto : cryptos)
                             {
                                 if(test == 5)
                                     break;
                                 qDebug() << crypto << "DEBUG";
                                 QLabel *cryptoLabel = new QLabel(crypto);
                                 ui->marketsLayout->addWidget(cryptoLabel);
                                 test++;
                             }

                             // Clean up the process
                             process->deleteLater();
                         });

        // Connect process signals to slots for error handling
        QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                         [=](int exitCode, QProcess::ExitStatus exitStatus){
                             if (exitStatus == QProcess::CrashExit) {
                                 qDebug() << "Process crashed with code" << exitCode;
                             } else {
                                 qDebug() << "Process finished with code" << exitCode;
                             }
                             // Clean up the process
                             process->deleteLater();
                         });

        // Connect errorOccurred signal for error handling
        QObject::connect(process, &QProcess::errorOccurred, [=](QProcess::ProcessError error){
            qDebug() << "Process error:" << error;
            // Clean up the process
            process->deleteLater();
        });

        // Start the process
        process->start();

        // Wait for the process to finish
        if (!process->waitForFinished(-1)) {
            qDebug() << "Process did not finish properly.";
        }
    } else {
        qDebug() << "marketsMenu or marketsContentLayout is not initialized properly.";
    }

void MainWindow::clearPortfolioLayout()
{
    QLayoutItem* item;
    while ((item = ui->portfolioContentLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();  // delete the widget
        }
        delete item;  // delete the layout item
    }
}

void MainWindow::openTransactionMenu()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) {
        qDebug() << "Error: No button found";
        return;
    }

    currentCoinId = button->property("coinName").toString();  // Store the current coin ID
    if (currentCoinId.isEmpty()) {
        qDebug() << "Error: coinId is empty";
        return;
    }

    updatePriceEvolution();  // Call to update the evolution data

    // Set up UI
    ui->labelCoin->setText(currentCoinId);  // Update the label with the coin ID
    ui->labelPrice->setText("Loading...");
    ui->labelPriceEvolution->setText("");

    ui->stackedWidget->setCurrentWidget(ui->transactionMenu);
}

void MainWindow::updatePriceEvolution()
{
    if (currentCoinId.isEmpty()) {
        qDebug() << "Error: currentCoinId is not set";
        return;
    }

    QString baseCurrency = "USDT";
    QString binanceSymbol = currentCoinId + baseCurrency;
    QString interval = ui->evolutionBox->currentText();

    QProcess *coinDataProcess = new QProcess(this);
    coinDataProcess->start("python", QStringList() << "get_coin_data.py" << binanceSymbol << interval);

    connect(coinDataProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, coinDataProcess](int exitCode, QProcess::ExitStatus exitStatus) {
                if (exitCode == 0 && exitStatus == QProcess::NormalExit) {
                    QString output(coinDataProcess->readAllStandardOutput());
                    QStringList parts = output.split(",");
                    if (parts.size() >= 2) {
                        ui->labelPrice->setText(parts[0].split(":").last().trimmed());
                        ui->labelPriceEvolution->setText(parts[1].split(":").last().trimmed());
                    }
                } else {
                    QString errorOutput(coinDataProcess->readAllStandardError());
                    qDebug() << "Error executing get_coin_data.py:" << errorOutput;
                }
                coinDataProcess->deleteLater();
            });
}

void MainWindow::executeTrade(const QString& coinName, const QString& tradeType)
{
    // Here you would implement the logic to execute a trade
    // For example, this might involve calling a script with the coinName and tradeType as arguments
    qDebug() << "Executing" << tradeType << "trade for" << coinName;
    // After executing the trade, you may want to update the UI to reflect the new state
}


void MainWindow::on_analysisButton_clicked()
{
    if (ui->analysisMenu) {
        ui->stackedWidget->setCurrentWidget(ui->analysisMenu);
    } else {
        qDebug() << "Analysis Menu is not initialized properly";
    }
}

void MainWindow::on_strategiesButton_clicked()
{
    if (ui->strategiesMenu) {
        ui->stackedWidget->setCurrentWidget(ui->strategiesMenu);
    } else {
        qDebug() << "Strategies Menu is not initialized properly";
    }
}

void MainWindow::on_riskManagementButton_clicked()
{
    if (ui->riskManagementMenu) {
        ui->stackedWidget->setCurrentWidget(ui->riskManagementMenu);
    } else {
        qDebug() << "Risk management menu is not initialized properly";
    }
}

void MainWindow::on_portfolioBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main is not initialized properly";
    }
}

void MainWindow::on_marketsMenuBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main is not initialized properly";
    }
}

void MainWindow::on_analysisBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main Menu is not initialized properly";
    }
}

void MainWindow::on_riskManagementBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main menu is not initialized properly";
    }
}

void MainWindow::on_strategiesBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main Menu is not initialized properly";
    }
}

void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

void MainWindow::on_apiLoginButton_clicked() {
    QString apiKey = ui->apiKeyInput->text();
    QString secretApiKey = ui->secretApiKeyInput->text();

    // Run the script with provided API keys
    QStringList arguments;
    arguments << "login.py" << apiKey << secretApiKey;
    QString program = "python";
    QProcess process;
    process.setProgram(program);
    process.setArguments(arguments);
    process.start();
    process.waitForFinished(-1);

    if (process.exitCode() == 0) { // Check if the script ran successfully (exit code 0)
        // Save API keys into settings
        QSettings settings("PC", "CryptoTradingBot");
        settings.setValue("apiKey", apiKey);
        settings.setValue("secretApiKey", secretApiKey);

        // Switch to main menu
        ui->stackedWidget->setCurrentWidget(ui->mainMenu); // Assuming ui->stackedWidget is used for managing pages
    } else {
        qDebug() << "Script execution failed!";
        // Handle failure, maybe show an error message to the user
    }
}

void MainWindow::on_demoModeToggleButton_toggled(bool checked)
{
    QSettings settings("PC", "CryptoTradingBot");
    if (checked) {
        settings.setValue("demoMode", true);
        qDebug() << checked;
    } else {
        settings.setValue("demoMode", false);
        qDebug() << checked;
    }
}

void MainWindow::on_evolutionBox_currentIndexChanged(int index)
{
    updatePriceEvolution();
}
