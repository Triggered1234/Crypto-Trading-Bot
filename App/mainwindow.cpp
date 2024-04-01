#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->mainMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * On click portfolio button action:
 * Changes from main menu widget to portfolio widget
 */
void MainWindow::on_portfolioButton_clicked()
{
    if (ui->portfolioMenu) {
        ui->stackedWidget->setCurrentWidget(ui->portfolioMenu);
    } else {
        qDebug() << "Portfolio Menu is not initialized properly";
    }
}

/*
 * On click analysis button action:
 * Changes from main menu widget to analysis widget
 */
void MainWindow::on_analysisButton_clicked()
{
    if (ui->analysisMenu) {
        ui->stackedWidget->setCurrentWidget(ui->analysisMenu);
    } else {
        qDebug() << "Analysis Menu is not initialized properly";
    }
}

/*
 * On click strategies button action:
 * Changes from main menu widget to strategies widget
 */
void MainWindow::on_strategiesButton_clicked()
{
    if (ui->strategiesMenu) {
        ui->stackedWidget->setCurrentWidget(ui->strategiesMenu);
    } else {
        qDebug() << "Strategies Menu is not initialized properly";
    }
}

/*
 * On click risk management button action:
 * Changes from main menu widget to risk management widget
 */
void MainWindow::on_riskManagementButton_clicked()
{
    if (ui->riskManagementMenu) {
        ui->stackedWidget->setCurrentWidget(ui->riskManagementMenu);
    } else {
        qDebug() << "Risk management menu is not initialized properly";
    }
}

/*
 * On click portfolio back button action:
 * Changes from portfolio widget to main menu widget
 */
void MainWindow::on_portfolioBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main is not initialized properly";
    }
}

/*
 * On click analysis back button action:
 * Changes from analysis widget to main menu widget
 */
void MainWindow::on_analysisBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main Menu is not initialized properly";
    }
}

/*
 * On click risk management back button action:
 * Changes from risk management widget to main menu widget
 */
void MainWindow::on_riskManagementBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main menu is not initialized properly";
    }
}

/*
 * On click strategies back button action:
 * Changes from strategies widget to main menu widget
 */
void MainWindow::on_strategiesBackButton_clicked()
{
    if (ui->mainMenu) {
        ui->stackedWidget->setCurrentWidget(ui->mainMenu);
    } else {
        qDebug() << "Main Menu is not initialized properly";
    }
}

/*
 * On click exit button action:
 * Exits the application
 */
void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

