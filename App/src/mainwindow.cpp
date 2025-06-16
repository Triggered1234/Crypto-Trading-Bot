#include "../include/mainwindow.hpp"
#include "ui/ui_mainwindow.h"
#include <QProcess>
#include <QFile>
#include <QCoreApplication> // Include this if QApplication is not included elsewhere
#include <QSettings> // Include for managing configuration files
#include <QMessageBox>
#include "../include/strategydialog.hpp"
#include "../include/initiatedstrategy.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadStrategies();

    SettingsManager& settings = SettingsManager::getInstance();
    settings.loadSettings();

    QString savedApiKey = settings.getApiKey();
    QString savedSecretApiKey = settings.getApiSecretKey();

    if (!savedApiKey.isEmpty() && !savedSecretApiKey.isEmpty()) {
        QStringList autoLoginArgs = { "login.py", savedApiKey, savedSecretApiKey };
        qDebug() << "Auto-login using:" << savedApiKey << savedSecretApiKey;

        bool success = false;
        QStringList output = ScriptManager::getInstance().runScriptSync("login.py", { savedApiKey, savedSecretApiKey }, &success);

        if (success) {
            qDebug() << "Login output successful:";
            ui->stackedWidget->setCurrentWidget(ui->mainMenu);
        } else {
            qDebug() << "Auto-login failed, please log in again.";
            ui->stackedWidget->setCurrentWidget(ui->apiMenu);
        }
    } else {
        ui->stackedWidget->setCurrentWidget(ui->apiMenu);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_portfolioButton_clicked()
{
    if (!ui->portfolioMenu || !ui->portfolioLayout_2) {
        qDebug() << "Portfolio Menu or portfolioLayout_2 is not initialized properly";
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->portfolioMenu);

    SettingsManager& settings = SettingsManager::getInstance();
    bool demoMode = settings.isDemoModeEnabled();

    QString apiKey = demoMode ? settings.getDemoApiKey() : settings.getApiKey();
    QString secretKey = demoMode ? settings.getDemoApiSecretKey() : settings.getApiSecretKey();

    if (apiKey.isEmpty() || secretKey.isEmpty()) {
        qDebug() << "API key or secret is empty. Cannot fetch portfolio.";
        return;
    }

    QString scriptName = demoMode ? "demoportfoliobalance.py" : "portfoliobalance.py";
    QStringList args = { apiKey, secretKey };

    bool ok = false;
    QStringList lines = ScriptManager::getInstance().runScriptSync(scriptName, args, &ok);

    if (!ok) {
        qDebug() << "Script execution failed.";
        return;
    }

    QLayoutItem* child;
    while ((child = ui->portfolioLayout_2->takeAt(0)) != nullptr) {
        if (child->widget()) delete child->widget();
        delete child;
    }

    int row = 0;
    for (const QString& line : lines) {
        QStringList coinInfo = line.split(": ");
        if (coinInfo.size() == 5) {
            QString asset = coinInfo[0].trimmed();
            QString balance = coinInfo[2].trimmed().split(",")[0].trimmed();
            QString price = coinInfo[3].trimmed().split(",")[0].trimmed();
            QString totalValue = coinInfo[4].trimmed();

            QLabel* coinLabel = new QLabel(
                QString("%1: Balance: %2, Price: %3, Total Value: %4")
                .arg(asset, balance, price, totalValue)
            );

            QPushButton* tradeButton = new QPushButton("Trade");
            tradeButton->setProperty("coinName", asset);
            tradeButton->setProperty("coinBalance", balance);
            connect(tradeButton, &QPushButton::clicked, this, &MainWindow::openTransactionMenu);

            ui->portfolioLayout_2->addWidget(coinLabel, row, 0);
            ui->portfolioLayout_2->addWidget(tradeButton, row, 1);
            row++;
        }
        else if (coinInfo.size() >= 3 && coinInfo[0].trimmed() == "USDT") {
            usdtBalance = coinInfo[2].trimmed().split(",")[0].trimmed().toDouble();
            QLabel* usdtLabel = new QLabel(QString("Total USDT Balance: %1").arg(usdtBalance));
            usdtLabel->setAlignment(Qt::AlignCenter);
            ui->portfolioLayout_2->addWidget(usdtLabel, row, 0, 1, 2);
            row++;
            qDebug() << "USDT Balance:" << usdtBalance;
        }
        else if (coinInfo.size() == 2 && coinInfo[0].trimmed() == "Total Balance") {
            QString totalBalance = coinInfo[1].trimmed();
            QLabel* totalLabel = new QLabel(QString("Total Balance: %1").arg(totalBalance));
            totalLabel->setAlignment(Qt::AlignCenter);
            ui->portfolioLayout_2->addWidget(totalLabel, row, 0, 1, 2);
        }
        else {
            qDebug() << "Skipping unrecognized line:" << line;
        }
    }
}

void MainWindow::on_marketsButton_clicked()
{
    if (!ui->marketsMenu || !ui->marketLayout) {
        qDebug() << "marketsMenu or marketLayout is not initialized properly.";
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->marketsMenu);

    QString scriptName = "markets.py";
    QStringList args;

    QLayoutItem* item;
    while ((item = ui->marketLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }

    ScriptManager::getInstance().runScriptAsync(
    scriptName,
    args,
    [=](const QStringList& output) {
        int row = 0;
        for (const QString& line : output) {
            QStringList coinInfo = line.split(": ");
            if (coinInfo.size() == 4) {
                QString asset = coinInfo[0].trimmed();
                QString price = coinInfo[2].trimmed().split(",")[0].trimmed();
                QString priceChange = coinInfo[3].trimmed();

                QLabel* coinLabel = new QLabel(
                    QString("%1: Price: %2, 24h Change: %3")
                    .arg(asset).arg(price).arg(priceChange)
                );
                QPushButton* tradeButton = new QPushButton("Trade");
                tradeButton->setProperty("coinName", asset);
                connect(tradeButton, &QPushButton::clicked, this, &MainWindow::openTransactionMenu);

                ui->marketLayout->addWidget(coinLabel, row, 0);
                ui->marketLayout->addWidget(tradeButton, row, 1);
                row++;
            } else {
                qDebug() << "Skipping line:" << line;
            }
        }
    },
    [=](int exitCode, QProcess::ExitStatus exitStatus) {
        if (exitStatus == QProcess::CrashExit) {
            qDebug() << "Script crashed with exit code" << exitCode;
        } else {
            qDebug() << "Script finished with exit code" << exitCode;
        }
    },
    [=](QProcess::ProcessError error) {
        qDebug() << "Script error output:" << error;
    });
}

void MainWindow::clearPortfolioLayout()
{
    QLayoutItem* item;
    while ((item = ui->portfolioLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::openTransactionMenu()
{
    for (const auto &strategy : strategies) {
        ui->strategiesList->addItem(strategy.getName());
    }
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) {
        qDebug() << "Error: No button found";
        return;
    }

    currentCoinId = button->property("coinName").toString();  // Store the current coin ID
    currentCoinBalance = button->property("coinBalance").toDouble();
    if (currentCoinId.isEmpty()) {
        qDebug() << "Error: coinId is empty";
        return;
    }

    updatePriceEvolution();  // Call to update the evolution data

    // Set up UI
    ui->labelCoin->setText(currentCoinId);  // Update the label with the coin ID
    ui->labelPrice->setText("Loading...");
    ui->labelPriceEvolution->setText("");
    ui->labelUSDTBalance->setText("USDT Balance: " + QString::number(usdtBalance));
    ui->coinBalance->setText("Coin Balance: " + QString::number(currentCoinBalance));
    ui->stackedWidget->setCurrentWidget(ui->transactionMenu);
}

void MainWindow::updatePriceEvolution()
{
    if (currentCoinId.isEmpty()) {
        qDebug() << "Error: currentCoinId is not set";
        return;
    }

    QString binanceSymbol = currentCoinId + "USDT";
    QString interval = ui->evolutionBox->currentText();
    QStringList args = { binanceSymbol, interval };
    QString scriptName = "get_coin_data.py";

    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [this](const QStringList& output) {
            if (!output.isEmpty()) {
                QString line = output[0].trimmed();

                QRegularExpression priceRegex("Current Price: \\$(\\d+\\.?\\d*)");
                QRegularExpressionMatch priceMatch = priceRegex.match(line);

                QRegularExpression changeRegex("24h Change: ([^,]+)");
                QRegularExpressionMatch changeMatch = changeRegex.match(line);

                QString priceStr;
                QString changeStr;

                if (priceMatch.hasMatch())
                    priceStr = "$" + priceMatch.captured(1);

                if (changeMatch.hasMatch())
                    changeStr = changeMatch.captured(1);

                if (!priceStr.isEmpty() && !changeStr.isEmpty()) {
                    QMetaObject::invokeMethod(this, [=]() {
                        ui->labelPrice->setText(priceStr);
                        ui->labelPriceEvolution->setText(changeStr);

                        double priceValue = priceStr.mid(1).toDouble();
                        if (priceValue > 0) {
                            ui->quantity->setMaximum(usdtBalance / priceValue - 0.01);
                        }
                        ui->sellQuantity->setMaximum(currentCoinBalance);
                    }, Qt::QueuedConnection);
                }
            }
        },
        [this](int exitCode, QProcess::ExitStatus exitStatus) {
            if (exitStatus != QProcess::NormalExit || exitCode != 0) {
                qDebug() << "Script finished with errors. Exit code:" << exitCode << ", Exit status:" << exitStatus;
            }
        },
        [this](QProcess::ProcessError error) {
            qDebug() << "Process error occurred:" << error;
        }
    );
}

void MainWindow::executeTrade(const QString& coinName, const QString& tradeType)
{
    // Here you would implement the logic to execute a trade
    // For example, this might involve calling a script with the coinName and tradeType as arguments
    qDebug() << "Executing" << tradeType << "trade for" << coinName;
    // After executing the trade, you may want to update the UI to reflect the new state
}

void MainWindow::on_strategiesButton_clicked()
{
    if (ui->strategiesMenu) {
        // Clear the existing buttons from strategiesLayout
        QLayoutItem *child;
        while ((child = ui->strategiesLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Load strategies
        loadStrategies();

        // Create buttons for each strategy and add them to strategiesLayout
        for (const auto &strategy : strategies) {
            QPushButton *button = new QPushButton(strategy.getName(), ui->strategiesMenu);
            ui->strategiesLayout->addWidget(button);

            // Connect button clicked signal to a lambda to open StrategyDialog for editing
            connect(button, &QPushButton::clicked, this, [=]() {
                editStrategy(strategy);
            });
        }

        ui->stackedWidget->setCurrentWidget(ui->strategiesMenu);
    } else {
        qDebug() << "Strategies Menu is not initialized properly";
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

void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

void MainWindow::on_apiLoginButton_clicked() {
    QString apiKey = ui->apiKeyInput->text();
    QString secretApiKey = ui->secretApiKeyInput->text();

    QString scriptName = "login.py";
    QStringList args = { apiKey, secretApiKey };

    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        args,
        [this](const QStringList& output) {},
        [this](int exitCode, QProcess::ExitStatus exitStatus) {
            if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                SettingsManager& settings = SettingsManager::getInstance();
                settings.setApiKey(ui->apiKeyInput->text());
                settings.setApiSecretKey(ui->secretApiKeyInput->text());
                settings.saveSettings();

                QMetaObject::invokeMethod(this, [this]() {
                    ui->stackedWidget->setCurrentWidget(ui->mainMenu);
                }, Qt::QueuedConnection);
            } else {
                qDebug() << "Script execution failed! Exit code:" << exitCode << ", Exit status:" << exitStatus;
            }
        },
        [this](QProcess::ProcessError error) {
            qDebug() << "Process error occurred:" << error;
        }
    );
}

void MainWindow::on_demoModeToggleButton_toggled(bool checked)
{
    SettingsManager::getInstance().setDemoModeEnabled(checked);
    qDebug() << "[SettingsManager] Demo mode set to:" << checked;
}


void MainWindow::on_evolutionBox_currentIndexChanged(int index)
{
    updatePriceEvolution();
}

void MainWindow::on_buyButton_clicked()
{
    if (!ui->transactionMenu || !ui->transactionLayout)
        return;

    bool demoMode = SettingsManager::getInstance().isDemoModeEnabled();
    QString tradingPair = currentCoinId + "USDT";
    QString quantityStr = QString::number(ui->quantity->value());

    SettingsManager& settings = SettingsManager::getInstance();
    QString apiKey = demoMode ? settings.getDemoApiKey() : settings.getApiKey();
    QString apiSecret = demoMode ? settings.getDemoApiSecretKey() : settings.getApiSecretKey();

    QStringList args;
    if (demoMode) {
        args << apiKey << apiSecret << tradingPair << quantityStr;
        ScriptManager::getInstance().runScriptAsync(
            "demobuy.py",
            args,
            [=](const QStringList& output) {
                for (const QString& line : output)
                    qDebug() << "[DEMOBUY SCRIPT OUTPUT]" << line;
            },
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                qDebug() << "Demo buy script finished with code" << exitCode;
            },
            [=](QProcess::ProcessError error) {
                qDebug() << "Demo buy script error:" << error;
            }
        );
    } else {
        args << apiKey << apiSecret << tradingPair << "BUY" << quantityStr << "0";
        ScriptManager::getInstance().runScriptAsync(
            "buy.py",
            args,
            [=](const QStringList& output) {
                for (const QString& line : output)
                    qDebug() << "[BUY SCRIPT OUTPUT]" << line;
            },
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
                qDebug() << "Buy script finished with code" << exitCode;
            },
            [=](QProcess::ProcessError error) {
                qDebug() << "Buy script error:" << error;
            }
        );
    }

    on_portfolioButton_clicked();
}

void MainWindow::on_sellButton_clicked()
{
    if (!ui->transactionMenu || !ui->transactionLayout) {
        qDebug() << "Portfolio Menu or portfolioLayout_2 is not initialized properly";
        return;
    }

    bool demoMode = SettingsManager::getInstance().isDemoModeEnabled();
    QStringList arguments;
    QString scriptName;

    if (demoMode) {
        scriptName = "demosell.py";
        arguments << SettingsManager::getInstance().getDemoApiKey()
                  << SettingsManager::getInstance().getDemoApiSecretKey()
                  << currentCoinId + "USDT"
                  << QString::number(ui->sellQuantity->value());
    } else {
        scriptName = "sell.py";
        arguments << SettingsManager::getInstance().getApiKey()
                  << SettingsManager::getInstance().getApiSecretKey()
                  << currentCoinId + "USDT"
                  << QString::number(ui->sellQuantity->value());
    }

    ScriptManager::getInstance().runScriptAsync(
        scriptName,
        arguments,
        [this](const QStringList& output) {
            for (const QString& line : output)
                qDebug() << line;
            qDebug() << "ORDER PLACED!";
            on_portfolioButton_clicked();
        },
        [this](int exitCode, QProcess::ExitStatus exitStatus) {
            if (exitStatus != QProcess::NormalExit || exitCode != 0) {
                qDebug() << "Script finished with errors. Exit code:" << exitCode << ", Exit status:" << exitStatus;
            }
        },
        [this](QProcess::ProcessError error) {
            qDebug() << "Process error occurred:" << error;
        }
    );
}

void MainWindow::loadStrategies()
{
    QString fileName = "settings.json";
    strategies = Strategy::loadSettings(fileName);
    qDebug() << "Load Strategies Called";
    for (const auto &strategy : strategies) {
        qDebug() << strategy.toString() << "\n";
    }
}

void MainWindow::on_addStrategyButton_clicked()
{
    qDebug() << "Strategy Dialog Requested";
    StrategyDialog *dialog = new StrategyDialog(this);

    connect(dialog, &StrategyDialog::strategySaved, this, [=]() {
        loadStrategies();
        for (const auto &strategy : strategies) {
            qDebug() << strategy.toString() << "\n";
        }
        dialog->deleteLater();
    });

    dialog->show();
}

void MainWindow::editStrategy(const Strategy &selectedStrategy)
{
    StrategyDialog *dialog = new StrategyDialog(&selectedStrategy, this);

    connect(dialog, &StrategyDialog::strategySaved, this, [=]() {
        loadStrategies();
        dialog->deleteLater();
    });

    dialog->show();
}

void MainWindow::on_transactionMenuBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->portfolioMenu);
}

void MainWindow::on_deployStrategyButton_clicked()
{
    std::shared_ptr<Strategy> currentStrategy;
    for (auto strategy : strategies)
    {
        if(ui->strategiesList->currentText()==strategy.getName())
        {
            initiateStrategy(strategy);
            break;
        };
    }
}

void MainWindow::on_quantity_valueChanged(double arg1)
{
    ui->totalCoinPrice->setText(QString::number(ui->labelPrice->text().split("$").last().toDouble()*ui->quantity->text().toDouble()));
}


void MainWindow::on_sellQuantity_valueChanged(double arg1)
{
    ui->totalCoinPrice->setText(QString::number(ui->labelPrice->text().split("$").last().toDouble()*ui->sellQuantity->text().toDouble()));

}

void MainWindow::initiateStrategy(const Strategy &selectedStrategy)
{
    qDebug() << ui->labelPrice->text().split("$").last();
    initiatedStrategyDialog = std::make_shared<InitiatedStrategy>(selectedStrategy, ui->labelCoin->text(), this->currentCoinBalance, this->usdtBalance, ui->labelPrice->text().split("$").last().toDouble(), this);
    // initiatedStrategyDialog->deleteLater();
    initiatedStrategyDialog->show();
}

void MainWindow::on_settingsButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->settingsMenu);
    SettingsManager& settingsManager = SettingsManager::getInstance();
    settingsManager.loadSettings();
    ui->demoModeToggleButton->setChecked(settingsManager.isDemoModeEnabled());
}

void MainWindow::on_settingsBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainMenu);
}
void MainWindow::on_strategiesBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainMenu);
}


void MainWindow::on_applyButton_clicked()
{
    QString apiKey = ui->settingsApiKeyInput->text();
    QString apiSecretKey = ui->settingsApiSecretKeyInput->text();
    QString demoApiKey = ui->settingsDemoApiKeyInput->text();
    QString demoApiSecretKey = ui->settingsDemoApiSecretKeyInput->text();
    bool demoMode = ui->demoModeToggleButton->isChecked();

    SettingsManager& settingsManager = SettingsManager::getInstance();

    settingsManager.setApiKey(apiKey);
    settingsManager.setApiSecretKey(apiSecretKey);
    settingsManager.setDemoApiKey(demoApiKey);
    settingsManager.setDemoApiSecretKey(demoApiSecretKey);
    settingsManager.setDemoModeEnabled(demoMode);

    settingsManager.saveSettings();

    QMessageBox::information(this, "Settings", "Setările au fost aplicate cu succes.");
}


