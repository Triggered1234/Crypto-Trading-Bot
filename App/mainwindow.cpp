// mainwindow.cpp

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , portfolioMenu(new PortfolioMenu(this))// Initialize the PortfolioMenu instance
    , analysisMenu(new AnalysisMenu(this))// Initialize the AnalysisMenu instance
{
    ui->setupUi(this);
    connect(ui->portfolioButton, &QPushButton::clicked, this, &MainWindow::on_portfolioButton_clicked);
    connect(ui->analysisButton, &QPushButton::clicked, this, &::MainWindow::on_analysisButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * Portfolio button action,
 * Shows the portfolio menu,
 * Hides the main menu
*/
void MainWindow::on_portfolioButton_clicked()
{
    if (portfolioMenu) {
        portfolioMenu->show(); // Show the PortfolioMenu
        centralWidget()->hide();
    } else {
        qDebug() << "PortfolioMenu is not initialized properly";
    }
}

void MainWindow::on_analysisButton_clicked()
{
    if (analysisMenu) {
        analysisMenu->show(); // Show the AnalysisMenu
        centralWidget()->hide();
    } else {
        qDebug() << "AnalysisMenu is not initialized properly";
    }
}
