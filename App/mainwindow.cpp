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
    if (ui->portfolioMenu) {
        ui->stackedWidget->setCurrentWidget(ui->portfolioMenu);
    } else {
        qDebug() << "Portfolio Menu is not initialized properly";
    }
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







